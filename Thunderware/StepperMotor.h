/*
  StepperMotor.h - Library for controlling the 3 stepper motors
  in the extruder. The motors are driven using a fast PWM signal
  (Timer1, Timer2 and Timer4). PWM is used because angular velocity
  is more important than angular position the PWM signal works well
  and frees up the processor for other jobs.

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#ifndef StepperMotor_h
#define StepperMotor_h

#include "Arduino.h"
#include "FastPWM.h"

class StepperMotor
{
  public:
    enum Motor {
      AUGER = 0,
      OUTFEED,
      SPOOL,
      //STARVE_FEEDER,
    };

    StepperMotor(Motor motor, int timerNumber);//constructor
    void setRPM(double rpm);
    float getRPM();
    void disable();
    void enable();
    Motor _motor;

  private:
    FastPWM _timer;
    double _rpm;
    int _ratio;//Stepmode And gear ratio (if it exists)
};

#endif
