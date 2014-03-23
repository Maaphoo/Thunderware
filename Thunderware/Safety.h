#ifndef Safety_h
#define Safety_h

char safetyMsg[20];

boolean heaterError(){
  if (*tempInput > maxExtruderTemp){
    barrel.off();
    nozzle.off();
    auger.disable();
    outfeed.disable();
    spool.disable();
    strcpy(safetyMsg, "Barrel over temp.");
    Serial.println(barrelTemp);
    currentState = SAFETY_SHUTDOWN;
    return true;
  }
  return false;
}

void safetyShutdown(){
        lcd.clear();
        lcd.write("Safety Shutdown");
        lcd.setCursor(0,1);
        lcd.write(safetyMsg);
        lcd.setCursor(0,3);
        lcd.write("Press any key exit");
//        safetyErrorSound();
        kpd.waitForKey();
        currentState = SELECT_PROFILE;

}
#endif // Safety_h
