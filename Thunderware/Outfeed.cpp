/*
Outfeed.cpp - Library for controlling the outfeed process.
It consists of a PID controller, DiameterSensor, and a
StepperMotor.

Created by Matthew P. Rogge, Februrary 12, 2014.
Released into the public domain.
*/

#include "Arduino.h"
#include "Outfeed.h"

Outfeed::Outfeed(Configuration* configuration)
  :  _motor(configuration, configuration->physical.outfeedPinSet),
     _bigWheelMotor(configuration, 2),
     _caliper2(configuration, 4),
     _caliper1(configuration, 3),
     _pid(&_caliper1.rawADC,
          &_motor._rpm,
          &configuration->profile.diaSetPoint,
          configuration->profile.outfeedKp,
          configuration->profile.outfeedKi,
          configuration->profile.outfeedKd,
          REVERSE)

{
  _configuration = configuration;
  _computeInterval = &configuration->profile.outfeedComputeInterval;
}


//revise so that the outfeed reports mm/s
float Outfeed::getRPM() {
  return _motor.getRPM();
}

double Outfeed::getDia() {
  _caliper2.update();
  return _caliper2.dia;
}

double Outfeed::getRawADC(int sensorNum) {
  switch (sensorNum) {
    case 1:
      return _caliper1.getRawADC();
    case 2:
      return _caliper2.getRawADC();
  }
}

void Outfeed::linReg(float slopeAndIntercept[], float *xVals, float *yVals, int *n)
{
  _caliper2.linReg(slopeAndIntercept, xVals, yVals, n);
}

void Outfeed::setRPM(float rpm)
{
  _motor._rpm = rpm;
  _motor.setRPM(rpm);
  float outfeedDia = 72.28;
//  float bigWheelRollerDia = 20.25; 
  _bigWheelMotor.setRPM(rpm*outfeedDia/_configuration->physical.spoolerDiskRadius);
}

void Outfeed::setMode(int mode) {
  _pid.SetTunings(_configuration->profile.outfeedKp, _configuration->profile.outfeedKi, _configuration->profile.outfeedKd);
  _pid.SetMode(mode);
}

int Outfeed::getMode() {
  return _pid.GetMode();
}

void Outfeed::setTunings() {
  _pid.SetTunings(_configuration->profile.outfeedKp,
                  _configuration->profile.outfeedKi,
                  _configuration->profile.outfeedKd);
}

double Outfeed::getKp() {
  return _pid.GetKp();
}

void Outfeed::setKp(double kp) {
  _pid.SetTunings(kp, _pid.GetKi(), _pid.GetKd());
}

double Outfeed::getKi() {
  return _pid.GetKi();
}

void Outfeed::setKi(double ki) {
  _pid.SetTunings(_pid.GetKp(), ki, _pid.GetKd());
}

double Outfeed::getKd() {
  return _pid.GetKd();
}

void Outfeed::setKd(double kd) {
  _pid.SetTunings(_pid.GetKp(), _pid.GetKi(), kd);
}

void Outfeed::loadPIDSettings() {
  _pid.SetOutputLimits(_configuration->profile.outfeedMinRPM, _configuration->profile.outfeedMaxRPM);
  _pid.SetTunings(_configuration->profile.outfeedKp, _configuration->profile.outfeedKi, _configuration->profile.outfeedKd);
  _pid.SetControllerDirection(REVERSE);
  _pid.SetSampleTime(_configuration->profile.outfeedComputeInterval);
}

void Outfeed::disable() {
  _motor.disable();
  _bigWheelMotor.disable();
}

void Outfeed::enable() {
  _motor.enable();
  _bigWheelMotor.enable();
}

float Outfeed::getMmExtruded()
{
  return _mmExtruded;
}

double Outfeed::getMPerMin()
{
  return getRPM() * 2.0 * PI * _configuration->physical.outfeedRollerRadius * 0.001;
}

double Outfeed::getFtPerMin()
{
  return getRPM() * 2.0 * PI * _configuration->physical.outfeedRollerRadius * 0.00328;
}

void Outfeed::reset()
{
  _mmExtruded = 0.0;
  _previousTime = millis();
}

//Idea: set update to call sample until a sample is ready. Reset sampleNum after the pid is computed
// put the mmExtruded into the compute time part. So then update can be called as rapidly as possible
void Outfeed::activate()
{
  _now = millis();

  if (_now >= _computeTime) {
    _mmExtruded += _configuration->physical.outfeedRollerRadius * _motor.getRPM() * 2.0 * PI / 60.0 * (_now - _previousTime) / 1000.0;
    _caliper1.update();
    _caliper2.update();
    if (_pid.GetMode() == AUTOMATIC) {
      _pid.Compute();
      _motor.setRPM(_motor._rpm);
    } else if (reduceSpeedFlag && _now >= reduceSpeedTime) {
      reduceSpeedTime += 1000;
      _motor.setRPM(_motor._rpm - (_configuration->profile.outfeedInitialRPM - _configuration->profile.outfeedRPM) / 60);
      if (_motor._rpm <  61.0 / 60.0 * _configuration->profile.outfeedRPM) {
        _motor.setRPM (_configuration->profile.outfeedRPM);
        reduceSpeedFlag = false;
      }
    }
    _computeTime = _now + (long) * _computeInterval;
  }
  _previousTime = _now;
}

void Outfeed::setDirection() {
  _motor.setDirection();
}

void Outfeed::reduceSpeed() {
  if (reduceSpeedFlag == false) {
    reduceSpeedFlag = true;
    reduceSpeedTime = millis();
  } else {
    reduceSpeedFlag = false;
  }
}


