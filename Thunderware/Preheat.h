#ifndef Preheat_h
#define Preheat_h

#include "Safety.h"
#include "TestReporting.h"

void displayPreheatScreen();
void displaySoakScreen();
void writeDouble(double val,int decPlaces, int col, int row);
void updateTime(unsigned long milliseconds, int col, int row);

void preheat(){
  static unsigned long now;
  static unsigned long reportTime;
  static unsigned long redrawTime;
  static boolean startFlag = true;//marks first time soak is run
  static boolean msgSet = false;//indicates that the preheat finished buzzer message has been set
  static boolean redrawLCD;

  now = millis();

  if (startFlag){
    lcd.clear();
    reportCurrentMeasurementTitles();

    //start from full power state
    barrel.setDutyCycle(90);
    nozzle.setDutyCycle(255);

    //Then set heater PIDs to automatic
    barrel.setMode(AUTOMATIC);
    nozzle.setMode(AUTOMATIC);
    redrawLCD = true;
    startFlag = false;
  }
  buzzer.activate();
  barrel.activate();
  nozzle.activate();

  if (now >= reportTime){

    //Safety check
    reportCurrentMeasurements();
    if (now>=redrawTime){
      lcd.begin(20,4);
      redrawLCD = true;
      redrawTime += 10000;
    }
    if (redrawLCD){
      displayPreheatScreen();
      redrawLCD = false;
    }

    //update Temps
    writeDouble(barrel.getTemp(),0, 12,2);
    writeDouble(nozzle.getTemp(),0, 12,3);
    reportTime = now+1000L;
  }

  //Now check for user input. 
  key = kpd.getKey();

  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }

  if (key){ 
    redrawLCD = true;
  }// A key was pressed so the screen will have to be redrawn


  switch(key){
  case 'B'://increase Tempature setpoint
    {
      lcd.clear();
      lcd.write("Increase temp to:");
      lcd.setCursor(0,1);
      configuration.profile.barrelTemp = configuration.profile.barrelTemp+5;
      char tempSetPointString[10];
      dtostrf(configuration.profile.barrelTemp, 1,2,tempSetPointString);
      lcd.write(tempSetPointString);

      Serial.print("Increased barrelTemp set point to: ");
      Serial.println(configuration.profile.barrelTemp);
      break;
    }
  case 'C'://decrease temp set point
    {
      lcd.clear();
      lcd.write("Decrease temp to:");
      lcd.setCursor(0,1);
      configuration.profile.barrelTemp = configuration.profile.barrelTemp-5;
      char tempSetPointString[10];
      dtostrf(configuration.profile.barrelTemp, 1,2,tempSetPointString);
      lcd.write(tempSetPointString);

      Serial.print("Decreased temp set point to: ");
      Serial.println(configuration.profile.barrelTemp);

      break;
    }

  case '1'://Skip soaking period
    configuration.profile.barrelTemp = configuration.profile.barrelTemp+5;
    Serial.print("TempSetPoint increased to: ");
    Serial.println(configuration.profile.barrelTemp);

    break;
  case '4':
    configuration.profile.barrelTemp = configuration.profile.barrelTemp-5;
    Serial.print("TempSetPoint decreased to: ");
    Serial.println(configuration.profile.barrelTemp);
    break;

  case'8':
    //     consKp+=.1;
    //      Serial.print("Kp increased to: ");
    //      Serial.println(consKp);
    //      barrelPID.SetTunings(consKp,consKi,consKd);
    break;

  case '0':
    //      consKp-=.1;
    //      Serial.print("Kp decreased to: ");
    //      Serial.println(consKp);
    //      barrelPID.SetTunings(consKp,consKi,consKd);
    break;

  case 'A':
    barrel.off();
    nozzle.off();
    currentState = SELECT_PROFILE;
    return;

  case 'D':
    lcd.begin(20, 4);
    break;

  case '*':
    startFlag = true;//set to reinitialize vars for next preheat
    currentState = SOAK;
    return;
  }


  if (barrel.getTemp() > configuration.profile.barrelTemp-3 && nozzle.getTemp() > configuration.profile.nozzleTemp-3){
    buzzer.setMsg(Buzzer::PREHEAT_FINISHED);
    startFlag = true;//set to reinitialize vars for next preheat
    currentState = SOAK;
  }
}

















