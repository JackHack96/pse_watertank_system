#include "watertank_iface.h"

watertank_iface::watertank_iface(sc_core::sc_module_name) :
    water_level_ams("water_level_ams"),
    water_level("water_level") {
}

void watertank_iface::processing() {
  water_level.write(water_level_ams.read());
}

