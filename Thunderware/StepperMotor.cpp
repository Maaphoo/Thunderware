/*
  StepperMotor.h - Library for controlling the 3 stepper motors
  in the extruder. The motors are driven using a fast PWM signal
  (Timer1, Timer2 and Timer4). PWM is used because angular velocity
  is more important than angular position the PWM signal works well
  and frees up the processor for other jobs.

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "StepperMotor.h"
#include "config.h"

StepperMotor::StepperMotor(PinSet pinSet, int timerNumber) : _timer(timerNumber)
{
  _pinSet = pinSet;
  //Set Direction, Step and Enable pins to output
  switch (_pinSet){
    case SET_3_14_8:
      _ratio = augerStepMode*gearRatio;

      DDRJ |= B00000010; //Direction, Pin 14 to output
      DDRH |= B00100000; // Enable pin 8 to output
      DDRH |= B00010000;//Step pin 3 to output

      //set Auger Stepper direction (pin 14)
      if (augerDir){
        PORTJ |= B00000010;// Direction is forward so set the pin HIGH
      }else{
        PORTJ &= B11111101; // Direction is Backward so set the pin LOW
      }

      break;

    case SET_11_15_12:
      _ratio = outfeedStepMode;

      DDRJ |= B00000001; //Direction, pin 15 to output
      DDRB |= B01000000; //Enable, pin 12 to output
      DDRB |= B00100000; //Step, pin 11 to output

      //set outfeed Stepper direction (pin 15)
      if (outfeedDir){
        PORTJ |= B00000001;// Direction is forward so set the pin HIGH
      }else{
        PORTJ &= B11111110; // Direction is backward so set the pin LOW
      }

      break;

    case SET_10_16_9:
        _ratio = spoolStepMode;

      DDRH |= B00000010; //Direction, pin 16 to output
      DDRH |= B01000000; //Enable, pin 9 to output
      DDRB |= B00010000;//Step, pin 10 to output

      //set spool Stepper direction pin (pin 16)
      if (spoolDir){
        PORTH = PORTH | B00000010;// Direction is backward so set the pin HIGH
      }else{
        PORTH = PORTH & B11111101; // Direction is forward so set the pin LOW
      }

      break;
  }
 }

void StepperMotor::setRPM(double RPM){
  _rpm = RPM;
  float freq = RPM/60.0*200.0*(float)_ratio;
  _timer.setFrequency(freq);
}

float StepperMotor::getRPM(){return _rpm;}


 //The following should be done before Setting the Spool RPM

   //Make sure the spoolRPM is updated
//   calcSpoolRPM();

void StepperMotor::enable() {
  switch (_pinSet){
    case SET_3_14_8:
      //Auger Stepper pin 8
      //disable is backwards for the KL stepper driver being used. Set HIGH
      PORTH &= B11011111;
      break;

    case SET_11_15_12:
      //Outfeed Stepper pin 12
      //disable outfeed stepper by setting the enable pin Low
      PORTB |= B01000000;
      break;

    case SET_10_16_9:
       //Spool Stepper pin 9
       //disable Spool stepper by setting the enable pin low
       PORTH |= B01000000;
       break;
  }
}

void StepperMotor::disable() {
  switch (_pinSet){
    case SET_3_14_8:
      //Auger Stepper pin 8
      //disable is backwards for the KL stepper driver being used. Set HIGH
      PORTH |= B00100000;
      break;

    case SET_11_15_12:
      //Outfeed Stepper pin 12
      //disable outfeed stepper by setting the enable pin Low
      PORTB &= B10111111;
      break;

    case SET_10_16_9:
       //Spool Stepper pin 9
       //disable Spool stepper by setting the enable pin low
       PORTH &= B10111111;
       break;
  }
}

