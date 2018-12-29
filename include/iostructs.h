#ifndef WATERTANK_SYSTEM_IOSTRUCT_H
#define WATERTANK_SYSTEM_IOSTRUCT_H

#include <systemc.h>
#include "valve_command.h"

struct xtea_packet_struct {
  sc_uint<32> key[4];
  sc_uint<32> text[2];
};

struct watertank_packet_struct{
  double water_level;
};


#endif //WATERTANK_SYSTEM_IOSTRUCT_H