//Soak state function
void soak(){
  static unsigned long now;
  static unsigned long startTime;
  static unsigned long extrudeTime;
  static unsigned long reportTime;  
  static unsigned long redrawTime;  
  static boolean startFlag = true;//marks first time soak is run
  static boolean redrawLCD;
  static boolean msgSet = false;//indicates that the end soak buzzer message has been set

  now = millis();

  if (startFlag){
    startTime = now;
    extrudeTime = startTime + configuration.profile.soakTime*60*1000;
    lcd.clear();
    redrawLCD = true;
    startFlag = false;    
  }

  buzzer.activate();
  barrel.activate();
  nozzle.activate();

  //Reporting status during heat up
  if (now >= reportTime){

    //Safety check
    if (heaterError()) {
      return;
    }

    //reportHeaterStatus1();
    reportCurrentMeasurements();
    reportTime = now+1000L;
    if (now>=redrawTime){
      lcd.begin(20,4);
      redrawLCD = true;
      redrawTime += 10000;
    }
    if (redrawLCD){
      displaySoakScreen();
      redrawLCD = false;
    }
    //update time and Temps
    updateTime(extrudeTime-now, 8,0);
    writeDouble(barrel.getTemp(),0, 12,2);
    writeDouble(nozzle.getTemp(),0, 12,3);
  }

  //Check for user input and respond accordingly
  key = kpd.getKey();

  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }

  if (key){ 
    redrawLCD = true;
  }// A key was pressed so the screen will have to be redrawn

  switch(key){
  case 'A':
    barrel.off();
    nozzle.off();
    currentState = SELECT_PROFILE;
    return;

  case 'B'://increase Tempature setpoint
    {
      lcd.clear();
      lcd.write("Increase temp to:");
      lcd.setCursor(0,1);
      configuration.profile.barrelTemp += 5;
      configuration.profile.nozzleTemp += 5;
      char tempSetPointString[10];
      dtostrf(configuration.profile.barrelTemp, 1,2,tempSetPointString);
      lcd.write(tempSetPointString);

      Serial.print("Increased temp set point to: ");
      Serial.println(configuration.profile.barrelTemp);

      break;
    }
  case 'C'://decrease temp set point
    {
      lcd.clear();
      lcd.write("Decrease temp to:");
      lcd.setCursor(0,1);
      configuration.profile.barrelTemp -= 5;
      configuration.profile.nozzleTemp -= 5;
      char tempSetPointString[10];
      dtostrf(configuration.profile.barrelTemp, 1,2,tempSetPointString);
      lcd.write(tempSetPointString);

      Serial.print("Decreased temp set point to: ");
      Serial.println(configuration.profile.barrelTemp);

      break;
    }
  case '*'://Skip soaking period
    {
      lcd.clear();
      lcd.write("Skip Soak?");
      lcd.setCursor(0,1);
      lcd.write("Press * to Skip");
      lcd.setCursor(0,2);
      lcd.write("Press D to continue");
      boolean noInput = true;
      while (noInput){
        barrel.activate();
        key = kpd.getKey();
        //Allow for keyboard input as well
        if (Serial.available() > 0) {
          key = (char)Serial.read();
        }
        if (key == '*'){
          startFlag = true;//set to reinitialize vars on next soak
          currentState = BEGIN_EXTRUDE;
          return;
        }
        if (key == 'D'){
          noInput = false;
        }
      }
      Serial.println("Pressed * or D");
      break;
    }

  case '1'://Increase soak time by 1 min
    lcd.clear();
    lcd.write("Increasing Time");
    extrudeTime = extrudeTime+1000L*60L;

    break;
  case '4'://Decrease soak time by 1 min
    extrudeTime = extrudeTime-1000L*60L;
    lcd.clear();
    lcd.write("Decreasing Time");
    break;

  case '7':

    //       if (barrelPID.GetMode() == MANUAL){
    //        barrelPID.SetMode(AUTOMATIC);
    //        Serial.print("Barrel PID set to Automatic");
    //       }else{
    //        barrelPID.SetMode(MANUAL);
    //        Serial.print("Barrel PID set to Manual");
    //       }

    break;

  case'8':
    //        consKp+=.1;
    //        Serial.print("ConsKp increased to: ");
    //        Serial.println(consKp);
    //        barrelPID.SetTunings(consKp,consKi,consKd);
    break;

  case '0':
    //        consKp-=.1;
    //        Serial.print("ConsKp decreased to: ");
    //        Serial.println(consKp);
    //        barrelPID.SetTunings(consKp,consKi,consKd);
    break;


  case'9':
    //        consKi+=.001;
    //        Serial.print("consKi increased to: ");
    //        Serial.println(consKi);
    //        barrelPID.SetTunings(consKp,consKi,consKd);
    break;

  case '#':
    //        consKi-=.001;
    //        Serial.print("consKi decreased to: ");
    //        Serial.println(consKi);
    //        barrelPID.SetTunings(consKp,consKi,consKd);
    break;

  case 'D':
    lcd.begin(20, 4);
    break;
  }

  if (now>=extrudeTime-5000 && !msgSet){
    buzzer.setMsg(Buzzer::SOAK_FINISHED);
    msgSet = true;
  }

  if (now>=extrudeTime){
    Serial.println("Finished Soaking");
    barrel.off();
    nozzle.off();
    startFlag = true;//set to reinitialize vars on next soak
    currentState = BEGIN_EXTRUDE;
  }
}

