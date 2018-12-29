#ifndef WATERTANK_SYSTEM_WATERTANK_IFACE_H
#define WATERTANK_SYSTEM_WATERTANK_IFACE_H

#include <systemc-ams.h>
#include "valve_command.h"

SCA_TDF_MODULE(watertank_iface) {
public:
  sca_tdf::sca_in<double> water_level_ams;

  sca_tdf::sca_de::sca_out<double> water_level;

  explicit watertank_iface(sc_core::sc_module_name);

  void processing();

};

#endif //WATERTANK_SYSTEM_WATERTANK_IFACE_H
