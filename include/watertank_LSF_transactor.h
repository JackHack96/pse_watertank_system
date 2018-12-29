#ifndef WATERTANK_SYSTEM_WATERTANK_LSF_TRANSACTOR_H
#define WATERTANK_SYSTEM_WATERTANK_LSF_TRANSACTOR_H

#include <systemc.h>
#include <tlm.h>
#include "iostructs.h"

class watertank_LSF_transactor : public sc_module, public virtual tlm::tlm_fw_transport_if<> {
public:
  tlm::tlm_target_socket<> target_socket;

  void b_transport(tlm::tlm_generic_payload &trans, sc_time &t) override;
  bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans,
                          tlm::tlm_dmi &dmi_data) override;

  unsigned int transport_dbg(tlm::tlm_generic_payload &trans) override;

  void end_of_elaboration() override;

  tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans,
                                     tlm::tlm_phase &phase, sc_time &t) override;

  watertank_packet_struct watertank_packet;

  tlm::tlm_generic_payload *pending_transaction;

  sc_time timing_annotation;

  SC_HAS_PROCESS(watertank_LSF_transactor);

  explicit watertank_LSF_transactor(sc_module_name name);

  // RTL Interface
  sc_in<double> water_level;
};

#endif // WATERTANK_SYSTEM_WATERTANK_LSF_TRANSACTOR_H
