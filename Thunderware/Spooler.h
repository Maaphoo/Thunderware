/*
  Spooler.h - Library for controlling the spooling mechanism. A stepper
      motor turns the spool. Its speed is determined by the geometry
      of the spool, the distance from the center of the spool to the surface
      of the filament and the rate at which filament is being extruded.

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef Spooler_h
#define Spooler_h

#include "Arduino.h"
#include "StepperMotor.h"
#include "Outfeed.h"

class StepperMotor;
class Outfeed;

class Spooler
{
  public:

    Spooler(Configuration* configuration, Outfeed* outfeed);//constructor
	void setConstatns();
    void setRPM();
    float  getRPM();
    void setRPM(float rpm);
    void enable();
    void disable(); 
	void setDirection();
    Outfeed* _outfeed;
    
  private:
    float _motorRPM;
    float _diaSetPoint;
    float _filamentSurfaceRaduis;
    Configuration* _configuration;
    float c1;
    float c2;
    float c3;
    float c4;
    StepperMotor _motor;
	float _prevRPM;


};

#endif
