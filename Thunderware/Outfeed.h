/*
  Outfeed.h - Library for activating the the barrel heater.
          The barrel heater is a 120 v 130 w heating element powered
          by an electro-mechanical relay. The relay coil is optically 
          isolated from the logic circuits and is activated by pin 7.
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef Outfeed_h
#define Outfeed_h

#include "Arduino.h"
//#include "config.h"
#include "Configuration.h"
#include "StepperMotor.h"
#include "Caliper.h"
#include "PID_v1.h"

class Configuration;
class StepperMotor;
class Caliper;
class PID;

class Outfeed
{
  public:

    Outfeed(Configuration* configuration);//constructor
    float getRPM();
    void setRPM(float rpm);
    void setMode(int mode);
    int getMode();
    void setTunings();
    double getKp();
    void setKp(double kp);
    double getKi();
    void setKi(double ki);
    double getKd();
    void setKd(double kd);
    void disable();
    void enable();
    void reset();
    float getMmExtruded();
    double getMPerMin();
    double getFtPerMin();
    double getDia();
    double getRawADC(int caliperNum);
    void linReg(float slopeAndIntercept[], float *xVals, float *yVals, int *n);
    void activate();
	void setDirection();
    
  private:
    Configuration* _configuration;
    StepperMotor   _motor;
    Caliper        _caliper2;
    Caliper        _caliper1;
    PID            _pid;
    double _rpm;
    int* _computeInterval;
    unsigned long _computeTime;
    float _mmExtruded;
    unsigned long _now;
    unsigned long _previousTime;

};

#endif
