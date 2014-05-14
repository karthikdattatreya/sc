// ref_src.h
// constant reference source

#ifndef REF_SRC_H
#define REF_SRC_H

#include <systemc-ams>

SCA_TDF_MODULE(ref_src)
{
public:
  sca_tdf::sca_out<double> out;

  ref_src( sc_core::sc_module_name nm, double value_= 1.0, sca_core::sca_time t_step_ = sca_core::sca_time(0.05, sc_core::SC_MS) )
  : out("out"), value(value_), t_step(t_step_)
  {}

  void set_attributes()
  {
    out.set_timestep(t_step);
    accept_attribute_changes();
  }

  void processing()
  {
    out.write(value);
  }

private:
  double value;
  sca_core::sca_time t_step;
};

#endif // REF_SRC_H

/*
 * Local Variables:
 * mode: C++
 * End:
 */
