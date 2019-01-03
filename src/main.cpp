#include "watertank_system.h"

int sc_main(int argc, char *argv[]) {
  watertank_system s("watertank_system");

  sca_trace_file *file = sca_create_vcd_trace_file("watertank_ams");


  sca_trace(file, s.water_level_ams, "water_level");
  sca_trace(file, s.aperture_threshold_ams, "aperture_threshold");


  sc_start(500, SC_SEC);
  sca_close_vcd_trace_file(file);
}