void displayPreheatScreen(){
  lcd.clear();

  lcd.write("Preheat:");

  lcd.setCursor(7,1);
  lcd.write("(SP) (ACT)");

  lcd.setCursor(18,2);
  lcd.write("C");
  lcd.setCursor(18,3);
  lcd.write("C");

  lcd.setCursor(0,2);
  lcd.write("Barrel ");
  char tempString[10];
  dtostrf(configuration.profile.barrelTemp, 3,0,tempString);
  lcd.write(tempString);
  writeDouble(barrel.getTemp(),0, 12,2);

  lcd.setCursor(0,3);
  lcd.write("Nozzle ");
  dtostrf(configuration.profile.nozzleTemp, 3,0,tempString);
  lcd.write(tempString);
  writeDouble(barrel.getTemp(),0, 12,3);
}

void writeDouble(double value, int decPlaces, int col, int row) {
  lcd.setCursor(col,row);
  char tempInputString[10];
  dtostrf(value, 3,decPlaces,tempInputString);
  lcd.write(tempInputString);
}

void displaySoakScreen() {
  lcd.clear();
  lcd.write("Soaking: ");

  lcd.setCursor(7,1);
  lcd.write("(SP) (ACT)");

  lcd.setCursor(18,2);
  lcd.write("C");
  lcd.setCursor(18,3);
  lcd.write("C");

  lcd.setCursor(0,2);
  lcd.write("Barrel ");
  char tempString[10];
  dtostrf(configuration.profile.barrelTemp, 3,0,tempString);
  lcd.write(tempString);
  writeDouble(barrel.getTemp(),0, 12,2);

  lcd.setCursor(0,3);
  lcd.write("Nozzle ");
  dtostrf(configuration.profile.nozzleTemp, 3,0,tempString);
  lcd.write(tempString);
  writeDouble(barrel.getTemp(),0, 12,3);
}

void updateTime(unsigned long milliseconds, int col, int row){
  int totalSeconds = milliseconds/1000L;
  int minutes = totalSeconds/60;
  int seconds = totalSeconds%60;
  char minString[3];
  char secString[3];
  dtostrf(minutes, 2,0,minString);
  dtostrf(seconds, 2,0,secString);
  lcd.setCursor(col,row);
  lcd.write(minString);
  lcd.write(":");
  if (seconds<10){
    secString[0] = '0';
  }
  lcd.write(secString);
}

void getPreheatInput(){

}

void getSoakInput(){

}

#endif // Preheat_h

