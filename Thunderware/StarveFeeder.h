/*
  StarveFeeder.h - Library for controlling the the StarveFeeder.
          The StarveFeeder's only electronic component is a stepper motor.
          By modifying the speed of the stepper, the rate of pellet feed
          into the hopper can be changed.
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */
#ifndef StarveFeeder_h
#define StarveFeeder_h

#include "Arduino.h"

#include "Configuration.h"
#include "StepperMotor.h"

class Configuration;
class StepperMotor;

class StarveFeeder
{
public:

  StarveFeeder(Configuration* configuration);
  void setRPM(double rpm);
    double getRPM();
    void disable();
    void enable();
    boolean getState();
    
private:
    StepperMotor _motor;
    boolean _running;
    float* _gramsPerMin;
    float _gramsPerSec;

};

#endif

//#ifndef StarveFeeder_h
//#define StarveFeeder_h
//
//boolean running;
//float gramsPerMin = 7.5;
//float gramsPerSec = (gramsPerMin/60.0);
//unsigned long endTime;
//int stepInterval = 400;
//
//void stepMotor();
//
//
//void initializeStarveFeeder(){
// pinMode(directionPin ,OUTPUT);
// pinMode(enablePin ,OUTPUT);
// pinMode(stepPin ,OUTPUT);
// digitalWrite(directionPin, HIGH);
// digitalWrite(enablePin, HIGH);
//}
//
//void runStarveFeeder(){
////  if (millis()<endTime){
//  stepMotor();
////  } else {
////    running = false;
////    disableStepper(1);
////    disableStepper(2);
////    disableStepper(3);
////    relayOff();
////    nozzleOff();
////    feederOff();
////    currentState = SELECT_PROFILE;
////    return;
////  }
//}
//
//
//void stepMotor(){
//  static unsigned long now;
//  static unsigned long stepTime = 0L;
//  now = micros();
//  if (running && now>= stepTime){
//   PORTL = PORTL | B00001000;
//   PORTL = PORTL & B11110111;
//   stepTime = now + (long)stepInterval;//this won't be accurate b/c now will not always be spaced out by stepInterval
//  }
//}
//
//void feederOn(){
////  endTime = millis()+60000L;
//  running = true;
//  digitalWrite(enablePin, LOW);
//}
//
//void feederOff(){
//  running = false;
//  digitalWrite(enablePin, HIGH);
//}
//
//boolean getFeederState(){
//  return running;
//}
//
//
//float getFeedRate(){
//  return gramsPerMin;
//}
//
//void setFeedRate(float feedRate){
//  gramsPerMin = feedRate;
//  gramsPerSec = (gramsPerMin/60.0);
//}
//
//void increaseFeedRate(){
// stepInterval -= 10;
//}
//
//void decreaseFeedRate(){
// stepInterval += 10;
//}
//
//
//float calcOutfeedRPM(){
// return (gramsPerMin*1.03*1000.0*2.0)/(PI*diaSetPoint*diaSetPoint*ro*PI);
//}
//
//#endif // StarveFeeder_h
