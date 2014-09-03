
#ifndef Extrude_h
#define Extrude_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void displayExtrudeScreen();
void printDiameter(int col, int row);
void printFtPerMin(int col, int row);
void stopExtruding();


//setup for extruding
void beginExtrude(){
  static boolean startFlag = true;
  static unsigned long accelerateTime;
  static float augerRPMTmp;
  static int i;

  if (startFlag){
    augerRPMTmp = configuration.profile.augerRPM;
    i = 1;
    lcd.clear();
    // Reset the outfeed mmExtruded and Spool quanitiy
    outfeed.reset();

    //For testing serial print the titles of the recorded Data
    reportCurrentMeasurementTitles();

    //if the auger will be rotating, check the temp before accelerating
    //if it isn't going to rotate skip straight to extrude
    if (configuration.profile.augerRPM > 0.0){
      if (barrel.getTemp()< 0){//Cant run the auger if the barrel isn't hot;
        startFlag = true;
        buzzer.setMsg(Buzzer::SAFETY);
          stateMachine.setState(StateMachine::SELECT_PROFILE);
        return;
      }
      else{
        auger.enable();
        startFlag = false;
        accelerateTime = millis()+5;
        lcd.clear();
        lcd.write("Starting to Extrude");
      }
    }
    else{
      outfeed.setRPM(configuration.profile.outfeedRPM);
      outfeed.enable();
      spooler.enable();
      starveFeeder.setRPM(configuration.profile.starveFeederRPM);
      starveFeeder.enable();
      startFlag = true;
      stateMachine.setExtrudeStartTime(millis());
      stateMachine.setState(StateMachine::EXTRUDE);
      return;
    }
  }

  if (millis() >= accelerateTime){
    //Accelerate Auger

    barrel.activate();
    nozzle.activate();

    auger.setRPM(augerRPMTmp/400.0*(double)i);
    i++;
    accelerateTime +=5;
  }

  if (i>400){
    outfeed.setRPM(configuration.profile.outfeedRPM);
    outfeed.enable();
    outfeed.setMode(MANUAL);
    spooler.enable();
    starveFeeder.setRPM(configuration.profile.starveFeederRPM);
    startFlag = true;
    stateMachine.setExtrudeStartTime(millis());
    stateMachine.setState(StateMachine::EXTRUDE);
  }
}


//State during which the filament is fed through the optical calipers, outfeed and spool
void loadFilament(){
  
}











