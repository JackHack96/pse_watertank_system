#include "XTEA_RTL_transactor.h"

XTEA_RTL_transactor::XTEA_RTL_transactor(sc_module_name name_)
    : sc_module(name_), target_socket("target_socket") {
  target_socket(*this);
  SC_THREAD(WRITEPROCESS);
  sensitive << clk.pos();
}

void XTEA_RTL_transactor::b_transport(tlm::tlm_generic_payload &trans,
                                      sc_time &t) {
  tlm::tlm_command trans_command = trans.get_command();

  switch (trans_command) {
  case tlm::TLM_WRITE_COMMAND:
    xtea_packet = *((xtea_packet_struct *)trans.get_data_ptr());
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    begin_write.notify();
    wait(end_write);
    break;
  case tlm::TLM_READ_COMMAND:
    trans.set_response_status(tlm::TLM_OK_RESPONSE);
    break;
  default:
    break;
  }
}

void XTEA_RTL_transactor::WRITEPROCESS() {
  while (true) {
    wait(begin_write);
    key_input[0].write(xtea_packet.key[0]);
    key_input[1].write(xtea_packet.key[1]);
    key_input[2].write(xtea_packet.key[2]);
    key_input[3].write(xtea_packet.key[3]);
    text_input[0].write(xtea_packet.text[0]);
    text_input[1].write(xtea_packet.text[1]);
    input_ready.write(1);
    end_write.notify();
    wait();
  }
}

void XTEA_RTL_transactor::end_of_elaboration() { }

bool XTEA_RTL_transactor::get_direct_mem_ptr(tlm::tlm_generic_payload &trans,
                                             tlm::tlm_dmi &dmi_data) {
  return false;
}

tlm::tlm_sync_enum
XTEA_RTL_transactor::nb_transport_fw(tlm::tlm_generic_payload &trans,
                                     tlm::tlm_phase &phase, sc_time &t) {
  return tlm::TLM_UPDATED;
}

unsigned int
XTEA_RTL_transactor::transport_dbg(tlm::tlm_generic_payload &trans) {
  return 0;
}
