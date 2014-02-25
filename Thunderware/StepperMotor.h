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
    enum PinSet {
      SET_3_14_8 = 0,// wired to auger motor, pins: step->3, dir->14, enable->8 
      SET_11_15_12,//wired to outfeed motor, pins: step->11, dir->15, enable->12
      SET_10_16_9,//wired to spool motor, pins: step->10, dir->16, enable->9
      //STARVE_FEEDER,
    };

    StepperMotor(PinSet pinSet, int timerNumber);//constructor
    void setRPM(double rpm);
    float getRPM();
    void disable();
    void enable();

  private:
    FastPWM _timer;
    double _rpm;
    int _ratio;//Stepmode And gear ratio (if it exists)
    PinSet _pinSet;
};

#endif
