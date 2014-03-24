
#ifndef Extrude_h
#define Extrude_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void displayExtrudeScreen();
void printDiameter(int col, int row);
void printFtPerMin(int col, int row);

//setup for extruding
void beginExtrude(){
  static boolean accelerating;

  if (!accelerating){

    lcd.clear();
    displayExtrudeScreen();

    // Reset the outfeed mmExtruded and Spool quanitiy
    outfeed.reset();

    //For testing serial print the titles of the recorded Data
    reportCurrentMeasurementTitles();

    //if the auger will me rotating, check the temp before accelerating
    //if it isn't going to rotate skip straight to extrude
    if (configuration.profile.augerRPM > 0.0){
      if (barrel.getTemp()<170 && auger.getRPM()>0){//Cant run the auger if the barrel isn't hot;
        currentState = SELECT_PROFILE;
        return;
      }
      else{
        auger.enable();
        accelerating = true;
      }
    }
    else{
      outfeed.enable();
      spool.enable();
      currentState = EXTRUDE;
      return;
    }
  }

  //Accelerate Auger
  static float augerRPMTmp = configuration.profile.augerRPM;
  static int i = 1;

  barrel.activate();
  nozzle.activate();

  auger.setRPM(augerRPMTmp/400.0*(double)i);
  i++;
  if (i>400){
    outfeed.setRPM(configuration.profile.outfeedRPM);
    outfeed.enable();
    spool.enable();
    outfeed.setMode(MANUAL);
    currentState = EXTRUDE;
    accelerating = false;//reset for a potential restart
  }
}

//Extrude function
void extrude(){
  static unsigned long now;
  static unsigned long reportTime;
  static unsigned long startExtrudingTime;
  static boolean redrawLCD = true;
  static boolean startFlag = true;//marks first time soak is run

  now = millis();

  if (startFlag){
    startExtrudingTime = now;
    startFlag = false;
  }

  //turn relay on or off (or neither)
  barrel.activate();
  nozzle.activate();
  outfeed.sample();

  //report sensor data
  if (now >= reportTime){

    //Safety check
    // if (heaterError()) {return;}
    spool.setRPM();

    if (redrawLCD){
      displayExtrudeScreen();
      redrawLCD = false;
    }

    //update temp dia and rate
    writeDouble(nozzle.getTemp(),0, 7,1);
    writeDouble(outfeed.getDia(),2, 7,2);
    writeDouble(outfeed.getMPerMin(),2, 7,3);
    Serial.println(outfeed.getMPerMin());

//    reportCurrentMeasurements();

    reportTime += 1000;
  }




  //now check for user input and respond accordingly
  key = kpd.getKey();

  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }
  
  if (key){redrawLCD = true;}
  
  switch(key){
  case '*':
    if (outfeed.getMode() == MANUAL){
      lcd.setCursor(0,3);
      lcd.write("Press * for AUTO  ");
      outfeed.setMode(AUTOMATIC);
    } 
    else {
      lcd.setCursor(0,3);
      lcd.write("Press * for MANUAL");
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

  case '3'://increase spool scale factor
    {
      //        setFeedRate(getFeedRate()+0.5);
      //          increaseFeedRate();

      break;
    }
  case '6'://decrease outfeed RPM
    {
      //        setFeedRate(getFeedRate()-0.5);
      //          decreaseFeedRate();
      break;
    }
    //Notify on Computer screen
    //Serial.print("Decreased spool Scale Factor to: ");
    //Serial.println(sf);
    break;

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
          spool.disable();
          barrel.off();
          nozzle.off();
          starveFeeder.disable();
          currentState = SELECT_PROFILE;
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

  //  if (outfeedPID.GetMode() == MANUAL){
  //    lcd.write("Press * for AUTO  ");
  //  } else {
  //    lcd.write("Press * for Manual");
  //  }

}


#endif // Extrude_h

