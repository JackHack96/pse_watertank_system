#ifndef WATERTANK_SYSTEM_VALVE_IFACE_H
#define WATERTANK_SYSTEM_VALVE_IFACE_H

#include <systemc-ams.h>
#include "valve_command.h"

SCA_TDF_MODULE(valve_iface) {
public:
  sca_tdf::sca_out<double> aperture_threshold_ams;
  sca_tdf::sca_out<VALVE_COMMAND> command_ams;

  sca_tdf::sca_de::sca_in<double> aperture_threshold;
  sca_tdf::sca_de::sca_in<sc_uint<32>> command;

  explicit valve_iface(sc_core::sc_module_name);

  void processing();

};

#endif //WATERTANK_SYSTEM_VALVE_IFACE_H
