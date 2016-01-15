/*
Thunder Head Filament Extruder Firmware

The Thunder Head extruder is a small scale extruder
that makes 3D printing filament.

Created by Matthew P. Rogge, Februrary 12, 2014.
Released into the public domain.
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <avr/pgmspace.h>
#include <EEPROM.h>
#include "Keypad.h"
#include "PID_v1.h"
#include "EEPROMAnything.h"
#include "Thermistor.h"
#include "Configuration.h"
#include "Buzzer.h"
#include "Heater.h"
#include "StepperMotor.h"
#include "FastPWM.h"
#include "Spooler.h"
#include "StarveFeeder.h"
#include "Caliper.h"
#include "Safety.h"
#include "Menu.h"

Configuration configuration;
#include "menuData.h"




//Setup Finite State Machine
enum ExtruderStates {
	STANDBY,
	BEGIN_PREHEAT,
	PREHEAT,
	BEGIN_SOAK,
	SOAK,
	BEGIN_LOAD_FILAMENT,
	LOAD_FILAMENT,
	BEGIN_EXTRUDE,
	EXTRUDE
} currentState;

void standby();
void beginPreheat();
void preheat();
void beginSoak();
void soak();
void beginLoadFilament();
void loadFilament();
void beginExtrude();
void extrude();

//Pointers to State functios
void (*state_table[])() = {
	standby,
	beginPreheat,
	preheat,
	beginSoak,
	soak,
	beginLoadFilament,
	loadFilament,
	beginExtrude,
	extrude
};

// lcd pins
const byte LCD_RS  = 22;
const byte LCD_EN  = 24;
const byte LCD_D4  = 26;
const byte LCD_D5  = 28;
const byte LCD_D6  = 30;
const byte LCD_D7  = 32;


const byte LCD_ROWS = 4;
const byte LCD_COLS = 20;

//initialize library with LCD interface pins
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//Keypad Rows and Columns
const byte ROWS = 4;
const byte COLS = 4;

//Membrane Kpd initialize keypad pins

byte rowPins[COLS] = {23, 25, 27, 29};
byte colPins[ROWS] = {31, 33, 35, 37};

//Keymap
char keys[ROWS][COLS] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};


Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char key;//The key that is pressed

//Initialize objects
//StateMachine stateMachine;



Buzzer buzzer;

StarveFeeder starveFeeder(&configuration);

Heater zone1(&configuration.physical.zone1);
Heater zone2(&configuration.physical.zone2);
Heater zone3(&configuration.physical.zone3);
Heater zone4(&configuration.physical.zone4);


StepperMotor auger(&configuration, configuration.physical.augerPinSet);

Outfeed outfeed(&configuration);

Spooler spooler(&configuration);

Safety safety(&configuration);

Menu mainMenu(mainItems, sizeof(mainItems) / sizeof(mainItems[0]), &lcd, &kpd);
Menu preheatMenu(preheatItems, sizeof(preheatItems) / sizeof(preheatItems[0]), &lcd, &kpd);
Menu soakMenu(soakItems, sizeof(soakItems) / sizeof(soakItems[0]), &lcd, &kpd);
Menu loadFilamentMenu(loadFilamentItems, sizeof(loadFilamentItems) / sizeof(loadFilamentItems[0]), &lcd, &kpd);
Menu extrudeMenu(extrudeItems, sizeof(extrudeItems) / sizeof(extrudeItems[0]), &lcd, &kpd);
Menu* activeMenu;



#include "Extrude.h"
#include "FSM.h"
#include "Preheat.h"
#include "Safety.h"
#include "TestReporting.h"

void setup()
{

	Serial.begin(115200);
	while (!Serial); // while the serial stream is not open, do nothing:
	Wire.begin();
	lcd.begin(20, 4); //Start up LCD
	lcd.clear();
	activeMenu = &mainMenu;
	buzzer.setMsg(Buzzer::POWER_ON);
	currentState = STANDBY;
	auger.disable(); // Why is this necessary. If not here, there is high frequency signal on the auger step pin.
	configuration.loadConfig();
	//starveFeeder.getMode(starveFeederMode);
	//  activeMenu = &loadFilamentMenu;
	activeMenu->reset();
	Serial.print("configuration.physical.slope: ");
	Serial.println(configuration.physical.slope,6);
	Serial.print("configuration.physical.yIntercept: ");
Serial.println(configuration.physical.yIntercept,4);}
static unsigned long refreshDisplayTime;

void loop() {
	static unsigned long now;
	
	//Allow for keyboard input as well
	key = kpd.getKey();
	if (Serial.available() > 0) {
		key = (char)Serial.read();
	}

	//  if (key) {
	//    Serial.print("freeMemory()=");
	//    Serial.println(freeMemory());
	//  }

	switch (key) {
		case 'A':
		case 'q':
		activeMenu->up();
		break;
		case 'B':
		case 'w':
		activeMenu->down();
		break;
		case 'C':
		case 'e':
		activeMenu->select();
		break;
		case 'D':
		case 'r':
		activeMenu->back();
		break;

		case '1':
		activeMenu->increase();
		break;

		case '4':
		activeMenu->decrease();
		break;

		case '*':
		lcd.begin(20,4);
		activeMenu->display();
		break;
	}
	state_table[currentState]();
	
	//Activate the heaters for testing
	zone1.activate();
	zone2.activate();
	zone3.activate();
	zone4.activate();
	
	now = millis();
	if (now >= refreshDisplayTime){
		//update display variables
		//Temps
		zone1Temp = zone1.getTemp();
		zone2Temp = zone2.getTemp();
		zone3Temp = zone3.getTemp();
		zone4Temp = zone4.getTemp();

		//diameter
		//diameter = outfeed.getDia();
		Serial.println(spooler.getRawADC());

		//soakTime remaining
		if (currentState == SOAK){
			makeTimeString(soakTimeRemaining,soakEndTime-millis());
		}

		//load filament Time
		if (currentState == LOAD_FILAMENT){
			makeTimeString(loadFilamentTimeRemaining,loadFilamentEndTime-millis());
		}
		refreshDisplayTime= millis()+1000L;

		activeMenu->display();
		//output all data on serial monitor
		//   reportCurrentMeasurements();
	}
}



//Wrapper functions for menu items whos actions are member fucntions of other classes

void loadDefaultConfig() {
	configuration.loadDefaultConfig();
	lcd.clear();
	lcd.print(F("Configuration Loaded"));
	delay(2000);
	mainMenu.display();
}

void loadConfig() {
	lcd.clear();
	lcd.print(F("Loading..."));
	delay(500);
	configuration.loadConfig();
	lcd.clear();
	lcd.print(F("Configuration Loaded"));
	delay(2000);
	mainMenu.display();
}

void saveConfig() {
	lcd.clear();
	lcd.print(F("Saving..."));
	delay(500);
	configuration.saveConfig();
	lcd.clear();
	lcd.print(F("Configuration Saved"));
	delay(2000);
	mainMenu.display();
}


void loadProfile0() {
	configuration.loadProfile(0);
}
void loadProfile1() {
	configuration.loadProfile(1);
}
void loadProfile2() {
	configuration.loadProfile(2);
}
void loadProfile3() {
	configuration.loadProfile(3);
}
void loadProfile4() {
	configuration.loadProfile(4);
}
void loadProfile5() {
	configuration.loadProfile(5);
}
void loadProfile6() {
	configuration.loadProfile(6);
}
void loadProfile7() {
	configuration.loadProfile(7);
}
void loadProfile8() {
	configuration.loadProfile(8);
}
void loadProfile9() {
	configuration.loadProfile(9);
}

void loadDefaultProfile() {
	configuration.loadDefaultProfile();
}
void extrude1() {

}


void saveCurrentProfile() {
	Serial.print(F("Saving Settings for profile number: "));
	Serial.println(configuration.profile.profileNumber);
	lcd.clear();
	lcd.print(F("Saving profile..."));
	configuration.saveProfile();
	delay(500);
	lcd.clear();
	lcd.print(F("Profile Saved"));
	delay(2000);
}

void resetEEPROM() {
	Serial.println(F("WARNING: This action will overwirte all stored profiles with the default Settings."));
	lcd.clear();
	lcd.print(F("WARNING: This action"));
	lcd.setCursor(0,1);
	lcd.print(F("will overwrite all "));
	lcd.setCursor(0,2);
	lcd.print(F("stored profiles with"));
	lcd.setCursor(0,3);
	lcd.print(F("the default settings"));
	delay (5000);
	lcd.clear();
	lcd.print(F("Would you like to proceed?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));

	boolean waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			Serial.println(F("Resetting the EEPROM..."));
			lcd.clear();
			lcd.print(F("Resetting EEPROM..."));
			configuration.loadDefaultConfig();
			configuration.saveConfig();
			configuration.loadDefaultProfile();
			for (int i = 0; i < 10; i++) {
				configuration.profile.profileNumber = i;
				//        selectProfileMenu[i].setText(configuration.profileNames[i]);//The names have been reset. This will reflect the change
				configuration.saveProfile();
			}
			waitForResponse = false;
		}

		if (key == 'B') {
			waitForResponse = false;
		}
	}

	mainMenu.display();
}

void actionExtrude() {
	currentState = BEGIN_PREHEAT;
	activeMenu = &preheatMenu;
	activeMenu->reset();
}

void skipPreheat() {
	currentState = BEGIN_SOAK;
	activeMenu = &soakMenu;
	activeMenu->reset();
}
void skipSoak() {
	currentState = BEGIN_LOAD_FILAMENT;
	activeMenu = &loadFilamentMenu;
	currentState = BEGIN_EXTRUDE;
	activeMenu = &extrudeMenu;
	activeMenu->reset();
}

void exitExtrude() {
	confirmStopExtruding();
}
void exitPreheat() {
	confirmStopExtruding();
}
void exitSoak() {
	confirmStopExtruding();
}
void exitLoadFilament() {
	confirmStopExtruding();
}

void filamentLoaded() {
	currentState = BEGIN_EXTRUDE;
	activeMenu = &extrudeMenu;
	activeMenu->reset();
}

void confirmStopExtruding() {
	lcd.clear();
	lcd.print(F("Stop Extruding?"));
	lcd.setCursor(0, 1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0, 2);
	lcd.print(F("B) No"));
	boolean waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'y' || key == 'A') {
			//Shut everything down here


			//Shut everything off
			auger.disable();
			outfeed.disable();
			starveFeeder.off();
			zone1.off();
			zone2.off();
			zone3.off();
			zone4.off();
			spooler.disable();

			//change the state to standby
			currentState = STANDBY;

			//reactivate the mainMenu
			activeMenu = &mainMenu;
			waitForResponse = false;
		}

		if (key == 'n' || key == 'B') {
			//do nothing
			waitForResponse = false;
		}
	}
}

char* makeTimeString(char* str, unsigned long milliseconds) {
	int totalSeconds = milliseconds / 1000L;
	int minutes = totalSeconds / 60;
	int seconds = totalSeconds % 60;
	char minString[3];
	char secString[3];
	dtostrf(minutes, 2, 0, minString);
	dtostrf(seconds, 2, 0, secString);
	strcpy(str, minString);
	char* strPtr = str;
	//go to end of string
	while (*strPtr)strPtr++;
	*strPtr = ':';
	strPtr++;
	if (seconds < 10) {
		secString[0] = '0';
	}
	int i = 0;
	while (secString[i]) {
		*strPtr = secString[i];
		strPtr++;
		i++;
	}
	return str;
}

void standby() {}


void starveFeederChangeMode() {
	starveFeeder.changeMode();
	starveFeeder.getMode(starveFeederMode);
	Serial.println("");
	Serial.print("Changing mode to: ");
	Serial.println(starveFeederMode);
	Serial.println("");
}

void increaseSoakTime() {
	soakEndTime += 60000L;;
}
void decreaseSoakTime() {
	soakEndTime -= 60000L;
}

void loadFilamentAddTime() {
	loadFilamentEndTime += 60000L;
}

void homeStarveFeeder(){
	starveFeeder.loadConfig();
	starveFeeder.home();
};

void dump(){
	starveFeeder.dump();
}

void feed(){
	starveFeeder.feed();
	if (starveFeeder._feeding){
		strcpy(feedMode, "On");
		} else {
		strcpy(feedMode, "Off");
	}
}

void toggleHeaterState(){
	if (heaterState[1] == 'f'){
		strcpy(heaterState, "On");
		zone1.setMode(AUTOMATIC);
		zone2.setMode(AUTOMATIC);
		zone3.setMode(AUTOMATIC);
		zone4.setMode(AUTOMATIC);
		}else{
		strcpy(heaterState,"Off");
		zone1.setMode(MANUAL);
		zone2.setMode(MANUAL);
		zone3.setMode(MANUAL);
		zone4.setMode(MANUAL);
		zone1.setDutyCycle(0);
		zone2.setDutyCycle(0);
		zone3.setDutyCycle(0);
		zone4.setDutyCycle(0);
	}
	activeMenu->display();
}

void setGramsPerMin(){
	starveFeeder.setGPM(configuration.profile.gramsPerMin);
}

void loadStarveFeederConfig(){
	starveFeeder.loadConfig();
}

void setAugerRPM(){
	auger.setRPM(configuration.profile.augerRPM);
}

void setOutfeedRPM(){
	outfeed.enable();
	outfeed.setRPM(configuration.profile.outfeedRPM);
}

void setOutfeedTunings(){
	outfeed.setTunings();
}

void baseOutfeedRPMonGPM(){
	//(g/min)*(1/density)*(127.32/D^2)*(1Rev/Pi*D) or (Gpm*40.528/(Density*Dia*Dia*DiaRoller)
	float cm3PerMin = configuration.profile.gramsPerMin/configuration.profile.density;
	float cmPerMin = cm3PerMin*400/(3.14159*configuration.profile.diaSetPoint*configuration.profile.diaSetPoint);
	float revPerMin = cmPerMin*10/(2*3.14159*configuration.physical.outfeedRollerRadius);
	configuration.profile.outfeedRPM = revPerMin;
	outfeed.setRPM(revPerMin);
}


void toggleOutfeedState(){
	if (outfeedState[1] == 'f'){
		strcpy(outfeedState, "On");
		outfeed.setRPM(outfeedRPM);
		outfeed.enable();
		}else{
		strcpy(outfeedState,"Off");
		outfeed.disable();
	}
	activeMenu->display();
}

void sendOneRevToOutfeed(){
	outfeed.enable();
	for (int i=0; i<200*16;i++){
		digitalWrite(11, HIGH);
		delayMicroseconds(1000);
		digitalWrite(11,LOW);
		delayMicroseconds(1000);
	}
	outfeed.disable();
	activeMenu->display();
}

void setZone1Temp(){
	configuration.physical.zone1.setTemp = configuration.profile.zone1SetTemp;
}
void setZone2Temp(){
	configuration.physical.zone2.setTemp = configuration.profile.zone2SetTemp;
}
void setZone3Temp(){
	configuration.physical.zone3.setTemp = configuration.profile.zone3SetTemp;
}
void setZone4Temp(){
	configuration.physical.zone4.setTemp = configuration.profile.zone4SetTemp;
}

void measureFilament(){
	unsigned long now = millis();
	unsigned long displayTime = millis();
	lcd.clear();
        configuration.loadDefaultProfile();
	outfeed.loadPIDSettings();
	outfeed.setRPM(10);
	spooler.setRPM();
	outfeed.enable();
//        Serial.print("outfeed RPM: ");
//	Serial.println(outfeed.getRPM());
//        delay(3000);
//	outfeed.setRPM(5);
//        Serial.print("outfeed RPM: ");
//	Serial.println(outfeed.getRPM());
//        delay(3000);
//	outfeed.setRPM(10);
        spooler.enable();
        outfeed.reset();
	outfeed.setMode(AUTOMATIC);
	
	while (true){
		
		//Stop is there is any serial input
		if (Serial.available() > 0) {
			outfeed.disable();
			spooler.disable();
			activeMenu->display();
			return;
		}
		
		now = millis();
		outfeed.activate();
		spooler.setRPM();
		if (now>=displayTime){
			
			Serial.print(outfeed.getRawADC(1));
			Serial.print(", ");
			Serial.print(1024.0-outfeed.getRawADC(2));
			Serial.print(", ");
			Serial.print(outfeed.getDia());
			Serial.print(", ");
			Serial.print(outfeed.getRPM());
			Serial.print(", ");
			Serial.println(outfeed.getMPerMin());

			displayTime = now+500;
		}
	}
	
}
#include "test.h"

