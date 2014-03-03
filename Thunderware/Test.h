#ifndef Test_h
#define Test_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void test()
{
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

  delay(5000);
    Serial.println("Saving new name to profile 1: Prof1Name");
    configuration.loadProfile(1);
    strcpy(configuration.profile.name, "Prof1Name");
    configuration.saveProfile(1);
    delay(200);
  Serial.println("Deleting Profile 2");
  configuration.deleteProfile(2);
  Serial.println();
  delay(2000);  
  Serial.println("Attempting to load profile 2");
  if (configuration.loadProfile(2)){
    Serial.println("Able to load profile 2");
  } else {
    Serial.println("Unable to load profile 2");
  }
  delay(2000);  
  Serial.println("loading Profile 1");
  configuration.loadProfile(1);
  Serial.print("It's name is: ");
  Serial.println(configuration.profile.name);
  Serial.println();
  Serial.println("Done with test");
  delay(1000000);
    


//      Serial.print("Getting Just the name: ");
//      Serial.println(configuration.getName(1));
//    }else{
//      Serial.println("loading Unsuccessful");
//    } 
//  configuration.physical.nozzleTBCoefficient = 55;
//  configuration.saveConfig();
}

#endif


