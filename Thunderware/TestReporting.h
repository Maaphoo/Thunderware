#ifndef TestReporting_h
#define TestReporting_h

#include "StarveFeeder.h"

void reportCurrentMeasurementTitles(){

  Serial.println("Time(s), "
                 "Dia(mm), "
                 "outfeedRPM, "
                 "starveFeederRPM,  "
                 "augerRPM, "
                 "Mode, "
                 "Barrel Temp(C), "
                 "BarrelDutyCycle(%), "
                 "Nozzle Temp(C), "
                 "NozzleDutyCycle(%), "
                 "outfeedKp, "
                 "outfeedKi, "
                 "outfeedKd, "
                 "feedRate(m/min), "
                 "metersExtruded");

}

void reportCurrentMeasurements(){

  //Serial.println("Barrel_Temp Nozzle_Temp Duty_Cycle Diameter");
   Serial.print((millis()-extrudeStartTime)/1000L);

   Serial.print(", ");
   Serial.print(outfeed.getDia(),3);

   Serial.print(", ");
   Serial.print(outfeed.getRPM());
   
   Serial.print(", ");
   Serial.print(starveFeeder.getRPM());
 
   Serial.print(", ");
   Serial.print(auger.getRPM());
   
   
   Serial.print(", ");
   Serial.print(outfeed.getMode());

   Serial.print(", ");
   Serial.print(barrel.getTemp(),2);

   Serial.print(", ");
   Serial.print(barrel.getDutyCycle());

   Serial.print(", ");
   Serial.print(nozzle.getTemp(),2);

   Serial.print(", ");
   Serial.print(nozzle.getDutyCycle());
 
   Serial.print(", ");
   Serial.print(outfeed.getKp());  
 
   Serial.print(", ");
   Serial.print(outfeed.getKi());
  
   Serial.print(", ");
   Serial.print(outfeed.getKd()); 

   Serial.print(", ");
   Serial.print(outfeed.getMPerMin());
   
   Serial.print(", ");
   Serial.print(outfeed.getMmExtruded()*0.001);

   Serial.println();
}

#endif // TestReporting_h
