#include "controller_TLM.h"

controller_TLM::controller_TLM(sc_module_name name) : sc_module(name) {
  watertank_socket(*this);
  xtea_socket(*this);
  SC_THREAD(run);
}

void controller_TLM::run() {
  sc_time local_time;
  tlm::tlm_generic_payload payload;
  while (true) {
    wait(1000, SC_MS);

    // load packet from watertank transactor
    payload.set_data_ptr((unsigned char *) &watertank_packet);
    payload.set_address(0);
    payload.set_read();
    watertank_socket->b_transport(payload, local_time);

    xtea_packet.key[0] = key[0];
    xtea_packet.key[1] = key[1];
    xtea_packet.key[2] = key[2];
    xtea_packet.key[3] = key[3];
    xtea_packet.text[1] = 0;

    if (watertank_packet.water_level >= 5 && watertank_packet.water_level <= 8.8)
      xtea_packet.text[0] = VALVE_COMMAND::IDLE;
    else if (watertank_packet.water_level > 8.8) {
      xtea_packet.text[0] = VALVE_COMMAND::CLOSE;
      valve_aperture_threshold *= 0.7;
    } else if (watertank_packet.water_level < 5) {
      xtea_packet.text[0] = VALVE_COMMAND::OPEN;
      valve_aperture_threshold *= 1.1;
    }

    // Do encryption
    xtea_encrypt();

    payload.set_data_ptr((unsigned char *) &xtea_packet);
    payload.set_address(0);
    payload.set_write();

    // Start write transaction
    xtea_socket->b_transport(payload, local_time);

    // Write aperture threshold to the valve transactor
    aperture_threshold.write(valve_aperture_threshold);
  }
}

void controller_TLM::invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) {}

tlm::tlm_sync_enum controller_TLM::nb_transport_bw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t) {
  return tlm::TLM_COMPLETED;
}

void controller_TLM::xtea_encrypt() {
  sc_uint<64> sum;
  sc_uint<32> i, delta, v0, v1, temp;
  v0 = xtea_packet.text[0];
  v1 = xtea_packet.text[1];
  sum = 0;

  // encipher
  delta = 0x9e3779b9;
  for (i = 0; i < 32; i++) {

    if ((sum & 3) == 0)
      temp = xtea_packet.key[0];
    else if ((sum & 3) == 1)
      temp = xtea_packet.key[1];
    else if ((sum & 3) == 2)
      temp = xtea_packet.key[2];
    else
      temp = xtea_packet.key[3];

    v0 += (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + temp);

    sum += delta;

    if (((sum >> 11) & 3) == 0)
      temp = xtea_packet.key[0];
    else if (((sum >> 11) & 3) == 1)
      temp = xtea_packet.key[1];
    else if (((sum >> 11) & 3) == 2)
      temp = xtea_packet.key[2];
    else
      temp = xtea_packet.key[3];

    v1 += (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + temp);
  }

  xtea_packet.text[0] = v0;
  xtea_packet.text[1] = v1;

  timing_annotation += sc_time(100, SC_NS);
}