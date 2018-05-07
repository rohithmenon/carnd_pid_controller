#ifndef PID_H
#define PID_H

class PID {
 public:

 /*
  * Constructor
  */
  PID(double kp,
      double ki,
      double kd,
      double target,
      double min_correction,
      double max_correction,
      double integral_decay);

 /*
  * Report observation.
  */
  void Report(double observation);

 /*
  * Correction to be applied
  */
  double Correction();
 private:
  // Gains
  double kp_;
  double ki_;
  double kd_;

  double total_error_;
  double last_error_;
  double target_;
  double correction_;
  double min_correction_;
  double max_correction_;
  double integral_decay_;
};

#endif /* PID_H */
