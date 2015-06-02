#ifndef Preheat_h
#define Preheat_h

#include "Safety.h"
#include "TestReporting.h"

static unsigned long preheatStartTime;

void beginPreheat(){
  preheatStartTime = millis();
    //start from full power state
    barrel.setDutyCycle(90);
    nozzle.setDutyCycle(255);

    //Then set heater PIDs to automatic
    barrel.setMode(AUTOMATIC);
    nozzle.setMode(AUTOMATIC);
    
    //Print the titles for the data output to the serial monitor
    reportCurrentMeasurementTitles();

    currentState = PREHEAT;
}

void preheat(){

  buzzer.activate();
  barrel.activate();
  nozzle.activate();

  if (barrel.getTemp() > configuration.profile.barrelTemp-3 && nozzle.getTemp() > configuration.profile.nozzleTemp-3){
    buzzer.setMsg(Buzzer::PREHEAT_FINISHED);
    currentState = BEGIN_SOAK;
    activeMenu = &soakMenu;
	activeMenu->reset();
    activeMenu->display();
  }
}



static unsigned long soakStartTime;
static unsigned long soakEndTime;

void beginSoak(){
  Serial.println("Begin Soak");
  soakStartTime = millis();
  soakEndTime = soakStartTime + configuration.profile.soakTime*60L*1000L;
  currentState = SOAK;
}



//Soak state function
void soak(){
  static unsigned long now;
  static boolean msgSet = false;//indicates that the end soak buzzer message has been set

  now = millis();

  buzzer.activate();
  barrel.activate();
  nozzle.activate();
//  safety.check();

  if (now>=soakEndTime-5000 && !msgSet){
    buzzer.setMsg(Buzzer::SOAK_FINISHED);
    msgSet = true;
  }

  if (now>=soakEndTime){
    msgSet = false;//reset msgSet flag
    Serial.println("");
    Serial.println(F("Finished Soaking"));
    Serial.println("");
    currentState = BEGIN_LOAD_FILAMENT;
    activeMenu = &loadFilamentMenu;
    
    activeMenu->reset();  
    activeMenu->display();  
  }
}




#endif // Preheat_h

