/*
  States.h - Library for controlling the state machine

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef StateMachine_h
#define StateMachine_h

#include "Arduino.h"

class StateMachine
{
  public:

    enum ExtruderState {
      SELECT_PROFILE,
      PREHEAT,
      SOAK,
      BEGIN_EXTRUDE,
      LOAD_FILAMENT,
      EXTRUDE,
      TEST,
      CALIBRATE_CALIPERS
    };
    
    StateMachine();//constructor
    ExtruderState getState();
    void setState(ExtruderState state);
    unsigned long getPreheatStartTime();
    void setPreheatStartTime(unsigned long time);
    unsigned long getLoadFilamentStartTime();
    void setLoadFilamentStartTime(unsigned long time);
    unsigned long getExtrudeStartTime();
    void setExtrudeStartTime(unsigned long time);
    
  private:
    ExtruderState _currentState;
    unsigned long _preheatStartTime;
    unsigned long _loadFilamentStartTime;
    unsigned long _extrudeStartTime;

};

#endif
//
//#ifndef States_h
//#define States_h
//
//Finite State Machine for controlling the state of the extruder.
//Names of States
//enum ExtruderState {
//  SELECT_PROFILE,
//  PREHEAT,
//  SOAK,
//  BEGIN_EXTRUDE,
//  LOAD_FILAMENT,
//  EXTRUDE,
//  SAFETY_SHUTDOWN,
//  TEST,
//  CALIBRATE_CALIPERS
//};
//
//ExtruderState currentState;
//
//
//The Time for starting the extrusion global variable
//unsigned long extrudeStartTime;
//unsigned long preheatStartTime;
//unsigned long startLoadFilament;
//#endif
