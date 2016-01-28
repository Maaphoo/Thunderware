
#ifndef Extrude_h
#define Extrude_h

#include "Preheat.h"
#include "StarveFeeder.h"
#include "TestReporting.h"

void stopExtruding();

unsigned long loadFilamentStartTime;
unsigned long loadFilamentEndTime;

void beginLoadFilament() {
  static boolean accelerating = false;//True if the auger is being accelerated
  static unsigned long accelerateTime;//time at which acceleration has started
  static float augerRPMTmp;
  static int accInt; //keeps track of the acceleration interval
  static boolean startFlag = true;//true for first run of this function

  if (startFlag) {
    if (configuration.profile.augerRPM > 0 && !accelerating) {
      //do a safety check before running auger
      safety.check();
      auger.enable();
      accelerating = true;
      accInt = 1;
      accelerateTime = millis();
    }
    startFlag = false;
  }

  //Accelerate auger if accelerating and it is time for a speed up)
  if (accelerating && millis() >= accelerateTime && accInt < 400) {
    //Accelerate Auger
    zone1.activate();
    zone2.activate();
    zone3.activate();
    zone4.activate();

    auger.setRPM(configuration.profile.augerRPM / 400.0 * (double)accInt);
    accInt++;
    accelerateTime += 5;
    return;//don't do anything else until the auger is accelerated
  }
  if (accelerating && accInt < 400) return;//stop progress until auger is accelerated if it is accelerating

  //Either the auger was accelerated or the auger RPM is zero

  accelerating = false;//reset for next time begin load filament is entered
  startFlag = true;// reset for the next start

  //The auger has been accelerated, turn everything else on and switch the state
  if (configuration.profile.outfeedRPM > 0.0) {
    outfeed.setRPM(configuration.profile.outfeedRPM);
    outfeed.setMode(MANUAL);
    outfeed.enable();
    spooler.setRPM();
    spooler.enable();
    /*	starveFeeder.dump();//Make sure that the sensor begins blocked*/
    /*    starveFeeder.on();*/
  }
  //get loadFilamentStartTime and set loadFilamentEnd time
  loadFilamentStartTime = millis();
  loadFilamentEndTime = loadFilamentStartTime + configuration.physical.loadFilamentTime * 60L * 1000L;

  currentState = LOAD_FILAMENT;
  activeMenu = &loadFilamentMenu;
  activeMenu->display();
}


//The state changes to BEGIN_EXTRUDE when user selects it in menu
void loadFilament() {
  //activate the heaters and outfeed
  buzzer.activate();
  zone1.activate();
  zone2.activate();
  zone3.activate();
  zone3.activate();
  outfeed.activate();

  if (millis() > loadFilamentEndTime - 30L * 1000L) {
    //trigger message load filament end is nearing
    buzzer.setMsg(Buzzer::LOAD_FILAMENT_TIME_RUNNING_OUT);
  }
  if (millis() > loadFilamentEndTime) {
    //trigger safety shutdown
  }
}



//setup for extruding
void beginExtrude() {
  //Set the temperatures of the heating zones to their extrusion temperatures.
  configuration.physical.zone1.setTemp = configuration.profile.zone1SetTemp;
  configuration.physical.zone2.setTemp = configuration.profile.zone2SetTemp;
  configuration.physical.zone3.setTemp = configuration.profile.zone3SetTemp;
  configuration.physical.zone4.setTemp = configuration.profile.zone4SetTemp;
  
  //Set motor RPMs and enable motors
  auger.enable();
  auger.setRPM(configuration.profile.augerRPM);
  outfeed.setRPM(configuration.profile.outfeedInitialRPM);
  outfeed.setMode(MANUAL);
  outfeed.enable();
  spooler.setRPM(60.0);
  spooler.enable();

  // If there is any message stop it
  buzzer.reset();

  //grab the time extrusion is started
  extrudeStartTime = millis();

  //For testing serial print the titles of the recorded Data
  reportCurrentMeasurementTitles();

  // Reset the outfeed mmExtruded and Spool quantity
  outfeed.reset();

  currentState = EXTRUDE;
}



//Extrude function
void extrude() {

  buzzer.activate();

  //activate the heaters, outfeed and spooler
  zone1.activate();
  zone2.activate();
  zone3.activate();
  zone4.activate();
  outfeed.activate();

  if (spoolerState[1] == 'n') {
    spooler.setRPM();
  }

}



void stopExtruding() {
  auger.disable();
  outfeed.disable();
  spooler.disable();
  zone1.off();
  zone2.off();
  zone3.off();
  zone4.off();
  starveFeeder.off();
}


#endif // Extrude_h




