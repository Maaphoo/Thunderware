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
  EEPROM_readAnything(0,configuration.currentConfig.configStored);
  if (configuration.currentConfig.configStored){
    Serial.println("The config file is stored");
    Serial.println(configuration.currentConfig.nozzleTBCoefficient);
    Serial.println("The config file is being deleted");
    configuration.deleteConfig();
  } 
  else {
    Serial.println("The config file is not stored");
    Serial.println(configuration.currentConfig.nozzleTBCoefficient);
    Serial.println("Changing nozzleTBCoefficient");
    configuration.currentConfig.nozzleTBCoefficient= 67;
    configuration.saveConfig();
  }

  delay(5000);
//  configuration.currentConfig.nozzleTBCoefficient = 55;
//  configuration.saveConfig();
}

#endif


