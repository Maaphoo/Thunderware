#ifndef Test_h
#define Test_h



//void test(){}

void testAuger(){
	lcd.clear();
	lcd.print(F("WARNING: The Auger"));
	lcd.setCursor(0,1);
	lcd.print(F("must be free to move"));
	lcd.setCursor(0,2);
	lcd.print(F("to perform the"));
	lcd.setCursor(0,3);
	lcd.print(F("following tests."));
	delay(5000);
	lcd.clear();
	lcd.print(F("Continue?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	boolean waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
			waitForResponse = false;
		}
	}
	lcd.clear();
	lcd.print(F("A) Enable/Disable"));
	lcd.setCursor(0,1);
	lcd.print(F("C) When Disabled"));
	lcd.setCursor(0,2);
	lcd.print(F("D) EXIT"));

	waitForResponse = true;
	boolean flag = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		switch (key){
			case 'A':
			if (flag){
				auger.enable();
				flag = false;
				} else {
				auger.disable();
				flag = true;
			}
			break;

			case 'C':

			if (!flag){
				configuration.physical.augerEnable = !configuration.physical.augerEnable;
			}
			waitForResponse = false;
			break;

			case 'D':
			activeMenu->display();
			return;
			break;

		}
	}

	//Auger Direction test
	lcd.clear();
	lcd.print(F("Auger Direction Test"));
	delay(5000);
	lcd.clear();
	lcd.print(F("Continue?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}

	auger.enable();
	auger.setRPM(1);

	lcd.clear();
	lcd.print(F("Auger direction OK?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	lcd.setCursor(0,3);
	lcd.print(F("D) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		switch (key){
			case 'A':
			if (flag){
				auger.disable();
				waitForResponse = false;
			}
			break;

			case 'B':
			configuration.physical.augerDirection = !configuration.physical.augerDirection;
			auger.setDirection();

			break;

			case 'D':
			auger.disable();
			activeMenu->display();
			return;
			break;

		}
	}

	// MicroStepping test
	lcd.clear();
	lcd.print(F("Microsteping Test"));
	delay(5000);
	lcd.clear();
	lcd.print(F("Mark the shaft. "));
	lcd.setCursor(0,1);
	lcd.print(F("Attempting 1 rev"));
	lcd.setCursor(0,2);
	lcd.print(F("A) Begin"));
	lcd.setCursor(0,3);
	lcd.print(F("B) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}
	lcd.clear();
	lcd.print(F("Rotating 1 rev..."));
	auger.enable();
	pinMode(6,OUTPUT);

	auger.enable();
	int rpm = 10;
	auger.setRPM(rpm);
	delay(1000.0*60.0/rpm);
	auger.disable();

	lcd.clear();
	lcd.print(F("If the auger didn't"));
	lcd.setCursor(0,1);
	lcd.print(F("make 1 rev, check"));
	lcd.setCursor(0,2);
	lcd.print(F("the wiring and"));
	lcd.setCursor(0,3);
	lcd.print(F("microstep settings"));
	delay(5000);

	//Save the settings
	lcd.clear();
	lcd.print(F("Save Settings?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			configuration.saveConfig();
			waitForResponse = false;
		}

		if (key == 'B') {
			waitForResponse = false;
		}
	}
	activeMenu->display();
}

void testOutfeed(){
	lcd.clear();
	lcd.print(F("WARNING: The Outfeed"));
	lcd.setCursor(0,1);
	lcd.print(F("must be free to move"));
	lcd.setCursor(0,2);
	lcd.print(F("to perform the"));
	lcd.setCursor(0,3);
	lcd.print(F("following tests."));
	delay(5000);
	lcd.clear();
	lcd.print(F("Continue?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	boolean waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
			waitForResponse = false;
		}
	}
	lcd.clear();
	lcd.print(F("A) Enable/Disable"));
	lcd.setCursor(0,1);
	lcd.print(F("C) When Disabled"));
	lcd.setCursor(0,2);
	lcd.print(F("D) EXIT"));

	waitForResponse = true;
	boolean flag = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		switch (key){
			case 'A':
			if (flag){
				outfeed.enable();
				flag = false;
				} else {
				outfeed.disable();
				flag = true;
			}
			break;

			case 'C':

			if (!flag){
				configuration.physical.outfeedEnable = !configuration.physical.outfeedEnable;
			}
			waitForResponse = false;
			break;

			case 'D':
			activeMenu->display();
			return;
			break;

		}
	}

	//OUtfeed Direction test
	lcd.clear();
	lcd.print(F("Outfeed Direction..."));
	delay(5000);
	lcd.clear();
	lcd.print(F("Continue?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}

	outfeed.enable();
	outfeed.setRPM(1);

	lcd.clear();
	lcd.print(F("Outfeed dir OK?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	lcd.setCursor(0,3);
	lcd.print(F("D) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		switch (key){
			case 'A':
			if (flag){
				outfeed.disable();
				waitForResponse = false;
			}
			break;

			case 'B':
			configuration.physical.outfeedDirection = !configuration.physical.outfeedDirection;
			outfeed.setDirection();

			break;

			case 'D':
			outfeed.disable();
			activeMenu->display();
			return;
			break;

		}
	}

	// MicroStepping test
	lcd.clear();
	lcd.print(F("Microsteping Test"));
	delay(5000);
	lcd.clear();
	lcd.print(F("Mark the Roller. "));
	lcd.setCursor(0,1);
	lcd.print(F("Attempting 1 rev"));
	lcd.setCursor(0,2);
	lcd.print(F("A) Begin"));
	lcd.setCursor(0,3);
	lcd.print(F("B) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}
	lcd.clear();
	lcd.print(F("Rotating 1 rev..."));
	outfeed.enable();
	pinMode(6,OUTPUT);

	outfeed.enable();
	float rpm = 10.0;
	outfeed.setRPM(rpm);
	delay(1000.0*60.0/rpm);
	outfeed.disable();

	lcd.clear();
	lcd.print(F("If outfeed didn't"));
	lcd.setCursor(0,1);
	lcd.print(F("make 1 rev, check"));
	lcd.setCursor(0,2);
	lcd.print(F("the wiring and"));
	lcd.setCursor(0,3);
	lcd.print(F("microstep settings"));
	delay(5000);

	//Test Roller diameter
	lcd.clear();
	lcd.print(F("Roller Diameter Test"));
	delay(5000);
	lcd.clear();
	lcd.print(F("Load 10ft filament."));
	lcd.setCursor(0,1);
	lcd.print(F("press Stop at 10Ft."));
	lcd.setCursor(0,2);
	lcd.print(F("A) Begin"));
	lcd.setCursor(0,3);
	lcd.print(F("B) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}
	outfeed.enable();
	rpm = 20.0;
	outfeed.setRPM(rpm);
	unsigned long startTime = millis();
	lcd.clear();
	lcd.print(F("press Stop at 10ft."));
	lcd.setCursor(0,1);
	lcd.print(F("A) Stop"));
	lcd.setCursor(0,2);
	lcd.print(F("B) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			outfeed.disable();
			activeMenu->display();
			return;
		}
	}

	outfeed.disable();
	unsigned long stopTime = millis();
	configuration.physical.outfeedRollerRadius = (300.0*60.0*1000.0)/((float)(stopTime-startTime)*rpm*2.0*3.14159);

	//Save the settings
	lcd.clear();
	lcd.print(F("Save Settings?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			configuration.saveConfig();
			waitForResponse = false;
		}

		if (key == 'B') {
			waitForResponse = false;
		}
	}
	activeMenu->display();
}

void testStarveFeeder(){

}

void testSpooler(){
	lcd.clear();
	lcd.print(F("WARNING: The Spooler"));
	lcd.setCursor(0,1);
	lcd.print(F("must be free to move"));
	lcd.setCursor(0,2);
	lcd.print(F("to perform the"));
	lcd.setCursor(0,3);
	lcd.print(F("following tests."));
	delay(5000);
	lcd.clear();
	lcd.print(F("Continue?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	boolean waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
			waitForResponse = false;
		}
	}
	lcd.clear();
	lcd.print(F("A) Enable/Disable"));
	lcd.setCursor(0,1);
	lcd.print(F("C) When Disabled"));
	lcd.setCursor(0,2);
	lcd.print(F("D) EXIT"));

	waitForResponse = true;
	boolean flag = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		switch (key){
			case 'A':
			if (flag){
				spooler.enable();
				flag = false;
				} else {
				spooler.disable();
				flag = true;
			}
			break;

			case 'C':

			if (!flag){
				configuration.physical.spoolerEnable = !configuration.physical.spoolerEnable;
			}
			waitForResponse = false;
			break;

			case 'D':
			activeMenu->display();
			return;
			break;

		}
	}

	//spooler Direction test
	lcd.clear();
	lcd.print(F("spooler Direction..."));
	delay(5000);
	lcd.clear();
	lcd.print(F("Continue?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}

	spooler.enable();
	spooler.setRPM(1);

	lcd.clear();
	lcd.print(F("spooler dir OK?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	lcd.setCursor(0,3);
	lcd.print(F("D) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		switch (key){
			case 'A':
			if (flag){
				spooler.disable();
				waitForResponse = false;
			}
			break;

			case 'B':
			configuration.physical.spoolerDirection = !configuration.physical.spoolerDirection;
			spooler.setDirection();

			break;

			case 'D':
			spooler.disable();
			activeMenu->display();
			return;
			break;

		}
	}

	// MicroStepping test
	lcd.clear();
	lcd.print(F("Microsteping Test"));
	delay(5000);
	lcd.clear();
	lcd.print(F("Mark the Roller. "));
	lcd.setCursor(0,1);
	lcd.print(F("Attempting 1 rev"));
	lcd.setCursor(0,2);
	lcd.print(F("A) Begin"));
	lcd.setCursor(0,3);
	lcd.print(F("B) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}
	lcd.clear();
	lcd.print(F("Rotating 1 rev..."));
	spooler.enable();
	pinMode(6,OUTPUT);

	spooler.enable();
	float rpm = 10.0;
	spooler.setRPM(rpm);
	delay(1000.0*60.0/rpm);
	spooler.disable();

	lcd.clear();
	lcd.print(F("If spooler didn't"));
	lcd.setCursor(0,1);
	lcd.print(F("make 1 rev, check"));
	lcd.setCursor(0,2);
	lcd.print(F("the wiring and"));
	lcd.setCursor(0,3);
	lcd.print(F("microstep settings"));
	delay(5000);

	//Test Roller/spool ratio diameter
	lcd.clear();
	lcd.print(F("Roller/Disk Test"));
	delay(5000);
	lcd.clear();
	lcd.print(F("Place roller on Disk"));
	lcd.setCursor(0,1);
	lcd.print(F("press Stop at 1 rev."));
	lcd.setCursor(0,2);
	lcd.print(F("A) Begin"));
	lcd.setCursor(0,3);
	lcd.print(F("B) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}
	spooler.enable();
	rpm = 20.0;
	spooler.setRPM(rpm);
	unsigned long startTime = millis();
	lcd.clear();
	lcd.print(F("press Stop at 1 rev."));
	lcd.setCursor(0,1);
	lcd.print(F("A) Stop"));
	lcd.setCursor(0,2);
	lcd.print(F("B) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			outfeed.disable();
			activeMenu->display();
			return;
		}
	}

	spooler.disable();
	unsigned long stopTime = millis();
	configuration.physical.spoolerMotorRollerRadius = 1.0;
	configuration.physical.spoolerDiskRadius = (rpm*(float)(stopTime-startTime))/(1000.0*60.0);

	//Don't forget to check spool dimensions
	lcd.clear();
	lcd.print(F("Don't forget to set "));
	lcd.setCursor(0,1);
	lcd.print(F("the spool Dimensions"));
	lcd.setCursor(0,2);
	lcd.print(F("in the spooler menu"));
	delay(5000);

	//Save the settings
	lcd.clear();
	lcd.print(F("Save Settings?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			configuration.saveConfig();
			waitForResponse = false;
		}

		if (key == 'B') {
			waitForResponse = false;
		}
	}
	activeMenu->display();
}
#endif

void beginBarrelTest(){
	activeMenu = &barrelTestMenu;
	activeMenu->reset();
	barrel.setMode(MANUAL);
	strcpy(barrelMode, "Off");
	barrel.setDutyCycle(0);
	currentState = BARREL_TEST;
}
void barrelTest(){
	barrel.activate();
}

void exitBarrelTest(){
	barrel.off();
	strcpy(barrelMode,"Off");
	currentState = STANDBY;
	activeMenu = &mainMenu;
}

void beginNozzleTest(){
	activeMenu = &nozzleTestMenu;
	activeMenu->reset();
	nozzle.setMode(MANUAL);
	strcpy(nozzleMode, "Off");
	nozzle.setDutyCycle(0);
	currentState = NOZZLE_TEST;
}
void nozzleTest(){
	nozzle.activate();
}

void exitNozzleTest(){
	nozzle.off();
	strcpy(nozzleMode, "Off");
	currentState = STANDBY;
	activeMenu = &mainMenu;
}

void beginStarveFeederTest(){
	activeMenu = &starveFeederTestMenu;
	activeMenu->reset();
	starveFeeder.loadConfig();
	currentState = STANDBY;
}

void sendCyclesToStarveFeeder(){
	starveFeeder.loadConfig();
	starveFeeder.setCycles(cyclesToSendToStarveFeeder);
}

void sendTimeToStarveFeeder(){
	starveFeeder.loadConfig();
	starveFeederStopTime = millis()+(unsigned long)timeToSendToStarveFeeder*60L*1000L;
	Serial.print("StarveFeederStopTime: ");
	Serial.println(starveFeederStopTime);	
	starveFeeder.on();
	currentState = STARVE_FEEDER_TEST;
}

void starveFeederTest(){
	if (millis() >= starveFeederStopTime){
		Serial.println("Turning Starve feeder off");
		starveFeeder.off();
		currentState = STANDBY;
	}
}

void stopStarveFeeder(){
	starveFeeder.off();
	currentState = STANDBY;
}

void exitStarveFeederTest(){
	starveFeeder.off();
	currentState = STANDBY;
	activeMenu = &mainMenu;
}





