#ifndef WATERTANK_SYSTEM_WATERTANK_LSF_H
#define WATERTANK_SYSTEM_WATERTANK_LSF_H

#include <systemc-ams.h>

class watertank_LSF : public sc_core::sc_module {
public:
  sca_tdf::sca_out<double> water_level_ams;
  sca_tdf::sca_in<double> aperture_ams;

  explicit watertank_LSF(sc_module_name);

private:

  sca_lsf::sca_tdf::sca_source converter1;
  sca_lsf::sca_tdf::sca_sink converter2;

  sca_lsf::sca_gain mul1, mul2;
  sca_lsf::sca_sub sub;
  sca_lsf::sca_integ integ;

  sca_lsf::sca_signal sig1, sig2, sig3, sig4, sig5;
};

#endif //WATERTANK_SYSTEM_WATERTANK_LSF_H