//Extrude function
void extrude(){
  static unsigned long now;
  static unsigned long reportTime;
  static unsigned long redrawTime;
  static unsigned long startTime;
  static boolean redrawLCD = true;
  static boolean startFlag = true;//marks first time soak is run

  now = millis();
  
//Uncomment the following for testing the starve feeder. 
//This should be rewritten into it's own state.
//  if (now > extrudeStartTime + 1000*60*2){ 
//    auger.disable();
//    outfeed.disable();
//    spooler.disable();
//    barrel.off();
//    nozzle.off();
//    starveFeeder.disable();
//    startFlag = true;//reset start flag so that vars are re initialized if extrude is re entered.
//    currentState = SELECT_PROFILE;
//    return;
//  }

  
  if (startFlag){
    reportTime = now;
    startTime = now;
    redrawLCD = true;
    startFlag = false;
  }
//  if (now-startTime >=60000){
//    stopExtruding();
//    startFlag = true;
//    currentState = SELECT_PROFILE;  
//  }
  //turn relay on or off (or neither)
  barrel.activate();
  nozzle.activate();
  outfeed.activate();

  //report sensor data
  if (now >= reportTime){

    //Safety check
    // if (heaterError()) {return;}
    spooler.setRPM();
    if (now>=redrawTime){
      lcd.begin(20,4);
      redrawLCD = true;
      redrawTime += 1000;
    }
    if (redrawLCD){
      displayExtrudeScreen();
      redrawLCD = false;
    }

    //update temp dia and rate
    writeDouble(nozzle.getTemp(),0, 7,1);
    writeDouble(outfeed.getDia(),2, 7,2);
    writeDouble(outfeed.getMPerMin(),2, 7,3);

    reportCurrentMeasurements();

    reportTime += 1000;
  }




  //now check for user input and respond accordingly
  key = kpd.getKey();

  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }

  if (key){
    redrawLCD = true;
  }

  switch(key){
  case '*':// Automatic or manual
    if (outfeed.getMode() == MANUAL){
      outfeed.setMode(AUTOMATIC);
    } 
    else {
      outfeed.setMode(MANUAL);
    }
    break;

  case '1'://increase Auger
    {
      auger.setRPM(auger.getRPM()+1);
      lcd.clear();
      lcd.write("Increase Auger to:");
      lcd.setCursor(0,1);
      char augerRPMString[10];
      dtostrf(auger.getRPM(), 1,2,augerRPMString);
      lcd.write(augerRPMString);

      //Serial.print("Increased Auger RPM to: ");
      //Serial.println(augerRPM);

      break;
    }
  case '4'://decrease Auger
    {
      auger.setRPM(auger.getRPM()-1);

      //Notify on LCD
      lcd.clear();
      lcd.write("Decrease Auger to:");
      lcd.setCursor(0,1);
      char augerRPMString[10];
      dtostrf(auger.getRPM(), 1,2,augerRPMString);
      lcd.write(augerRPMString);

      //Notify on computer
      //Serial.print("Decreased Auger RPM to: ");
      //Serial.println(augerRPM);

      break;
    }

  case '2'://increase outfeed RPM
    {
      outfeed.setRPM(outfeed.getRPM()+1);

      //Notify on LCD
      lcd.clear();
      lcd.write("Increase outfeed to:");
      lcd.setCursor(0,1);
      outfeed.setRPM(outfeed.getRPM()*1.02);
      char outfeedRPMString[10];
      dtostrf(outfeed.getRPM(), 1,2,outfeedRPMString);
      lcd.write(outfeedRPMString);

      //Notify on Computer screen
      //Serial.print("Increased outfeed RPM to: ");
      //Serial.println(outfeedRPM);

      break;
    }
  case '5'://decrease outfeed RPM
    {
      outfeed.setRPM(outfeed.getRPM()-1);

      //Notify on LCD
      lcd.clear();
      lcd.write("Decrease outfeed to:");
      lcd.setCursor(0,1);
      outfeed.setRPM(outfeed.getRPM()*.98);
      char outfeedRPMString[10];
      dtostrf(outfeed.getRPM(), 1,2,outfeedRPMString);
      lcd.write(outfeedRPMString);

      //Notify on computer
      //Serial.print("Decreased outfeed RPM to: ");
      //Serial.println(outfeedRPM);

      break;
    }

  case '3'://increase starveFeeder RPM
    {
      starveFeeder.setRPM(starveFeeder.getRPM()+1.0);
      break;
    }
  case '6'://decrease starveFeeder RPM
    {
      starveFeeder.setRPM(starveFeeder.getRPM()-1.0);
      break;
    }

  case '7':

    //Sets the outfeedRPM at the theoretical correct speed to match the pellet input
    //        outfeedRPM = calcOutfeedRPM();
    outfeed.setRPM(0);

    break;

  case'8':
    configuration.profile.outfeedKp+=.1;
    //    Serial.print("diaKp increased to: ");
    //    Serial.println(configuration.profile.outfeedKp);
    outfeed.setTunings();
    break;

  case '0':
    configuration.profile.outfeedKp-=.1;
    //    Serial.print("diaKp increased to: ");
    //    Serial.println(configuration.profile.outfeedKp);
    outfeed.setTunings();
    break;


  case'9':
    configuration.profile.outfeedKi+=.1;
    //    Serial.print("diaKp increased to: ");
    //    Serial.println(configuration.profile.outfeedKi);
    outfeed.setTunings();
    break;

  case '#':
    configuration.profile.outfeedKi-=.1;
    //    Serial.print("diaKp increased to: ");
    //    Serial.println(configuration.profile.outfeedKi);
    outfeed.setTunings();
    break;

  case 'A'://Stop!!!
    {
      lcd.begin(20, 4);
      lcd.clear();
      lcd.write("Stop Extruding?");
      lcd.setCursor(0,1);
      lcd.write("Press * to continue");
      lcd.setCursor(0,2);
      lcd.write("Press A to stop");
      boolean waitForResponse = true;
      while(waitForResponse){
        key = kpd.getKey();

        //Allow for keyboard input as well
        if (Serial.available() > 0) {
          key = (char)Serial.read();
        }

        if (key == '*'){
          displayExtrudeScreen();
          waitForResponse = false;
        }
        if (key == 'A'){
          auger.disable();
          outfeed.disable();
          spooler.disable();
          barrel.off();
          nozzle.off();
          starveFeeder.disable();
          startFlag = true;//reset start flag so that vars are re initialized if extrude is re entered.
          stateMachine.setState(StateMachine::SELECT_PROFILE);
          return;
        }
      }
      break;
    }


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

      //Serial.print("Increased temp set point to: ");
      //Serial.println(*tempSetPoint);

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

      //Serial.print("Decreased temp set point to: ");
      //Serial.println(*tempSetPoint);

      break;
    }

  case 'D':
    if (starveFeeder.getState()){
      starveFeeder.disable();
    }
    else{
      starveFeeder.enable();
    }
    break;
  }
}


void displayExtrudeScreen(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Extruding");
  
  //Display if in Auto or Manual
  lcd.setCursor(10, 0);
  if (outfeed.getMode() == MANUAL){
    lcd.write("Manual");
  } else {
    lcd.write("Automatic");
  }

  lcd.setCursor(0,1);
  lcd.write("Nozzle: ");
  writeDouble(nozzle.getTemp(),0, 7,1);
  lcd.write(" C");

  lcd.setCursor(0,2);
  lcd.write("Dia: ");
  writeDouble(outfeed.getDia(),2, 7,2);
  lcd.write(" mm");

  lcd.setCursor(0,3);
  lcd.write("Rate: ");
  writeDouble(outfeed.getMPerMin(),2, 7,3);
  lcd.write(" m/min");
}

void stopExtruding(){
  auger.disable();
  outfeed.disable();
  spooler.disable();
  barrel.off();
  nozzle.off();
  starveFeeder.disable();
}


#endif // Extrude_h


