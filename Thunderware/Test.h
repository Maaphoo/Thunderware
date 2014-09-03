#ifndef Test_h
#define Test_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void test()
{
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

////Auger Direction test
//auger.enable();
//auger.setRPM(30);
//delay(5000);
//auger.disable();
//delay(1000);

////Small Stepper Enable Tests
//outfeed.enable();
//spooler.enable();
//starveFeeder.enable();
//delay (5000);
//outfeed.disable();
//spooler.disable();
//starveFeeder.disable();
//delay (1000);

//Small Stepper Direction and pot adjust tests
//outfeed.enable();
//spooler.enable();
//starveFeeder.enable();
//outfeed.setRPM(60);
//starveFeeder.setRPM(60);
//spooler.setRPM(60);
//delay(5000);
//outfeed.disable();
//spooler.disable();
//starveFeeder.disable();
//delay(1000);


////buzzer Test
//buzzer.setMsg(Buzzer::SOAK_FINISHED);
//while(millis()<10000){
//  buzzer.activate();
//}



//Serial.println(caliper.getRawADC());
//delay (1000);




//delay(100000);


////Nozzle Testing
//static long now;
//static long reportTime;
//static int interval;
//static boolean flag;
//
//nozzle.activate();
//
//now = millis();
//if (now >= reportTime){
//  nozzle.setDutyCycle(0);
//  Serial.print("nozzle Temp set point: ");
//  Serial.println(configuration.profile.nozzleTemp);
//  Serial.print("nozzle Temp");
//  Serial.println(nozzle.getTemp());
//  Serial.print("nozzle dutyCycle");
//  Serial.println(nozzle.getDutyCycle());  
//  Serial.println();
//  reportTime += 1000;
//}

////Barrel Testing
//static long now;
//static long reportTime;
//static int interval;
//static boolean flag;
//
//barrel.activate();
//
//now = millis();
//if (now >= reportTime){
//  barrel.setDutyCycle(0);
//  Serial.print("barrel Temp set point: ");
//  Serial.println(configuration.profile.barrelTemp);
//  Serial.print("barrel Temp");
//  Serial.println(barrel.getTemp());
//  Serial.print("barrel dutyCycle");
//  Serial.println(barrel.getDutyCycle());  
//  Serial.println();
//  reportTime += 1000;
//}

////Keypad Testing
//key = kpd.waitForKey();
//Serial.println(key);

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


