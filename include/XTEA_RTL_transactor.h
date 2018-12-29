#ifndef WATERTANK_SYSTEM_XTEA_RTL_TRANSACTOR_H
#define WATERTANK_SYSTEM_XTEA_RTL_TRANSACTOR_H

#include <systemc.h>
#include <tlm.h>
#include "iostructs.h"

class XTEA_RTL_transactor : public sc_module, public tlm::tlm_fw_transport_if<> {
public:
  // TLM side
  tlm::tlm_target_socket<> target_socket;
  xtea_packet_struct xtea_packet;
  sc_event begin_write, end_write;

  // TLM interfaces
  void b_transport(tlm::tlm_generic_payload &trans, sc_time &t) override;
  bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data) override;
  tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t) override;
  unsigned int transport_dbg(tlm::tlm_generic_payload &trans) override;

  //RTL ports
  sc_in_clk clk;   // The clock signal

  sc_out <sc_uint<32>> text_input[2]; // 32-bit data input ports
  sc_out <sc_uint<32>> key_input[4];  // 32-bit key input ports

  sc_out<bool> input_ready; // Flag for telling system is ready

  //processes
  void WRITEPROCESS();

  //mandatory for TLM
  void end_of_elaboration();

  SC_HAS_PROCESS(XTEA_RTL_transactor);
  XTEA_RTL_transactor(sc_module_name name_);
};

#endif //WATERTANK_SYSTEM_XTEA_RTL_TRANSACTOR_H
