#include "watertank_system.h"

void watertank_system::clock() {
  while(true) {
    clk.write(true);
    wait(100, SC_US);
    clk.write(false);
    wait(100, SC_US);
  }
}

watertank_system::watertank_system(sc_core::sc_module_name name) :
    sc_module(name),
    watertank("watertank"),
    valve("valve"),
    controller("controller"),
    xtea("xtea"),
    watertank_transactor("watertank_trasactor"),
    watertank_interface("watertank_interface"),
    xtea_transactor("xtea_transactor"),
    valve_interface("valve_interface") {
  // Valve connection
  valve.command_ams(command_ams);
  valve.aperture_threshold_ams(aperture_threshold_ams);
  valve.aperture_ams(current_aperture_ams);

  // Watertank connection
  watertank.aperture_ams(current_aperture_ams);
  watertank.water_level_ams(water_level_ams);

  // Watertank interface connection
  watertank_interface.water_level_ams(water_level_ams);
  watertank_interface.water_level(water_level);

  // Watertank transactor connection
  watertank_transactor.water_level(water_level);

  // Controller connection
  controller.watertank_socket(watertank_transactor.target_socket);
  controller.aperture_threshold(aperture_threshold);
  valve_interface.aperture_threshold(aperture_threshold);

  // XTEA transactor connection
  controller.xtea_socket(xtea_transactor.target_socket);
  xtea_transactor.clk(clk);
  xtea_transactor.input_ready(input_ready);
  xtea_transactor.text_input[0](text_input[0]);
  xtea_transactor.text_input[1](text_input[1]);
  xtea_transactor.key_input[0](key_input[0]);
  xtea_transactor.key_input[1](key_input[1]);
  xtea_transactor.key_input[2](key_input[2]);
  xtea_transactor.key_input[3](key_input[3]);

  // XTEA RTL connection
  xtea.clk(clk);
  xtea.rst(rst);
  xtea.input_ready(input_ready);
  xtea.output_ready(output_ready);
  xtea.text_input[0](text_input[0]);
  xtea.text_input[1](text_input[1]);
  xtea.key_input[0](key_input[0]);
  xtea.key_input[1](key_input[1]);
  xtea.key_input[2](key_input[2]);
  xtea.key_input[3](key_input[3]);
  xtea.data_output[0](command);
  xtea.data_output[1](data_output[1]);

  // Valve interface connection
  valve_interface.command(command);
  valve_interface.command_ams(command_ams);
  valve_interface.aperture_threshold_ams(aperture_threshold_ams);

  SC_THREAD(clock);
}