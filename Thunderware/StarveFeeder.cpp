///*
//  StarveFeeder.cpp - Library for controlling the the StarveFeeder.
//          The StarveFeeder's only electronic component is a stepper motor.
//          By modifying the speed of the stepper, the rate of pellet feed
//          into the hopper can be changed.
//      
//  Created by Matthew P. Rogge, Februrary 12, 2014.
//  Released into the public domain.
//*/
//
//#include "Arduino.h"
//#include "StarveFeeder.h"
//
//StarveFeeder::StarveFeeder(Configuration* configuration)
//             : _motor(configuration, configuration->physical.starveFeederPinSet)
//        
//{
//    _gramsPerMin = &configuration->profile.starveFeederTargetFeedRate;
//    _gramsPerSec = (*_gramsPerMin/60.0);
//    _running = false;
//}
//
//
//
//void StarveFeeder::setRPM(double rpm)
//{
//  _motor.setRPM(rpm);
//}
//
//double StarveFeeder::getRPM(){//return _motor.getRPM();}
//
//void StarveFeeder::disable()
//{
////  _motor.disable();
////  _running = false;
//}
//
//void StarveFeeder::enable()
//{
////  _motor.enable();
////  _running = true;
//}
//
//boolean StarveFeeder::getState(){return _running;}
