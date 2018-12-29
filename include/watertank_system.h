#ifndef WATERTANK_SYSTEM_WATERTANK_SYSTEM_H
#define WATERTANK_SYSTEM_WATERTANK_SYSTEM_H

#include "watertank_LSF.h"
#include "valve_TDF.h"
#include "XTEA_RTL.h"
#include "controller_TLM.h"

#include "watertank_LSF_transactor.h"
#include "XTEA_RTL_transactor.h"
#include "valve_iface.h"

class watertank_system : public sc_module {
public:
  explicit watertank_system(sc_core::sc_module_name);
  watertank_LSF watertank;
  valve_TDF valve;
  controller_TLM controller;
  XTEA_RTL xtea;

  watertank_LSF_transactor watertank_transactor;
  XTEA_RTL_transactor xtea_transactor;
  valve_iface valve_interface;

  sca_tdf::sca_signal<double> aperture_threshold_ams;
  sca_tdf::sca_signal<VALVE_COMMAND> command_ams;
  sca_tdf::sca_signal<double> current_aperture_ams;

  sc_core::sc_signal<double> water_level;
  sc_core::sc_signal<sc_uint<32>> command;
  sc_core::sc_signal<double> aperture_threshold;

  sc_clock clk;
  sc_signal<bool> rst, input_ready, output_ready;
  sc_signal<sc_uint<32>> text_input[2];
  sc_signal<sc_uint<32>> key_input[4];
  sc_signal<sc_uint<32>> data_output[2];
};

#endif //WATERTANK_SYSTEM_WATERTANK_SYSTEM_H
