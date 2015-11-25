#ifndef TestReporting_h
#define TestReporting_h

//#include "StarveFeeder.h"

void reportCurrentMeasurementTitles(){

  Serial.println(F("Time(s), "
                 "Dia(mm), "
                 "outfeedRPM, "
                 "starveFeederRPM,  "
                 "augerRPM, "
                 "Mode, "
                 "outfeedKp, "
                 "outfeedKi, "
                 "outfeedKd, "
                 "feedRate(m/min), "
                 "metersExtruded"));

}

void reportCurrentMeasurements(){

  //Serial.println("Barrel_Temp Nozzle_Temp Duty_Cycle Diameter");
//   Serial.print((millis()-stateMachine.getExtrudeStartTime())/1000L);

   Serial.print(F(", "));
   Serial.print(outfeed.getDia(),3);

   Serial.print(F(", "));
   Serial.print(outfeed.getRPM());
   
//   Serial.print(F(", "));
//   Serial.print(starveFeeder.getRPM());
 
   Serial.print(F(", "));
   Serial.print(auger.getRPM());
   
   
   Serial.print(F(", "));
   Serial.print(outfeed.getMode());

//    Serial.print(F(", "));
//    Serial.print(barrel.getTemp(),2);
// 
//    Serial.print(F(", "));
//    Serial.print(barrel.getDutyCycle());
// 
//    Serial.print(F(", "));
//    Serial.print(nozzle.getTemp(),2);
// 
//    Serial.print(F(", "));
//    Serial.print(nozzle.getDutyCycle());
 
   Serial.print(", ");
   Serial.print(outfeed.getKp());  
 
   Serial.print(F(", "));
   Serial.print(outfeed.getKi());
  
   Serial.print(F(", "));
   Serial.print(outfeed.getKd()); 

   Serial.print(F(", "));
   Serial.print(outfeed.getMPerMin());
   
   Serial.print(F(", "));
   Serial.print(outfeed.getMmExtruded()*0.001);

   Serial.println();
}

#endif // TestReporting_h
