#ifndef Test_h
#define Test_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void test()
{
 outfeed.enable();
 spool.enable();
 while(1){
   //it is as if spool._outfeed is pointing to a null Outfeed object.
 outfeed.setRPM(60);//Doesen't work. spool can't access outfeed.getRPM() all it gets is zero. 
 spool._outfeed.setRPM(60);//Works to get spool in contact with the outfeed. 
 spool.setRPM();
 Serial.print("Spool outfeed: ");
 Serial.println(spool._outfeed.getRPM());

 Serial.print("beginning to outfeed: ");
 Serial.println(outfeed.getMmExtruded());
 delay(10000); 

  Serial.print("done outfeed: ");
  Serial.println(outfeed.getMmExtruded());
  outfeed.reset();
  outfeed.setRPM(0);
  spool.setRPM();
 delay(10000); 
 }
}

#endif
