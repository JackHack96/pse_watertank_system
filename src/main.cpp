#include "watertank_system.h"

int sc_main(int argc, char *argv[]) {
  watertank_system s("watertank_system");

  sca_trace_file *file = sca_create_vcd_trace_file("watertank_ams");
  sc_trace_file *file2=sc_create_vcd_trace_file("watertank");

  sca_trace(file, s.aperture_threshold_ams, "aperture_threshold_ams");
  sca_trace(file, s.command_ams,"command_ams");
  sca_trace(file, s.current_aperture_ams, "current_aperture_ams");

  sca_trace(file, s.water_level, "water_level");
  sc_trace(file2, s.command, "command");
  sca_trace(file, s.aperture_threshold, "aperture_threshold");

  sc_trace(file2, s.clk, "clk");
  sc_trace(file2, s.rst, "rst");
  sc_trace(file2, s.input_ready, "input_ready");
  sc_trace(file2, s.output_ready, "output_ready");
  sc_trace(file2, s.text_input, "text_input");
  sc_trace(file2, s.key_input, "key_input");
  sc_trace(file2, s.data_output, "data_output");

  sc_start(1, SC_MS);
  sca_close_vcd_trace_file(file);
  sc_close_vcd_trace_file(file2);
}