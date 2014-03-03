/*
 UI.h - Library for managing the user interface
 of the Thunderhead filament Extruder.
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */
#ifndef UI_H
#define UI_h

#include "Arduino.h"
#include "OMMenuMgr.h"
#include <Keypad.h>
#include <LiquidCrystal.h>
#include "Configuration.h"


class OMMenuMgr;
class Configuration;
class Keypad;
class LiquidCrystal;


class UI
{
public:
	
    UI(Configuration* config, Keypad* kpd, LiquidCrystal* lcd);//constructor

private:
	
	Configuration*	_config;
	Keypad*		_kpd;
	LiquidCrystal*	_lcd;
	
	
	
	
};

#endif
