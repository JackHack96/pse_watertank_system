#ifndef WATERTANK_SYSTEM_VALVE_TDF_H
#define WATERTANK_SYSTEM_VALVE_TDF_H

#include <systemc-ams.h>
#include "valve_command.h"

SCA_TDF_MODULE(valve_TDF) {
public:
  sca_tdf::sca_in<double> aperture_threshold_ams;
  sca_tdf::sca_in<VALVE_COMMAND> command_ams;

  sca_tdf::sca_out<double> aperture_ams;

  explicit valve_TDF(sc_core::sc_module_name);

  void processing() override;

  void set_attributes() override;

private:
  double current_aperture;
};

#endif //WATERTANK_SYSTEM_VALVE_TDF_H
