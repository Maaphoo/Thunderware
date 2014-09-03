/*
  StateMachine.cpp - Library for activating the buzzer which
      signals changes in the extruder's state and safety
      errors. The buzzer pin is 17

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "StateMachine.h"


StateMachine::StateMachine()
{
  currentState = SELECT_PROFILE;
}
 
ExtruderState StateMachine::getState(){return _currentState;}

void StateMachine::setState(ExtruderState state){_currentState = state;}

