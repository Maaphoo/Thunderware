#ifndef FSM_h
#define FSM_h

#include "config.h"
#include "StarveFeeder.h"

double getNumber(char *title, char *subTitle);


void selectProfile(){
   //
  //Display message on LCD and Computer Screen
  // initializeLCD();
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.write("Select a profile.");
//  lcd.setCursor(0,1);
//  lcd.write("1: 2.85 ABS");
//  lcd.setCursor(0,2);
//  lcd.write("2: No Auger");
//  lcd.setCursor(0,3);
//  lcd.write("3: No Heat");


  Serial.println(F("Select a profile."));
  Serial.println(F("1: 1.75 ABS (Default)"));
  Serial.println(F("2: No Auger"));
  Serial.println(F("3: No Heat\n"));
  boolean invalid = true;

  while(invalid){
    buzzer.activate();
    key = kpd.getKey();
    
    //Allow for keyboard input as well
    if (Serial.available() > 0) {
      key = (char)Serial.read();
    }

    if (key == '1' || key == '2' || key == '3' || key == '4' || key == 'D'){
      invalid = false;
    }
  }
  switch(key){
  case '1':
    {

      configuration.loadDefaultProfile();
      stateMachine.setState(StateMachine::PREHEAT);

    }
    break;

  case '2':
    {
      configuration.loadDefaultProfile();

      configuration.profile.barrelTemp = 0;
      configuration.profile.nozzleTemp = 0;
      configuration.profile.augerRPM = 0 ;
      configuration.profile.starveFeederRPM = 0;
      configuration.profile.soakTime = 0;

      stateMachine.setState(StateMachine::BEGIN_EXTRUDE);

    }
    break;

  case '3':
    //select 1.75 profile No Heat
    configuration.loadDefaultProfile();
    configuration.profile.barrelTemp = 0;
    configuration.profile.nozzleTemp = 0;
    configuration.profile.soakTime = 0;

    //Shift state.
    stateMachine.setState(StateMachine::BEGIN_EXTRUDE);
    break;

  case '4':
    Serial.println(F("calibrate Calipers"));
    //Shift state.
    stateMachine.setState(StateMachine::CALIBRATE_CALIPERS);
    break;

  case 'D':
    stateMachine.setState(StateMachine::TEST);
    break;
  }
}


