#include "watertank_LSF.h"

watertank_LSF::watertank_LSF(sc_module_name) :
    aperture_ams("aperture_ams"),
    converter1("converter1"),
    converter2("converter2"),
    integ("integrator"),
    mul1("multiplier_a", 0.6),
    mul2("multiplier_b", 0.03),
    sub("subtractor"),
    sig1("sig1"),
    sig2("sig2"),
    sig3("sig3"),
    sig4("sig4"),
    sig5("sig5") {
  converter1.inp(aperture_ams); // read the current value of the aperture_ams
  converter1.y(sig1); // put result on sig1

  // first multiplier
  mul1.x(sig1);
  mul1.y(sig2);

  // subtractor
  sub.x1(sig2);
  sub.x2(sig5);
  sub.y(sig3);

  // integrator
  integ.x(sig3);
  integ.y(sig4);

  // second multiplier
  mul2.x(sig4);
  mul2.y(sig5);

  // write the value
  converter2.x(sig4);
  converter2.outp(water_level);
}
