#include "PID.h"

#include <algorithm>
#include <iostream>

PID::PID(double kp,
         double ki,
         double kd,
         double target,
         double min_correction,
         double max_correction,
         double integral_decay)
    : kp_(kp),
      ki_(ki),
      kd_(kd),
      total_error_(0.0),
      last_error_(0.0),
      target_(target),
      correction_(0.0),
      min_correction_(min_correction),
      max_correction_(max_correction),
      integral_decay_(integral_decay) {}

void PID::Report(double observed) {
  double error = target_ - observed;
  double delta_error = error - last_error_;
  total_error_ = integral_decay_ * total_error_ + error;
  last_error_ = error;
  // PID correction.
  correction_ = kp_ * error + ki_ * total_error_ + kd_ * delta_error;
  // Bound correction value.
  correction_ = std::min(max_correction_, std::max(min_correction_, correction_));
}

double PID::Correction() {
  return correction_;
}
