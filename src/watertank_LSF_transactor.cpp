#include "watertank_LSF_transactor.h"

watertank_LSF_transactor::watertank_LSF_transactor(sc_module_name name)
    : sc_module(name), target_socket("target_socket"),
      pending_transaction(NULL) {
  target_socket(*this);
}

void watertank_LSF_transactor::b_transport(tlm::tlm_generic_payload &trans,
                                           sc_time &t) {
  watertank_packet = *((watertank_packet_struct *) trans.get_data_ptr());
  watertank_packet.water_level = water_level.read();
  *((watertank_packet_struct *) trans.get_data_ptr()) = watertank_packet;
}

bool watertank_LSF_transactor::get_direct_mem_ptr(
    tlm::tlm_generic_payload &trans, tlm::tlm_dmi &dmi_data) {
  return false;
}

tlm::tlm_sync_enum
watertank_LSF_transactor::nb_transport_fw(tlm::tlm_generic_payload &trans,
                                          tlm::tlm_phase &phase, sc_time &t) {
  return tlm::TLM_COMPLETED;
}

unsigned int
watertank_LSF_transactor::transport_dbg(tlm::tlm_generic_payload &trans) {
  return 0;
}

void watertank_LSF_transactor::end_of_elaboration() {
  sc_module::end_of_elaboration();
}
