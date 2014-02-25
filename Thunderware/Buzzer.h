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

    enum Message {
      NO_MSG = 0, // no message
      SOAKING, // The soak period is starting
      EXTRUDING, // The machine is extruding
      OUT_OF_TOL, // The filament is out of tolerance
      SAFETY // A safety shutdown has been triggered
    };

    Buzzer();//constructor
    void setMsg(Message msg);
    void activate();

  private:
    unsigned long _now;
    unsigned long _changeTime; //the time to turn the buzzer on or off
    Message _currentMsg;
    static int _messages[5][10];

};

#endif
