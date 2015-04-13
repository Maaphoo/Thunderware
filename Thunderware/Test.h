#ifndef Test_h
#define Test_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void test()
{
  static unsigned long now;
  static unsigned long reportTime;
  static int interval;
  static boolean flag = true;
  now = millis();
//  //Test current draw on 12 v power supply by running everything at once
//  if (flag){
//    auger.enable();
//    starveFeeder.enable();
//    outfeed.enable();
//    spooler.enable();
//    
//    auger.setRPM(30);
//    starveFeeder.setRPM(30);
//    outfeed.setRPM(30);
//    spooler.setRPM(30);
//    flag = false;
//  }
//  nozzle.activate();
//  barrel.activate();
//  outfeed.activate();
//  if (now >= reportTime){
//    nozzle.setDutyCycle(255);
//    barrel.setDutyCycle(100);
//    outfeed.getRawADC();
//    lcd.clear();
//    lcd.write("Nozzle Test: ");
//
//    lcd.setCursor(7,1);
//    lcd.write("(SP) (ACT)");
//
//    lcd.setCursor(18,2);
//    lcd.write("C");
//    lcd.setCursor(18,3);
//    lcd.write("C");
//
//    lcd.setCursor(0,2);
//    lcd.write("Barrel ");
//    char tempString[10];
//    dtostrf(configuration.profile.barrelTemp, 3,0,tempString);
//    lcd.write(tempString);
//
//    dtostrf(barrel.getTemp(), 3,0,tempString);
//    lcd.setCursor(12,2);
//    lcd.write(tempString);
//
//    lcd.setCursor(0,3);
//    lcd.write("Nozzle ");
//    dtostrf(configuration.profile.nozzleTemp, 3,0,tempString);
//    lcd.write(tempString);
//
//    dtostrf(nozzle.getTemp(), 3,0,tempString);
//    lcd.setCursor(12,3);
//    lcd.write(tempString);
//    reportTime += 1000;
//  }

  ////Spooler Calibration
  //lcd.clear();
  //lcd.write("Spooler Calibration");
  //lcd.setCursor(0,1);
  //lcd.write("Mark the Spool disk");
  //lcd.setCursor(0,2);
  //lcd.write("at the roller.");
  //lcd.setCursor(0,3);
  //lcd.write("Press any key...");
  //kpd.waitForKey();
  //spooler.setRPM(60);
  //unsigned long durration = configuration.physical.spoolerDiskRadius/configuration.physical.spoolerMotorRollerRaduis*1000.0;
  //unsigned long startTime = millis();
  //unsigned long endTime = startTime+durration;
  //spooler.enable();
  //unsigned long now;
  //while (now < endTime){
  //  now = millis();
  //}
  //spooler.disable();
  ////Add in Adjustment pressing 1 for more, 4 for less, 2 for even more, 4 for even less. etc.
  ////Then report and record the setting. and repeat to double check.





  //  Serial.println(configuration.physical.outfeedDirection);
  // outfeed.enable();
  // spooler.enable();
  // while(1){
  //   //it is as if spooler._outfeed is pointing to a null Outfeed object.
  // outfeed.setRPM(60);//Doesen't work. spooler can't access outfeed.getRPM() all it gets is zero. 
  // spooler.setRPM();
  //
  // Serial.print("beginning to outfeed: ");
  // Serial.println(outfeed.getMmExtruded());
  // delay(10000); 
  //
  //  Serial.print("done outfeed: ");
  //  Serial.println(outfeed.getMmExtruded());
  //  outfeed.reset();
  //  outfeed.setRPM(0);
  //  spooler.setRPM();
  // delay(10000); 
  // }

  ////Auger Enable test
  //auger.enable();
  //delay(5000);
  //auger.disable();
  //delay(1000);

// //Auger Direction test
// auger.enable();
// auger.setRPM(4);//This is 1 rpm for the motor b/c the gear ratio is 1:3
// delay(5000);
// auger.disable();
// delay(1000);

//// Small Stepper Enable Tests
// outfeed.enable();
// spooler.enable();
// starveFeeder.enable();
// delay (5000);
// outfeed.disable();
// spooler.disable();
// starveFeeder.disable();
// delay (1000);

//  //Small Stepper Direction and pot adjust tests
// outfeed.enable();
// spooler.enable();
// starveFeeder.enable();
// outfeed.setRPM(60);
// starveFeeder.setRPM(60);
// spooler.setRPM(60);
// delay(5000);
// outfeed.disable();
// spooler.disable();
// starveFeeder.disable();
// delay(1000);


  ////buzzer Test
  //buzzer.setMsg(Buzzer::SOAK_FINISHED);
  //while(millis()<10000){
  //  buzzer.activate();
  //}

//  //Test ADC in caliper. Second arduino must be powered for this to work.
//  Serial.println(outfeed.getRawADC());
//  lcd.clear();
//  lcd.write("Raw ADC: ");
//  char tempString[10];
//  dtostrf(outfeed.getRawADC(), 3,0,tempString);
//  lcd.write(tempString);
//  delay (1000);

////Nozzle Testing
//  nozzle.activate();
//  barrel.activate();
//  if (now >= reportTime){
//    nozzle.setDutyCycle(255);
//    barrel.setDutyCycle(0);
//    Serial.print("nozzle Temp set point: ");
//    Serial.println(configuration.profile.nozzleTemp);
//    Serial.print("nozzle Temp");
//    Serial.println(nozzle.getTemp());
//    Serial.print("nozzle dutyCycle");
//    Serial.println(nozzle.getDutyCycle());  
//    Serial.println();
//    
//    lcd.clear();
//    lcd.write("Nozzle Test: ");
//
//    lcd.setCursor(7,1);
//    lcd.write("(SP) (ACT)");
//
//    lcd.setCursor(18,2);
//    lcd.write("C");
//    lcd.setCursor(18,3);
//    lcd.write("C");
//
//    lcd.setCursor(0,2);
//    lcd.write("Barrel ");
//    char tempString[10];
//    dtostrf(configuration.profile.barrelTemp, 3,0,tempString);
//    lcd.write(tempString);
//
//    dtostrf(barrel.getTemp(), 3,0,tempString);
//    lcd.setCursor(12,2);
//    lcd.write(tempString);
//
//    lcd.setCursor(0,3);
//    lcd.write("Nozzle ");
//    dtostrf(configuration.profile.nozzleTemp, 3,0,tempString);
//    lcd.write(tempString);
//
//    dtostrf(nozzle.getTemp(), 3,0,tempString);
//    lcd.setCursor(12,3);
//    lcd.write(tempString);
//    reportTime += 1000;
//  }

  //  ////Barrel Testing
  //  nozzle.activate();
  //  barrel.activate();
  //  if (now >= reportTime){
  //    nozzle.setDutyCycle(0);
  //    barrel.setDutyCycle(50);
  //    Serial.print("nozzle Temp set point: ");
  //    Serial.println(configuration.profile.nozzleTemp);
  //    Serial.print("nozzle Temp");
  //    Serial.println(nozzle.getTemp());
  //    Serial.print("nozzle dutyCycle");
  //    Serial.println(nozzle.getDutyCycle());  
  //    Serial.println();
  //    
  //    lcd.clear();
  //    lcd.write("Barrel Test: ");
  //
  //    lcd.setCursor(7,1);
  //    lcd.write("(SP) (ACT)");
  //
  //    lcd.setCursor(18,2);
  //    lcd.write("C");
  //    lcd.setCursor(18,3);
  //    lcd.write("C");
  //
  //    lcd.setCursor(0,2);
  //    lcd.write("Barrel ");
  //    char tempString[10];
  //    dtostrf(configuration.profile.barrelTemp, 3,0,tempString);
  //    lcd.write(tempString);
  //
  //    dtostrf(barrel.getTemp(), 3,0,tempString);
  //    lcd.setCursor(12,2);
  //    lcd.write(tempString);
  //
  //    lcd.setCursor(0,3);
  //    lcd.write("Nozzle ");
  //    dtostrf(configuration.profile.nozzleTemp, 3,0,tempString);
  //    lcd.write(tempString);
  //
  //    dtostrf(nozzle.getTemp(), 3,0,tempString);
  //    lcd.setCursor(12,3);
  //    lcd.write(tempString);
  //    reportTime += 1000;
  //  }

  //  //Thermistor Testing
  //  //Just keeps up dating the currently measured temps
  //  barrel.sampleTemp();
  //  nozzle.sampleTemp();
  //  if (now>reportTime){
  //    lcd.clear();
  //    lcd.write("Thermistor Temps:");
  //    lcd.setCursor(0,1);
  //    lcd.write("Barrel: ");
  //    char barrelTempString[10];
  //    dtostrf(barrel.getTemp(), 1,2,barrelTempString);
  //    lcd.write(barrelTempString);
  //    lcd.setCursor(0,2);
  //    lcd.write("Nozzle: ");
  //    char nozzleTempString[10];
  //    dtostrf(nozzle.getTemp(), 1,2,nozzleTempString);
  //    lcd.write(nozzleTempString); 
  //    Serial.print("Barrel Temp: ");
  //    Serial.println(barrel.getTemp());
  //    Serial.print("Nozzle Temp: ");
  //    Serial.println(nozzle.getTemp());
  //    reportTime = now+1000L;
  //  }

////Keypad Testing
//  while (key != 'D'){
//    key = kpd.waitForKey();
//    Serial.println(key);
//    lcd.write(key);
//  }
  //  boolean assignedKeys[ROWS][COLS];
  //  //char targetKeys[ROWS*COLS] = ['1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', '*', '#'];
  //  char targetKeys[ROWS*COLS];
  //  //make 1D array of all Characters on keypad
  //  for (int i=0; i<ROWS; i++){
  //    for (int j=0; j<COLS;j++){
  //      targetKeys[COLS*i+j] = keys[i][j];
  //    }
  //  }
  //  boolean keyFound;
  //    lcd.clear();
  //    for (int k=0;k<ROWS*COLS;k++){
  //    lcd.write("Press '");
  //    lcd.write(targetKeys[k]);
  //    lcd.write("'");
  //    keyFound = false;
  //    key = kpd.waitForKey();
  //    for (int i=0; i<ROWS; i++){
  //      for (int j=0; j<COLS;j++){
  //        if (keys[i][j] == key && !assignedKeys[i][j]){
  //          assignedKeys[i][j] = true;
  //          keys[i][j] = targetKeys[k];
  //          keyFound = true;
  //          lcd.clear();
  //          for (int i=0;i<ROWS;i++){
  //            for (int j=0; j<COLS;j++){
  //              lcd.setCursor(12+j,i);
  //              lcd.write(keys[i][j]);
  //            }
  //          }
  //        }
  //      }
  //    }
  //    if (!keyFound){
  //      lcd.clear();
  //      lcd.setCursor(0,0);
  //      lcd.write("ERROR: Key not found");
  //      lcd.setCursor(0,2);     
  //      lcd.write("Check the keys array.");
  //    }
  //  }
  //
  //  // The keys array is now correct. 
  //  // Store it in the EEPROM
  //
  //
  //  lcd.clear();
  //  lcd.setCursor(0,0);
  //  lcd.write("keys array:");
  //  for (int i=0;i<ROWS;i++){
  //    for (int j=0; j<COLS;j++){
  //      lcd.setCursor(12+j,i);
  //      lcd.write(keys[i][j]);
  //    }
  //  }
  //  key = kpd.waitForKey();
  //  return;




  ////LCD Testing
  //  lcd.clear();
  //  lcd.setCursor(0,0);
  //  lcd.write("This is a Test.");
  //  lcd.setCursor(0,1);
  //  lcd.write("1: Only a test");
  //  lcd.setCursor(0,2);
  //  lcd.write("2:Not the Real thing");
  //  lcd.setCursor(0,3);
  //  lcd.write("3: But close");
  //delay (5000);

  ////Optical Caliper testing
  //  lcd.clear();
  //  lcd.write("Sensor Value");
  //
  //  double rawADC;
  //  while(1){
  //    rawADC = outfeed.getRawADC();
  //    lcd.setCursor(7,1);
  //    writeDouble(rawADC,0,7,1);
  //    Serial.println(rawADC);
  //    delay(1000);
  //
  //  }

  //  delay(5000);
  //    Serial.println("Saving new name to profile 1: Prof1Name");
  //    configuration.loadProfile(1);
  //    strcpy(configuration.profile.name, "Prof1Name");
  //    configuration.saveProfile(1);
  //    delay(200);
  //  Serial.println("Deleting Profile 2");
  //  configuration.deleteProfile(2);
  //  Serial.println();
  //  delay(2000);  
  //  Serial.println("Attempting to load profile 2");
  //  if (configuration.loadProfile(2)){
  //    Serial.println("Able to load profile 2");
  //  } else {
  //    Serial.println("Unable to load profile 2");
  //  }
  //  delay(2000);  
  //  Serial.println("loading Profile 1");
  //  configuration.loadProfile(1);
  //  Serial.print("It's name is: ");
  //  Serial.println(configuration.profile.name);
  //  Serial.println();
  //  Serial.println("Done with test");
  //  delay(1000000);









  //      Serial.print("Getting Just the name: ");
  //      Serial.println(configuration.getName(1));
  //    }else{
  //      Serial.println("loading Unsuccessful");
  //    } 
  //  configuration.physical.nozzleTBCoefficient = 55;
  //  configuration.saveConfig();
}

#endif








