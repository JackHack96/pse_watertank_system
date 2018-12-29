#include "valve_TDF.h"

valve_TDF::valve_TDF(sc_core::sc_module_name) :
    aperture_threshold_ams("aperture_threshold_ams"),
    command_ams("command_ams"),
    aperture_ams("aperture_ams") {
}

void valve_TDF::processing() {
  current_threshold = aperture_threshold_ams.read();
  switch (command_ams.read()) {
  case IDLE:break;
  case OPEN:
    if (current_aperture < current_threshold) // valve's aperture_ams can be opened more
      current_aperture += 0.25 * get_timestep().to_seconds();
    else // we can't open the valve more than this
      current_aperture = current_threshold;
    break;
  case CLOSE:
    if (current_aperture > 0) // valve's aperture_ams can be closed more
      current_aperture -= 0.25 * get_timestep().to_seconds();
    else // we can't close the valve more than this
      current_aperture = 0;
    break;
  }
  aperture_ams.write(current_aperture);
}

void valve_TDF::set_attributes() {
  this->set_timestep(1, SC_MS);
}