#ifndef WATERTANK_SYSTEM_XTEA_TLM_LT_TESTBENCH_H
#define WATERTANK_SYSTEM_XTEA_TLM_LT_TESTBENCH_H

#include <systemc-ams.h>
#include <tlm.h>
#include <tlm_utils/tlm_quantumkeeper.h>
#include "iostructs.h"
#include "valve_command.h"

class controller_TLM : public sc_module, public tlm::tlm_bw_transport_if<>{
public:
  // constructors
  SC_HAS_PROCESS(controller_TLM);
  explicit controller_TLM(sc_module_name name_);

  // TLM ports
  tlm::tlm_initiator_socket<> watertank_socket;
  tlm::tlm_initiator_socket<> xtea_socket;

  // functions that must be implemented to be compliant with the standard not used here
  void invalidate_direct_mem_ptr(uint64 start_range, uint64 end_range) override;
  tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans, tlm::tlm_phase &phase, sc_time &t) override;

  //RTL Interface to the valve (for the aperture threshold)
  sc_core::sc_out<double> aperture_threshold;
private:
  // internal data
  watertank_packet_struct watertank_packet;
  xtea_packet_struct xtea_packet;
  sc_time timing_annotation;

  double valve_aperture_threshold;

  sc_uint<32> key[4] = {0x6a1d78c8, 0x8c86d67f, 0x2a65bfbe, 0xb4bd6e46};

  tlm_utils::tlm_quantumkeeper m_qk;

  void run();
  void xtea_encrypt();
};

#endif //WATERTANK_SYSTEM_XTEA_TLM_LT_TESTBENCH_H
