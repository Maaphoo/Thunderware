#ifndef Safety_h
#define Safety_h

char safetyMsg[20];

boolean heaterError(){
  if (barrel.getTemp() > maxExtruderTemp){
    barrel.off();
    nozzle.off();
    auger.disable();
    outfeed.disable();
    spooler.disable();
    strcpy(safetyMsg, "Barrel over temp.");
    Serial.println(barrel.getTemp());
    currentState = SAFETY_SHUTDOWN;
    return true;
  }
  return false;
}

void safetyShutdown(){
  lcd.clear();
  lcd.write("Safety Shutdown");
  Serial.println("Safety Shutdown");
  lcd.setCursor(0,1);
  lcd.write(safetyMsg);
  lcd.setCursor(0,3);
  lcd.write("Press any key exit");
  Serial.println("Press any key to exit.");
  //        safetyErrorSound();
  while(1){
    kpd.getKey();

    if (Serial.available() > 0) {
      key = (char)Serial.read();
    }

    if (key){ 
      break;
    }
  }
  currentState = SELECT_PROFILE;

}
#endif // Safety_h

