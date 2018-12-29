#include "valve_iface.h"

valve_iface::valve_iface(sc_core::sc_module_name) :
    aperture_threshold_ams("aperture_threshold_ams"),
    command_ams("command_ams"),
    aperture_threshold("aperture_threshold"),
    command("command") {
}

void valve_iface::processing() {
  aperture_threshold_ams.write(aperture_threshold.read());
  switch (command.read()) {
  case 1:command_ams.write(VALVE_COMMAND::OPEN);
    break;
  case 2:command_ams.write(VALVE_COMMAND::CLOSE);
    break;
  default:command_ams.write(VALVE_COMMAND::IDLE);
    break;
  }
}

