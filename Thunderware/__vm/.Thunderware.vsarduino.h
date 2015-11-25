/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega w/ ATmega2560 (Mega 2560), Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define ARDUINO 161
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 161
#define ARDUINO_AVR_MEGA2560
#define ARDUINO_ARCH_AVR
extern "C" void __cxa_pure_virtual() {;}

//
//
void loadDefaultConfig();
void loadConfig();
void saveConfig();
void loadProfile0();
void loadProfile1();
void loadProfile2();
void loadProfile3();
void loadProfile4();
void loadProfile5();
void loadProfile6();
void loadProfile7();
void loadProfile8();
void loadProfile9();
void loadDefaultProfile();
void extrude1();
void saveCurrentProfile();
void resetEEPROM();
void actionExtrude();
void skipPreheat();
void skipSoak();
void exitExtrude();
void exitPreheat();
void exitSoak();
void exitLoadFilament();
void filamentLoaded();
void confirmStopExtruding();
char* makeTimeString(char* str, unsigned long milliseconds);
void starveFeederChangeMode();
void increaseSoakTime();
void decreaseSoakTime();
void loadFilamentAddTime();
void homeStarveFeeder();
void dump();
void feed();
void toggleHeaterState();
void setGramsPerMin();
void loadStarveFeederConfig();
void setAugerRPM();
void setOutfeedRPM();
void setOutfeedTunings();
void baseOutfeedRPMonGPM();

#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include <Thunderware.ino>
#include <Buzzer.cpp>
#include <Buzzer.h>
#include <Caliper.cpp>
#include <Caliper.h>
#include <Configuration.cpp>
#include <Configuration.h>
#include <EEPROMAnything.h>
#include <Extrude.h>
#include <FSM.h>
#include <FastPWM.cpp>
#include <FastPWM.h>
#include <Heater.cpp>
#include <Heater.h>
#include <Key.cpp>
#include <Key.h>
#include <Keypad.cpp>
#include <Keypad.h>
#include <Menu.cpp>
#include <Menu.h>
#include <MenuData.h>
#include <Outfeed.cpp>
#include <Outfeed.h>
#include <PID_v1.cpp>
#include <PID_v1.h>
#include <Preheat.h>
#include <Safety.cpp>
#include <Safety.h>
#include <Spooler.cpp>
#include <Spooler.h>
#include <StarveFeeder.cpp>
#include <StarveFeeder.h>
#include <StepperMotor.cpp>
#include <StepperMotor.h>
#include <Test.h>
#include <TestReporting.h>
#include <Thermistor.cpp>
#include <Thermistor.h>
