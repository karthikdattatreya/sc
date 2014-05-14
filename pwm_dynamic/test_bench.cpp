// testbench.cpp
//
// TODO: improve parametrization of pi_ctrl1 and drv_motor1 -- especially the omega parameters (2 pi f).

#include <systemc-ams>

#include "pwm.h"
#include "pi_ctrl.h"
#include "diff.h"
#include "ref_src.h"
#include "drv_motor.h"


int sc_main(int argc, char* argv[])
{
  using sca_core::sca_time;
  sc_core::sc_set_time_resolution(1.0, sc_core::SC_FS);


  // ref_src
  const double ref_val = 7.5;
  const sca_time t_step = sca_core::sca_time(0.01, sc_core::SC_MS);
  // pi_ctrl1
  const double kp = 1.0 / 15.0;       // original value: 2.0
  const double ki = 2.0 * M_PI * 2.0; // original value: 5.0
  // pwm1
  const double v0 = 0.0;
  const double v1 = 1.0;
  const sca_time t_period = sca_time(100.0 * 0.05, sc_core::SC_MS); // original value: 255 * 0.05 ms
  const sca_time t_ramp = sca_time(0.05, sc_core::SC_MS);           // original value: 0.05 ms
  // drv_motor1
  const double h0 = 15.0;                  // original value: 255.0
  const double omega0 = 2.0 * M_PI * 10.0; // original value: 20.0

  sca_tdf::sca_signal<double> iref, ierr, imeas, ictrl, vdrv;

  ref_src ref_src1("ref_src1", ref_val, t_step);
   ref_src1.out(iref);

  diff diff1("diff1");
   diff1.ref(iref);
   diff1.meas(imeas);
   diff1.err(ierr);

  pi_ctrl pi_ctrl1("pi_ctrl1", kp, ki);
   pi_ctrl1.in(ierr);
   pi_ctrl1.out(ictrl);

  pwm pwm1("pwm1", v0, v1, t_period, t_ramp);
   pwm1.in(ictrl);
   pwm1.out(vdrv);

  drv_motor drv_motor1("drv_motor1", h0, omega0);
   drv_motor1.in(vdrv);
   drv_motor1.out(imeas);


  sca_util::sca_trace_file* tfp_tab = sca_util::sca_create_tabular_trace_file("pwm_dynamic");
  sca_util::sca_trace(tfp_tab, iref, "iref");
  sca_util::sca_trace(tfp_tab, imeas, "imeas");
  sca_util::sca_trace(tfp_tab, ierr, "ierr");
  sca_util::sca_trace(tfp_tab, ictrl, "ictrl");
  sca_util::sca_trace(tfp_tab, vdrv, "vdrv");



  sc_start(0.2,sc_core::SC_SEC);


  sc_core::sc_stop();
  sca_util::sca_close_tabular_trace_file(tfp_tab);

  return 0;
}
