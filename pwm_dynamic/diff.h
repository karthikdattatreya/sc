// diff.h

#ifndef DIFF_H
#define DIFF_H

#include <systemc-ams>

SCA_TDF_MODULE(diff)
{
public:
  sca_tdf::sca_in<double> ref, meas;
  sca_tdf::sca_out<double> err;

  SCA_CTOR(diff) : ref("ref"), meas("meas"), err("err")
  {}

  void set_attributes()
  {
    err.set_delay(1); // essential - system has control loop
    // Enable DTDF, attention this will cause variiations in the delay
    // introduced to break the algebraic loop.
    accept_attribute_changes();
  }

  void processing()
  {
    err.write( ref.read() - meas.read() );
  }
};

#endif // DIFF_H

/*
 * Local Variables:
 * mode: C++
 * End:
 */