void calibrateCalipers(){
  lcd.clear();
  lcd.print(F("Caliper Calibration"));
  Serial.println(F("Caliper Calibration"));
  delay (4000);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(F("Step 1:Load filament"));
  lcd.setCursor(0,1);
  lcd.print(F("with target Diameter"));
  lcd.setCursor(0,3);
  lcd.print(F("Press <enter>"));
  Serial.println(F("Step 1: Load filament with target diameter."));
  
  char key;
  while (1){
    key = kpd.getKey();
  
  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }

    if(key == 'D'){ 
      break;
    }
    if (key == 'A'){
      stateMachine.setState(StateMachine::SELECT_PROFILE);
      return;
    }
  }
  lcd.clear();
  lcd.print(F("Step 2: Adjust the"));
  lcd.setCursor(0,1);
  lcd.write("sensor until it is");
  lcd.setCursor(0,2);
  lcd.write("between 450 and 550.");
  lcd.setCursor(0,3);
  lcd.write("Then press <enter>.");
  Serial.println(F("Step2: Adjust the sensor until it is between 450 and 550."));
  Serial.println(F("Then Press <enter>"));
  delay(4000);
  lcd.clear();

  lcd.write("Sensor Adjust");

  double rawADC;
  while(1){
    rawADC = outfeed.getRawADC();
    lcd.setCursor(7,1);
    writeDouble(rawADC,0,7,1);
    Serial.println(rawADC);
    delay(1000);

    if (rawADC < 550.0 && rawADC > 450.0){
      lcd.setCursor(0,3);
      lcd.write("Press <enter>");
    }

    key = kpd.getKey();
    //Allow for keyboard input as well
    if (Serial.available() > 0) {
      key = (char)Serial.read();
    }
    if( key == 'D' /*&& rawADC < 550.0 && rawADC > 450.0*/  ){ 
      break;
    }
    if (key == 'A'){
      stateMachine.setState(StateMachine::SELECT_PROFILE);
      return;
    }
  }

  lcd.clear();
  lcd.write("Step 3: Load samples");
  lcd.setCursor(0,1);
  lcd.write("with known diameter.");
  lcd.setCursor(0,2);
  lcd.write("Minimum of 3");
  lcd.setCursor(0,3);
  lcd.write("Then record Diameter");
  Serial.println(F("Step 3: Load samples with known Diameter. Minimum of 3. Then Record Diameter."));
  delay(4000);

  key = 0;
  float sampleDias[10];
  float sampleADCs[10];
  int i = 0;
  boolean finished = false;
  while(i<10 || finished){
    lcd.clear();
    lcd.write("Load sample ");
    writeDouble(i+1,0,12,0);

    lcd.setCursor(0,2);
    lcd.write("Press <enter>");
    
    lcd.setCursor(0,3);
    lcd.write("Press 'C' when done");
    Serial.println(F("Load sample then poress 'D'. Press 'C' when Done."));
    while (1){ 
      key = kpd.getKey();

      //Allow for keyboard input as well
      if (Serial.available() > 0) {
      key = (char)Serial.read();
      }

      if(key == 'D'){ 
        break;
      }
      if(key == 'C'){ 
        if (i<2){
          stateMachine.setState(StateMachine::SELECT_PROFILE);
        return;
        }
        finished = true;
        break;
      }
      if (key == 'A'){
        stateMachine.setState(StateMachine::SELECT_PROFILE);
        return;
      }
    }
    if (finished){ break;}
    sampleADCs[i] = outfeed.getRawADC();   

    lcd.clear();
    sampleDias[i] = getNumber("Enter Diameter", "<enter> to exit");
    if (sampleDias[i] == -1){ 
      if (i<2){
        stateMachine.setState(StateMachine::SELECT_PROFILE);
      return;
      }
      break;
    }
    i++;
  }

  outfeed.linReg(&configuration.physical.slope, &configuration.physical.yIntercept, &sampleADCs[0], &sampleDias[0],&i);
  lcd.clear();
  lcd.write("Calibration Complete");
  lcd.setCursor(0,1);
  lcd.write("Slope: ");
  writeDouble(configuration.physical.slope,7,7,1);
  lcd.setCursor(0,2);
  lcd.write("yInt: ");
  writeDouble(configuration.physical.yIntercept,4,7,2);
  lcd.setCursor(0,3);
  lcd.write("Press <enter>");

  while (1){ 
  key = kpd.getKey();
    if(key){ 
      stateMachine.setState(StateMachine::SELECT_PROFILE);
      return;
    }
  }
}




double getNumber(char *title, char *subTitle){
  char diameterString[6];
  char *diameterPtr;//pointer to char in diameterString.
  bool noDecimal = true;
  lcd.clear();
  lcd.write(title);
  lcd.setCursor(0,1);
  lcd.write(subTitle);
  lcd.setCursor(0,3);
  lcd.write("(Esc press <-)");
  lcd.setCursor(0,2);

  boolean invalid = true;
  diameterPtr = diameterString;// set pointer to first digit

  while (invalid){
    key=kpd.waitForKey();//get user input
    
    //Allow for keyboard input as well
    if (Serial.available() > 0) {
      key = (char)Serial.read();
    }
    
    switch(key){

    case 'D':
      //Check to see that a valid diameter was entered
      if (atof(diameterString) == 0.0){
        return -1; 
      }else{
      //return number
      return atof(diameterString);
      }

    case 'A': //backspace was pressed so go back.
      if (diameterPtr > diameterString){
        lcd.setCursor(diameterPtr - diameterString - 1,2);
        lcd.write(' ');
        lcd.setCursor(diameterPtr - diameterString - 1,2);
        diameterPtr--;
        if (*diameterPtr == '.'){
          noDecimal = true;
        }

      } 
      else {//back space was pressed to exit Custom
        //keep state as selectProfile
        return -1;
      }

    case 'B'://invalid do nothing
      break;

    case 'C'://invalid do nothing
      break;

    case '#'://invalid do nothing
      break;

    case '*'://decimal place
    case '.'://decimal place
      if (diameterPtr - diameterString < 5 && noDecimal == true){ //Make sure that the diameterString isn't full
        *diameterPtr = '.';
        lcd.write('.');
        diameterPtr++;
        noDecimal = false;
      }
      break;

    default:
      if (diameterPtr - diameterString < 5){ //Make sure that the diameterString isn't full
        *diameterPtr = key;
        diameterPtr++;
        lcd.write(key);
      }
    }
  }
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


