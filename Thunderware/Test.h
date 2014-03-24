#ifndef Test_h
#define Test_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void test()
{
//  Serial.println(configuration.physical.outfeedDirection);
// outfeed.enable();
// spool.enable();
// while(1){
//   //it is as if spool._outfeed is pointing to a null Outfeed object.
// outfeed.setRPM(60);//Doesen't work. spool can't access outfeed.getRPM() all it gets is zero. 
// spool.setRPM();
//
// Serial.print("beginning to outfeed: ");
// Serial.println(outfeed.getMmExtruded());
// delay(10000); 
//
//  Serial.print("done outfeed: ");
//  Serial.println(outfeed.getMmExtruded());
//  outfeed.reset();
//  outfeed.setRPM(0);
//  spool.setRPM();
// delay(10000); 
// }

//Serial.println("HEre about to enable");
//starveFeeder.enable();
//starveFeeder.setRPM(100);
//delay(100000);

//static boolean flag;
//if (!flag){
//auger.enable();
//auger.setRPM(40);
//outfeed.enable();
//outfeed.setRPM(50);
//spool.enable();
//spool.setRPM();
//flag = true;
//}

auger.enable();
auger.setRPM(10);
delay (5000);
auger.disable();
delay (1000);


//Serial.println(caliper.getRawADC());
//delay (1000);




//delay(100000);


//static long now;
//static long reportTime;
//static int interval;
//static boolean flag;
//
//nozzle.activate();
//
//now = millis();
//if (now >= reportTime){
////  nozzle.setDutyCycle(50);
//  Serial.print("nozzle Temp set point: ");
//  Serial.println(configuration.profile.nozzleTemp);
//  Serial.print("nozzle Temp");
//  Serial.println(nozzle.getTemp());
//  Serial.print("nozzle dutyCycle");
//  Serial.println(nozzle.getDutyCycle());  
//  Serial.println();
//  reportTime += 1000;
//}


//pinMode(5, OUTPUT);
//analogWrite(5,100);
//delay (100000);



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


