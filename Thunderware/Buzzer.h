/*
  Buzzer.h - Library for activating the buzzer which
      signals changes in the extruder's state and safety
      errors. The buzzer pin is 17
      
  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"

class Buzzer
{
  public:
    //Messages
    #define NO_MSG 0 // no message
    #define SOAKING 1 //The soak period is starting
    #define EXTRUDING 2 //The machine is extruding
    #define OUT_OF_TOL 3 //The filament is out of tolerance
    #define SAFETY 4 //A safety shutdown has been triggered

    Buzzer();//constructor
    void setMsg(int msg);
    void activate();
    
  private:
    unsigned long _now;
    unsigned long _changeTime; //the time to turn the buzzer on or off
    int _currentMsg;
    static int _messages[5][10];
 
};

#endif
