#ifndef FSM_h
#define FSM_h

#include "config.h"
#include "StarveFeeder.h"

char diameterString[6];
char *diameterPtr;//pointer to char in diameterString.

void selectProfile(){
  //Display message on LCD and Computer Screen
// initializeLCD();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Select a profile.");
  lcd.setCursor(0,1);
  lcd.write("1: 1.75 ABS");
  lcd.setCursor(0,2);
  lcd.write("2: No Auger");
  lcd.setCursor(0,3);
  lcd.write("3: No Heat");


  Serial.println("Select a profile.");
  Serial.println("1: 1.75 ABS (Default)");
  Serial.println("2: No Auger");
  Serial.println("3: No Heat\n");
  boolean invalid = true;

  while(invalid){
    key = kpd.getKey();

  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }

    if (key == '1' || key == '2' || key == '3' || key == 'D'){
      invalid = false;
    }
  }
  switch(key){
    case '1':
    {

      configuration.loadDefaultProfile();
      currentState = PREHEAT;

    }
      break;

    case '2':
      {
      configuration.loadDefaultProfile();
      
      configuration.profile.barrelTemp = 0;
      configuration.profile.nozzleTemp = 0;
      configuration.profile.augerRPM = 0 ;
      configuration.profile.outfeedRPM = 70;
      configuration.profile.soakTime = 0;
  
      currentState = EXTRUDE;
  
      }
      break;

    case '3':
        //select 1.75 profile No Heat
      configuration.loadDefaultProfile();
      configuration.profile.barrelTemp = 0;
      configuration.profile.nozzleTemp = 0;
      configuration.profile.augerRPM = 38 ;
      configuration.profile.outfeedRPM = 70;
      configuration.profile.soakTime = 0;

        //Shift state.
        currentState = EXTRUDE;
    break;
    
    case 'D':
        currentState = TEST;
        break;
    }
  }



void calibrateCalipers(){
  
  Serial.println("Calibrating Calipers");
  
}




double getNumber(char *title, char *subTitle){
// bool noDecimal = true;
// lcd.clear();
// lcd.write(title);
// lcd.setCursor(0,1);
// lcd.write(subTitle);
// lcd.setCursor(0,3);
// lcd.write("(Esc press <-)");
// lcd.setCursor(0,2);
//
// boolean invalid = true;
// diameterPtr = diameterString;// set pointer to first digit
//
// while (invalid){
// key=kpd.waitForKey();//get user input
//
// switch(key){
//
// case 'D':
// //Check to see that a valid diameter was entered
//
// //return number
// return atof(diameterString);
//
// case 'A': //backspace was pressed so go back.
// if (diameterPtr > diameterString){
// lcd.setCursor(diameterPtr - diameterString - 1,2);
// lcd.write(' ');
// lcd.setCursor(diameterPtr - diameterString - 1,2);
// diameterPtr--;
// if (*diameterPtr == '.'){
// noDecimal = true;
// }
//
// } else {//back space was pressed to exit Custom
// //keep state as selectProfile
// return -1;
// }
//
// case 'B'://invalid do nothing
// break;
//
// case 'C'://invalid do nothing
// break;
//
// case '#'://invalid do nothing
// break;
//
// case '*'://decimal place
// if (diameterPtr - diameterString < 5 && noDecimal == true){ //Make sure that the diameterString isn't full
// *diameterPtr = '.';
// lcd.write('.');
// diameterPtr++;
// noDecimal = false;
// }
// break;
//
// default:
// if (diameterPtr - diameterString < 5){ //Make sure that the diameterString isn't full
// *diameterPtr = key;
// diameterPtr++;
// lcd.write(key);
// }
// }
// }
  return 0.0;
}

#endif // FSM_h



///*
//  FSM.h - Library for the finite state machine that
//  controlls the states of the filament extruder.
// 
// Created by Matthew P. Rogge, Februrary 12, 2014.
// Released into the public domain.
// */
//#ifndef FSM_h
//#define FSM_h
//
//#include "Arduino.h"
//
//#include "Configuration.h"
//
//class Configuration;
//
//class FSM
//{
//public:
//
//  FSM(Configuration* configuration);//constructor
//  //Setup Finite State Machine
//
//
//
//private:
//  //Names of States
//  enum State {
//    SELECT_PROFILE_SETUP,
//    SELECT_PROFILE,
//    CUSTOM_PROFILE,
//    PREHEAT,
//    SOAK,
//    EXTRUDE_MANUAL,
//    EXTRUDE_AUTOMATIC,
//    EXTRUSION_COMPLETE,
//    SAFETY_SHUTDOWN,
//    TEST
//  };
//  
//  State _currentState;
//  void selectProfileSetup();
//  void selectProfile();
//  void customProfile();
//  void preheat();
//  void soak();
//  void extrudeManual();
//  void extrudeAutomatic();
//  void extrudeComplete();
//  void safetyShutdown();
//  void test();
//
////Pointers to State functios
//  void (*state_table[10])();
////  void (*state_table[])()={
////    selectProfileSetup,
////    selectProfile,
////    customProfile,
////    preheat,
////    soak,
////    extrudeManual,
////    extrudeAutomatic,
////    extrudeComplete,
////    safetyShutdown,
////    test
////  };
//  
// Configuration* _configuration;
//
//};
//
//#endif

