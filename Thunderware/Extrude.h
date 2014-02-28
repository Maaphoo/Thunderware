
#ifndef Extrude_h
#define Extrude_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void displayExtrudeScreen();
void printDiameter(int col, int row);
void printFtPerMin(int col, int row);

//Extrude function
void extrudeAutomatic(){

  buzzer.setMsg(Buzzer::EXTRUDING);//Sound the buzzer that extrusion is beginning

  barrelPID.SetTunings(consKp, consKi, consKd);
  now = millis();
  startExtrudingTime = now;
  computeTime = now+2000L;
  reportTime = now+1000L;

  lcd.clear();
  displayExtrudeScreen();


  mmExtruded = 0;
//   reportSettings();
//   reportSPS();
  reportCurrentMeasurementTitles();

  //Turn on the PWM for the steppers
//  timer1FastPWM(1000);
//  timer2FastPWM(1000);
//  timer4FastPWM(1000);

//  auger.setRPM(0);
//  outfeed.setRPM(0);
//  spool.setRPM(0);

  if (app.barrelThermistor()->getTemp()<170 && augerRPM>0){//Cant run the auger if the barrel isn't hot;
    currentState = SELECT_PROFILE;
    return;
  }

  if (augerRPM !=0){
    auger.enable();
      //Accelerate Auger
      float augerRPMTmp = augerRPM;
    for (int i=1;i<401;i++){
      barrelHeater.activate();
//      ActivateRelay();
      auger.setRPM(augerRPMTmp/400.0*(double)i);
      delay(5);
    }
  }

  auger.enable();
  outfeed.enable();
  spool.enable();

  outfeedPID.SetMode(MANUAL);



  boolean continueExtruding = true;
  feederOn();
  while(continueExtruding){
      key = kpd.getKey();

  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }
    switch(key){
      case '*':
        if (outfeedPID.GetMode() == MANUAL){
          lcd.setCursor(0,3);
          lcd.write("Press * for AUTO  ");
          outfeedPID.SetMode(AUTOMATIC);
        } else {
          lcd.setCursor(0,3);
          lcd.write("Press * for MANUAL");
          outfeedPID.SetMode(MANUAL);
        }
        break;

      case '1'://increase Auger
       {
        auger.setRPM(auger.getRPM()+1);
        lcd.clear();
        lcd.write("Increase Auger to:");
        lcd.setCursor(0,1);
        char augerRPMString[10];
        dtostrf(augerRPM, 1,2,augerRPMString);
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
        dtostrf(augerRPM, 1,2,augerRPMString);
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
        outfeedRPM = outfeedRPM*1.02;
        char outfeedRPMString[10];
        dtostrf(outfeedRPM, 1,2,outfeedRPMString);
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
        outfeedRPM = outfeedRPM*0.98;
        char outfeedRPMString[10];
        dtostrf(outfeedRPM, 1,2,outfeedRPMString);
        lcd.write(outfeedRPMString);

        //Notify on computer
        //Serial.print("Decreased outfeed RPM to: ");
        //Serial.println(outfeedRPM);

        break;
       }

       case '3'://increase spool scale factor
       {
//        setFeedRate(getFeedRate()+0.5);
          increaseFeedRate();

        break;
       }
      case '6'://decrease outfeed RPM
       {
//        setFeedRate(getFeedRate()-0.5);
          decreaseFeedRate();
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
        diaKp+=.1;
        Serial.print("diaKp increased to: ");
        Serial.println(diaKp);
        outfeedPID.SetTunings(diaKp,diaKi,diaKd);
        break;

       case '0':
        diaKp-=.1;
        Serial.print("diaKp decreased to: ");
        Serial.println(diaKp);
        outfeedPID.SetTunings(diaKp,diaKi,diaKd);
        break;


       case'9':
        diaKi+=.1;
        Serial.print("diaKi increased to: ");
        Serial.println(diaKi);
        outfeedPID.SetTunings(diaKp,diaKi,diaKd);
        break;

      case '#':
        diaKi-=.1;
        Serial.print("diaKi decreased to: ");
        Serial.println(diaKi);
        outfeedPID.SetTunings(diaKp,diaKi,diaKd);
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
            barrelHeater.off();
            nozzleHeater.off();
            feederOff();
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
        barrelSetPoint = barrelSetPoint+5;
        char tempSetPointString[10];
        dtostrf(*tempSetPoint, 1,2,tempSetPointString);
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
        barrelSetPoint = barrelSetPoint-5;
        char tempSetPointString[10];
        dtostrf(*tempSetPoint, 1,2,tempSetPointString);
        lcd.write(tempSetPointString);

        //Serial.print("Decreased temp set point to: ");
        //Serial.println(*tempSetPoint);

        break;
       }

        case 'D':
        if (getFeederState()){
          feederOff();
        }else{
          feederOn();
        }
        break;
    }

    now = millis();

    //turn relay on or off (or neither)
    barrelHeater.activate();

    //measure temp. One at a time for better temp measurement
    if (alternateThermistors){
      app.barrelThermistor()->sampleTemp();
      alternateThermistors = !alternateThermistors;
    }else{
      app.nozzleThermistor()->sampleTemp();
      alternateThermistors = !alternateThermistors;
    }

    //If another diameter measurement is ready, get it
    updateDiameter();

    //get lumps from starve feeder if needed
//    runStarveFeeder();

    //computations that get done once every 2 seconds
    if (now>=computeTime){

      //Get Temps and update temp controllers
      barrelTemp = app.barrelThermistor()->getTemp();
      nozzleTemp = app.nozzleThermistor()->getTemp();

      //compute outputs for the PID controllers.
      barrelPID.Compute();
      barrelHeater.setDutyCycle(barrelDutyCycle);

      nozzlePID.Compute();

      //Set the PWM that heats the nozzle of the extruder
      nozzleHeater.setPWM(nozzleDutyCycle);
//      setNozzlePWM();

      //Get Diameter and update outfeed controller
      getMedianDia();
      outfeedPID.Compute();
      outfeed.setRPM(0);
      spool.setRPM();

      //Get ready for next compute time
      computeTime += 2000;
    }

    //report sensor data
    if (now >= reportTime){

      //Safety check
     // if (heaterError()) {return;}

      displayExtrudeScreen();

     reportCurrentMeasurements();

      reportTime += 1000;
    }
  }
}

void displayExtrudeScreen(){
//  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Extruding");

  lcd.setCursor(0,1);
  lcd.write("Temp: ");
  updateTemp(6,1);
  lcd.write(" C");

  lcd.setCursor(0,2);
  lcd.write("Dia: ");
  printDiameter(6,2);
  lcd.write(" mm");

  lcd.setCursor(0,3);
  lcd.write("Rate: ");
  printFtPerMin(6,3);
  lcd.write("ft/min");

//  if (outfeedPID.GetMode() == MANUAL){
//    lcd.write("Press * for AUTO  ");
//  } else {
//    lcd.write("Press * for Manual");
//  }

}


void printDiameter(int col, int row){
    lcd.setCursor(col,row);
    char diaInputString[10];
    dtostrf(medianDia, 1,2,diaInputString);
    lcd.write(diaInputString);
}

void printFtPerMin(int col, int row){
    lcd.setCursor(col,row);
    char rateInputString[10];
    dtostrf(outfeedRPM*2.0*PI*ro*0.0032808, 1,2,rateInputString);
    lcd.write(rateInputString);
}

#endif // Extrude_h
