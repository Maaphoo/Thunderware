//Maintain this file using an excel spread sheet so that it is easier to keep all of the linkages correct.

#ifndef MenuData_h
#define MenuData_h



//MenuItem Text strings
const char rootStr[] PROGMEM = "Main Menu";
const char selectProfileStr[] PROGMEM = "Select Profile";
const char calibrateStr[] PROGMEM = "Calibrate";
const char auxiliaryStr[] PROGMEM = "Auxiliary";
const char profile0Str[] PROGMEM = "1)";
const char profile1Str[] PROGMEM = "2)";
const char profile2Str[] PROGMEM = "3)";
const char profile3Str[] PROGMEM = "4)";
const char profile4Str[] PROGMEM = "5)";
const char profile5Str[] PROGMEM = "6)";
const char profile6Str[] PROGMEM = "7)";
const char profile7Str[] PROGMEM = "8)";
const char profile8Str[] PROGMEM = "9)";
const char profile9Str[] PROGMEM = "10)";
const char defaultProfileStr[] PROGMEM = "Default Profile";
const char extrudeStr[] PROGMEM = "Extrude";
const char saveProfileStr[] PROGMEM = "Save Profile";
const char profileNameStr[] PROGMEM = "Name";
const char diaSetPointStr[] PROGMEM = "Diameter";
const char densityStr[] PROGMEM = "Density";
const char toleranceStr[] PROGMEM = "Tolerance";
const char gramsPerMinStr[] PROGMEM = "Grams/Min";
const char augerRPMStr[] PROGMEM = "Auger RPM";
const char outfeedRPMStr[] PROGMEM = "Outfeed RPM";
const char outfeedKpStr[] PROGMEM = "Outfeed Kp";
const char outfeedKiStr[] PROGMEM = "Outfeed Ki";
const char outfeedKdStr[] PROGMEM = "Outfeed Pd";
const char soakTimeStr[] PROGMEM = "Soak Time";
const char barrelSetTempStr[] PROGMEM = "Barrel Set Temp";
const char nozzleSetTempStr[] PROGMEM = "Nozzle Set Temp";
const char minTempStr[] PROGMEM = "Min Temp";
const char maxTempStr[] PROGMEM = "Max Temp";
const char maxPreheatTimeStr[] PROGMEM = "MaxPreheatTime";
const char saveConfigStr[] PROGMEM = "Save Configuration";
const char starveFeederConfigStr[] PROGMEM = "StarveFeeder";
const char augerConfigStr[] PROGMEM = "Auger";
const char barrelConfigStr[] PROGMEM = "Barrel";
const char nozzleConfigStr[] PROGMEM = "Nozzle";
const char outfeedConfigStr[] PROGMEM = "Outfeed";
const char spoolerConfigStr[] PROGMEM = "Spooler";
const char testStarveFeederStr[] PROGMEM = "Test Starve Feeder";
const char starveFeederSlaveAddressStr[] PROGMEM = "Slave Address";
const char starveFeederLumpMassStr[] PROGMEM = "Lump Mass";
const char starveFeederHomePositionStr[] PROGMEM = "Home Position";
const char starveFeederDumpPositionStr[] PROGMEM = "Dump Position";
const char starveFeederStepDelayStr[] PROGMEM = "Step Delay";
const char starveFeederHomingStepDelayStr[] PROGMEM = "Homing Delay";
const char starveFeederOverRotationStr[] PROGMEM = "Over Rotation";
const char starveFeederDirectionStr[] PROGMEM = "Direction";
const char starveFeederVibDutyCycleStr[] PROGMEM = "DutyCycle";
const char starveFeederStartupDutyCycleStr[] PROGMEM = "Startup DutyCycle";
const char starveFeederMaxDutyCycleStr[] PROGMEM = "MaxDutyCycle";
const char starveFeederMinFillTimeStr[] PROGMEM = "MinFillTime";
const char starveFeederMaxFillTimeStr[] PROGMEM = "MaxFillTime";
const char starveFeederStartupTimeStr[] PROGMEM = "Startup Time";
const char starveFeederDebounceTimeStr[] PROGMEM = "Debounce Time";
const char testAugerStr[] PROGMEM = "Test Auger";
const char augerPinSetStr[] PROGMEM = "Pin Set";
const char augerStepModeStr[] PROGMEM = "Step Mode";
const char augerDirectionStr[] PROGMEM = "Direction";
const char augerEnableStr[] PROGMEM = "Enable";
const char augerGearRatioStr[] PROGMEM = "Gear Ration";
const char testBarrelStr[] PROGMEM = "Test Barrel";
const char timeBaseStr[] PROGMEM = "Time Base";
const char barrelMaxDutyCycleStr[] PROGMEM = "Max Duty Cycle";
const char barrelMinDutyCycleStr[] PROGMEM = "Min Duty Cycle";
const char barrelKpStr[] PROGMEM = "Kp";
const char barrelKiStr[] PROGMEM = "Ki";
const char barrelKdStr[] PROGMEM = "Kd";
const char barrelTRNomStr[] PROGMEM = "Ther Resist Nom";
const char barrelTTNomStr[] PROGMEM = "Ther Temp Nom";
const char barrelTNumSamplesStr[] PROGMEM = "Ther Num Samples";
const char barrelTBCoefficientStr[] PROGMEM = "Ther B Coeff";
const char barrelTSeriesResistorStr[] PROGMEM = "Ther Series Resist";
const char testNozzleStr[] PROGMEM = "Test Nozzle";
const char nozzlePinStr[] PROGMEM = "Pin";
const char nozzleMaxDutyCycleStr[] PROGMEM = "Max Duty Cycle";
const char nozzleMinDutyCycleStr[] PROGMEM = "Min Duty Cycle";
const char nozzleKpStr[] PROGMEM = "Kp";
const char nozzleKiStr[] PROGMEM = "Ki";
const char nozzleKdStr[] PROGMEM = "Kd";
const char nozzleSampleTimeStr[] PROGMEM = "Sample Time";
const char nozzleTRNomStr[] PROGMEM = "Ther Resist Nom";
const char nozzleTTNomStr[] PROGMEM = "Ther Temp Nom";
const char nozzleTNumSamplesStr[] PROGMEM = "Ther Num Samples";
const char nozzleTBCoefficientStr[] PROGMEM = "Ther B Coeff";
const char nozzleTSeriesResistorStr[] PROGMEM = "Ther Series Resist";
const char testOutfeedStr[] PROGMEM = "Test Outfeed";
const char outfeedPinSetStr[] PROGMEM = "Pin Set";
const char outfeedStepModeStr[] PROGMEM = "Step Mode";
const char outfeedDirectionStr[] PROGMEM = "Direction";
const char outfeedEnableStr[] PROGMEM = "Enable";
const char outfeedRollerRadiusStr[] PROGMEM = "Roller Radius";
const char outfeedMaxRPMStr[] PROGMEM = "Max RPM";
const char outfeedMinRPMStr[] PROGMEM = "Min RPM";
const char testSpoolerStr[] PROGMEM = "Test Spooler";
const char spoolerPinSetStr[] PROGMEM = "Pin Set";
const char spoolerStepModeStr[] PROGMEM = "Step Mode";
const char spoolerDirectionStr[] PROGMEM = "Direction";
const char spoolerEnableStr[] PROGMEM = "Enable";
const char spoolerDiskRadiusStr[] PROGMEM = "Disk Radius";
const char spoolerCoreRadiusStr[] PROGMEM = "Core Radius";
const char spoolerTraverseLengthStr[] PROGMEM = "Traverse Len";
const char spoolerMotorRollerRadiusStr[] PROGMEM = "Roller Radius";
const char feedStr[] PROGMEM = "Feed Plastic";
const char measureFilametStr[] PROGMEM = "Measure Filament";
const char resetEEPROMStr[] PROGMEM = "Reset EEPROM";
const char preheatRootStr[] PROGMEM = "Preheating. . .";
const char barrelTempStr[] PROGMEM = "Barrel Temp";
const char nozzleTempStr[] PROGMEM = "Nozzle Temp";
const char skipPreheatStr[] PROGMEM = "Skip Preheat";
const char soakRootStr[] PROGMEM = "Soaking. . .";
const char soakTimeRemainingStr[] PROGMEM = "Time Remaining";
const char increaseSoakTimeStr[] PROGMEM = "Increase Soak Time";
const char decreaseSoakTimeStr[] PROGMEM = "Decrease Soak Time";
const char skipSoakStr[] PROGMEM = "Skip Soak";
const char homeStarveFeederStr[] PROGMEM = "Home";
const char dumpStr[] PROGMEM = "Dump";
const char loadFilamentRootStr[] PROGMEM = "Load Filament. . .";
const char loadFilamentRemainingTimeStr[] PROGMEM = "Time Remaining";
const char filamentLoadedStr[] PROGMEM = "Filament Loaded";
const char loadFilamentAddTimeStr[] PROGMEM = "Add Time";
const char starveFeederModeStr[] PROGMEM = "Starve Feeder";
const char baseOutfeedOnGPMStr[] PROGMEM = "Base Outfeed on GPM";
const char extrudeRootStr[] PROGMEM = "Extruding. . .";
const char filamentDiameterStr[] PROGMEM = "Diameter";
const char gramsExtrudedStr[] PROGMEM = "Grams Extruded";
const char nozzleTestRootStr[] PROGMEM = "Nozzle Test";
const char nozzleModeStr[] PROGMEM = "Status";
const char barrelTestRootStr[] PROGMEM = "Barrel Test";
const char barrelModeStr[] PROGMEM = "Status";
const char starveFeederTestRootStr[] PROGMEM = "Starve Feeder Test";
const char sendCyclesStr[] PROGMEM = "Send Cycles";
const char cyclesToSendToStarveFeederStr[] PROGMEM = "Cycles to send";
const char sendTimeStr[] PROGMEM = "Send Time";
const char timeToSendToStarveFeederStr[] PROGMEM = "Time to send";
const char stopStr[] PROGMEM = "Stop";

//Variables for holding Menu values
double barrelTemp;
double nozzleTemp;
char loadFilamentTimeRemaining[6];
char starveFeederMode[4] = "Off";
char soakTimeRemaining[6];
char nozzleMode[4];
char barrelMode[4];
int gramsExtruded;
float diameter = 1.75;
int cyclesToSendToStarveFeeder = 10;
int timeToSendToStarveFeeder = 4;
unsigned long starveFeederStopTime;
char feedMode[4] = "Off";//starve feeder feeding plastic or not

//Menu Action methods
void testAuger();
// void testBarrel();
// void testNozzle();
void testOutfeed();
void testSpooler();
void beginBarrelTest();
void exitBarrelTest();
void beginNozzleTest();
void exitNozzleTest();
void changeBarrelMode();
void changeNozzleMode();
void beginStarveFeederTest();
/*void homeStarveFeederStr();*/
void sendTimeToStarveFeeder();
void sendCyclesToStarveFeeder();
void stopStarveFeeder();
void exitStarveFeederTest();

void measureFilament(){}

const Menu::MenuItem mainItems[] PROGMEM =
{
	{rootStr, -1, 1, NULL, 0, Menu::TITLE, NULL},
	{selectProfileStr, 0, 4, NULL, 0, Menu::TITLE, NULL},
	{calibrateStr, 0, 33, NULL, 0, Menu::TITLE, NULL},
	{auxiliaryStr, 0, 104, NULL, 0, Menu::TITLE, NULL},
	{profile0Str, 1, 15, &configuration.profileNames[0], 0, Menu::TITLE_STRING, &loadProfile0},
	{profile1Str, 1, 15, &configuration.profileNames[1], 0, Menu::TITLE_STRING, &loadProfile1},
	{profile2Str, 1, 15, &configuration.profileNames[2], 0, Menu::TITLE_STRING, &loadProfile2},
	{profile3Str, 1, 15, &configuration.profileNames[3], 0, Menu::TITLE_STRING, &loadProfile3},
	{profile4Str, 1, 15, &configuration.profileNames[4], 0, Menu::TITLE_STRING, &loadProfile4},
	{profile5Str, 1, 15, &configuration.profileNames[5], 0, Menu::TITLE_STRING, &loadProfile5},
	{profile6Str, 1, 15, &configuration.profileNames[6], 0, Menu::TITLE_STRING, &loadProfile6},
	{profile7Str, 1, 15, &configuration.profileNames[7], 0, Menu::TITLE_STRING, &loadProfile7},
	{profile8Str, 1, 15, &configuration.profileNames[8], 0, Menu::TITLE_STRING, &loadProfile8},
	{profile9Str, 1, 15, &configuration.profileNames[9], 0, Menu::TITLE_STRING, &loadProfile9},
	{defaultProfileStr, 1, 15, NULL, 0, Menu::TITLE, &loadDefaultProfile},
	{extrudeStr, 4, -1, NULL, 0, Menu::TITLE, &actionExtrude},
	{saveProfileStr, 4, -1, NULL, 0, Menu::TITLE, &saveCurrentProfile},
	{profileNameStr, 4, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
	{diaSetPointStr, 4, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
	{densityStr, 4, -1, &configuration.profile.density, 2, Menu::DOUBLE, NULL},
	{toleranceStr, 4, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
	{gramsPerMinStr, 4, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, NULL},
	{augerRPMStr, 4, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
	{outfeedRPMStr, 4, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
	{outfeedKpStr, 4, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, NULL},
	{outfeedKiStr, 4, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, NULL},
	{outfeedKdStr, 4, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, NULL},
	{soakTimeStr, 4, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
	{barrelSetTempStr, 4, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
	{nozzleSetTempStr, 4, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
	{minTempStr, 4, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
	{maxTempStr, 4, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
	{maxPreheatTimeStr, 4, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL},
	{saveConfigStr, 2, -1, NULL, 0, Menu::ACTION, &saveConfig},
	{starveFeederConfigStr, 2, 40, NULL, 0, Menu::TITLE, NULL},
	{augerConfigStr, 2, 56, NULL, 0, Menu::TITLE, NULL},
	{barrelConfigStr, 2, 62, NULL, 0, Menu::TITLE, NULL},
	{nozzleConfigStr, 2, 74, NULL, 0, Menu::TITLE, NULL},
	{outfeedConfigStr, 2, 87, NULL, 0, Menu::TITLE, NULL},
	{spoolerConfigStr, 2, 95, NULL, 0, Menu::TITLE, NULL},
	{testStarveFeederStr, 34, -1, NULL, 0, Menu::ACTION, &beginStarveFeederTest},
	{starveFeederSlaveAddressStr, 34, -1, &configuration.physical.starveFeederSlaveAddress, 0, Menu::INT, NULL},
	{starveFeederLumpMassStr, 34, -1, &configuration.physical.starveFeederLumpMass, 2, Menu::FLOAT, NULL},
	{starveFeederHomePositionStr, 34, -1, &configuration.physical.starveFeederHomePosition, 0, Menu::INT, NULL},
	{starveFeederDumpPositionStr, 34, -1, &configuration.physical.starveFeederDumpPosition, 0, Menu::INT, NULL},
	{starveFeederStepDelayStr, 34, -1, &configuration.physical.starveFeederStepDelay, 0, Menu::INT, NULL},
	{starveFeederHomingStepDelayStr, 34, -1, &configuration.physical.starveFeederHomingStepDelay, 0, Menu::INT, NULL},
	{starveFeederOverRotationStr, 34, -1, &configuration.physical.starveFeederOverRotation, 0, Menu::INT, NULL},
	{starveFeederDirectionStr, 34, -1, &configuration.physical.starveFeederDirection, 0, Menu::BOOLEAN, NULL},
	{starveFeederVibDutyCycleStr, 34, -1, &configuration.physical.starveFeederVibDutyCycle, 0, Menu::INT, NULL},
	{starveFeederStartupDutyCycleStr, 34, -1, &configuration.physical.starveFeederStartupDutyCycle, 0, Menu::INT, NULL},
	{starveFeederMaxDutyCycleStr, 34, -1, &configuration.physical.starveFeederMaxDutyCycle, 0, Menu::INT, NULL},
	{starveFeederMinFillTimeStr, 34, -1, &configuration.physical.starveFeederMinFillTime, 0, Menu::INT, NULL},
	{starveFeederMaxFillTimeStr, 34, -1, &configuration.physical.starveFeederMaxFillTime, 0, Menu::INT, NULL},
	{starveFeederStartupTimeStr, 34, -1, &configuration.physical.starveFeederStartupTime, 0, Menu::INT, NULL},
	{starveFeederDebounceTimeStr, 34, -1, &configuration.physical.starveFeederDebounceTime, 0, Menu::INT, NULL},
	{testAugerStr, 35, -1, NULL, 0, Menu::ACTION, &testAuger},
	{augerPinSetStr, 35, -1, &configuration.physical.augerPinSet, 0, Menu::INT, NULL},
	{augerStepModeStr, 35, -1, &configuration.physical.augerStepMode, 0, Menu::INT, NULL},
	{augerDirectionStr, 35, -1, &configuration.physical.augerDirection, 0, Menu::BOOLEAN, NULL},
	{augerEnableStr, 35, -1, &configuration.physical.augerEnable, 0, Menu::BOOLEAN, NULL},
	{augerGearRatioStr, 35, -1, &configuration.physical.augerGearRatio, 2, Menu::FLOAT, NULL},
	{testBarrelStr, 36, -1, NULL, 0, Menu::ACTION, &beginBarrelTest},
	{timeBaseStr, 36, -1, &configuration.physical.timeBase, 0, Menu::INT, NULL},
	{barrelMaxDutyCycleStr, 36, -1, &configuration.physical.barrelMax, 0, Menu::DOUBLE, NULL},
	{barrelMinDutyCycleStr, 36, -1, &configuration.physical.barrelMin, 0, Menu::DOUBLE, NULL},
	{barrelKpStr, 36, -1, &configuration.physical.barrelKp, 2, Menu::DOUBLE, NULL},
	{barrelKiStr, 36, -1, &configuration.physical.barrelKi, 2, Menu::DOUBLE, NULL},
	{barrelKdStr, 36, -1, &configuration.physical.barrelKd, 2, Menu::DOUBLE, NULL},
	{barrelTRNomStr, 36, -1, &configuration.physical.barrelTRNom, 0, Menu::UNSIGNED_LONG, NULL},
	{barrelTTNomStr, 36, -1, &configuration.physical.barrelTTNom, 0, Menu::INT, NULL},
	{barrelTNumSamplesStr, 36, -1, &configuration.physical.barrelTNumSamples, 0, Menu::INT, NULL},
	{barrelTBCoefficientStr, 36, -1, &configuration.physical.barrelTBCoefficient, 0, Menu::INT, NULL},
	{barrelTSeriesResistorStr, 36, -1, &configuration.physical.barrelTSeriesResistor, 0, Menu::INT, NULL},
	{testNozzleStr, 37, -1, NULL, 0, Menu::TITLE, &beginNozzleTest},
	{nozzlePinStr, 37, -1, &configuration.physical.nozzlePin, 0, Menu::INT, NULL},
	{nozzleMaxDutyCycleStr, 37, -1, &configuration.physical.nozzleMax, 0, Menu::DOUBLE, NULL},
	{nozzleMinDutyCycleStr, 37, -1, &configuration.physical.nozzleMin, 0, Menu::DOUBLE, NULL},
	{nozzleKpStr, 37, -1, &configuration.physical.nozzleKp, 2, Menu::DOUBLE, NULL},
	{nozzleKiStr, 37, -1, &configuration.physical.nozzleKi, 2, Menu::DOUBLE, NULL},
	{nozzleKdStr, 37, -1, &configuration.physical.nozzleKd, 2, Menu::DOUBLE, NULL},
	{nozzleSampleTimeStr, 37, -1, &configuration.physical.nozzleSampleTime, 0, Menu::INT, NULL},
	{nozzleTRNomStr, 37, -1, &configuration.physical.nozzleTRNom, 0, Menu::UNSIGNED_LONG, NULL},
	{nozzleTTNomStr, 37, -1, &configuration.physical.nozzleTTNom, 0, Menu::INT, NULL},
	{nozzleTNumSamplesStr, 37, -1, & configuration.physical.nozzleTNumSamples, 0, Menu::INT, NULL},
	{nozzleTBCoefficientStr, 37, -1, &configuration.physical.nozzleTBCoefficient, 0, Menu::INT, NULL},
	{nozzleTSeriesResistorStr, 37, -1,  &configuration.physical.nozzleTSeriesResistor, 0, Menu::INT, NULL},
	{testOutfeedStr, 38, -1, NULL, 0, Menu::ACTION, &testOutfeed},
	{outfeedPinSetStr, 38, -1, &configuration.physical.outfeedPinSet, 0, Menu::INT, NULL},
	{outfeedStepModeStr, 38, -1, &configuration.physical.outfeedStepMode, 0, Menu::INT, NULL},
	{outfeedDirectionStr, 38, -1, &configuration.physical.outfeedDirection, 0, Menu::BOOLEAN, NULL},
	{outfeedEnableStr, 38, -1, &configuration.physical.outfeedEnable, 0, Menu::BOOLEAN, NULL},
	{outfeedRollerRadiusStr, 38, -1, &configuration.physical.outfeedRollerRadius, 2, Menu::FLOAT, NULL},
	{outfeedMaxRPMStr, 38, -1, &configuration.physical.outfeedMaxRPM, 2, Menu::DOUBLE, NULL},
	{outfeedMinRPMStr, 38, -1, &configuration.physical.outfeedMinRPM, 2, Menu::DOUBLE, NULL},
	{testSpoolerStr, 39, -1, NULL, 0, Menu::ACTION, &testSpooler},
	{spoolerPinSetStr, 39, -1, &configuration.physical.spoolerPinSet, 0, Menu::INT, NULL},
	{spoolerStepModeStr, 39, -1, &configuration.physical.spoolerStepMode, 0, Menu::INT, NULL},
	{spoolerDirectionStr, 39, -1, &configuration.physical.spoolerDirection, 0, Menu::BOOLEAN, NULL},
	{spoolerEnableStr, 39, -1, &configuration.physical.spoolerEnable, 0, Menu::BOOLEAN, NULL},
	{spoolerDiskRadiusStr, 39, -1, &configuration.physical.spoolerDiskRadius, 2, Menu::FLOAT, NULL},
	{spoolerCoreRadiusStr, 39, -1, &configuration.physical.spoolerCoreRadius, 2, Menu::FLOAT, NULL},
	{spoolerTraverseLengthStr, 39, -1, &configuration.physical.spoolerTraverseLength, 2, Menu::FLOAT, NULL},
	{spoolerMotorRollerRadiusStr, 39, -1, &configuration.physical.spoolerMotorRollerRadius, 2, Menu::FLOAT, NULL},
	{feedStr, 3, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
	{measureFilametStr, 3, -1, NULL, -1, Menu::ACTION, &measureFilament},
	{resetEEPROMStr, 3, -1, NULL, 0, Menu::ACTION, &resetEEPROM}
};

const Menu::MenuItem preheatItems[] PROGMEM =
{
	{preheatRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitPreheat},
	{barrelTempStr, 0, -1, &barrelTemp, 1, Menu::DOUBLE_LOCKED, },
	{nozzleTempStr, 0, -1, &nozzleTemp, 1, Menu::DOUBLE_LOCKED, },
	{barrelSetTempStr, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
	{nozzleSetTempStr, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
	{skipPreheatStr, 0, -1, NULL, 0, Menu::ACTION, &skipPreheat},
	{profileNameStr, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
	{diaSetPointStr, 0, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
	{toleranceStr, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
	{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, NULL},
	{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
	{augerRPMStr, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
	{outfeedRPMStr, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
	{outfeedKpStr, 0, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, NULL},
	{outfeedKiStr, 0, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, NULL},
	{outfeedKdStr, 0, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, NULL},
	{soakTimeStr, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
	{minTempStr, 0, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
	{maxTempStr, 0, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
	{maxPreheatTimeStr, 0, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL}
};

const Menu::MenuItem soakItems[] PROGMEM =
{
	{soakRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitSoak},
	{soakTimeRemainingStr, 0, -1, &soakTimeRemaining, 0, Menu::STRING_LOCKED, NULL},
	{barrelTempStr, 0, -1, &barrelTemp, 1, Menu::DOUBLE_LOCKED, NULL},
	{nozzleTempStr, 0, -1, &nozzleTemp, 1, Menu::DOUBLE_LOCKED, NULL},
	{increaseSoakTimeStr, 0, -1, NULL, 0, Menu::ACTION, &increaseSoakTime},
	{decreaseSoakTimeStr, 0, -1, NULL, 0, Menu::ACTION, &decreaseSoakTime},
	{skipSoakStr, 0, -1, NULL, 0, Menu::ACTION, &skipSoak},
	{barrelSetTempStr, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
	{nozzleSetTempStr, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
	{homeStarveFeederStr, 0, -1, NULL, 0, Menu::ACTION, &homeStarveFeeder},
	{dumpStr, 0, -1, NULL, 0, Menu::ACTION, &dump},
	{profileNameStr, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
	{diaSetPointStr, 0, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
	{toleranceStr, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
	{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, NULL},
	{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
	{augerRPMStr, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, NULL},
	{outfeedRPMStr, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, NULL},
	{outfeedKpStr, 0, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, NULL},
	{outfeedKiStr, 0, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, NULL},
	{outfeedKdStr, 0, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, NULL},
	{soakTimeStr, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
	{minTempStr, 0, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
	{maxTempStr, 0, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
	{maxPreheatTimeStr, 0, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL}
};

const Menu::MenuItem loadFilamentItems[] PROGMEM =
{
	{loadFilamentRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitLoadFilament},
	{loadFilamentRemainingTimeStr, 0, -1, &loadFilamentTimeRemaining, 0, Menu::STRING_LOCKED, NULL},
	{filamentLoadedStr, 0, -1, NULL, 0, Menu::ACTION, &filamentLoaded},
	{loadFilamentAddTimeStr, 0, -1, NULL, 0, Menu::ACTION, &loadFilamentAddTime},
	{starveFeederModeStr, 0, -1, &starveFeederMode, 0, Menu::STRING_LOCKED, &starveFeederChangeMode},
	{barrelSetTempStr, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
	{nozzleSetTempStr, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
	{profileNameStr, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
	{diaSetPointStr, 0, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
	{toleranceStr, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
	{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, &setGramsPerMin},
	{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
	{augerRPMStr, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, &setAugerRPM},
	{outfeedRPMStr, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, &setOutfeedRPM},
	{baseOutfeedOnGPMStr, 0, -1, NULL, 0, Menu::ACTION, &baseOutfeedRPMonGPM},
	{outfeedKpStr, 0, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, &setOutfeedTunings},
	{outfeedKiStr, 0, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, &setOutfeedTunings},
	{outfeedKdStr, 0, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, &setOutfeedTunings},
	{soakTimeStr, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
	{minTempStr, 0, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
	{maxTempStr, 0, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
	{maxPreheatTimeStr, 0, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL}
};

const Menu::MenuItem extrudeItems[] PROGMEM =
{
	{extrudeRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitExtrude},
	{filamentDiameterStr, 0, -1, &diameter, 0, Menu::DOUBLE_LOCKED, NULL},
	{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, &setGramsPerMin},
	{gramsExtrudedStr, 0, -1, &gramsExtruded, 0, Menu::INT_LOCKED, NULL},
	{barrelTempStr, 0, -1, &barrelTemp, 1, Menu::DOUBLE_LOCKED, NULL},
	{nozzleTempStr, 0, -1, &nozzleTemp, 1, Menu::DOUBLE_LOCKED, NULL},
	{augerRPMStr, 0, -1, &configuration.profile.augerRPM, 1, Menu::FLOAT, &setAugerRPM},
	{outfeedRPMStr, 0, -1, &configuration.profile.outfeedRPM, 1, Menu::DOUBLE, &setOutfeedRPM},
	{baseOutfeedOnGPMStr, 0, -1, NULL, 0, Menu::ACTION, &baseOutfeedRPMonGPM},
	{starveFeederModeStr, 0, -1, &starveFeederMode, 0, Menu::STRING_LOCKED, &starveFeederChangeMode},
	{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
	{barrelSetTempStr, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
	{nozzleSetTempStr, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
	{profileNameStr, 0, -1, &configuration.profile.name, 0, Menu::STRING, NULL},
	{diaSetPointStr, 0, -1, &configuration.profile.diaSetPoint, 2, Menu::DOUBLE, NULL},
	{toleranceStr, 0, -1, &configuration.profile.tolerance, 2, Menu::FLOAT, NULL},
	{outfeedKpStr, 0, -1, &configuration.profile.outfeedKp, 2, Menu::DOUBLE, &setOutfeedTunings},
	{outfeedKiStr, 0, -1, &configuration.profile.outfeedKi, 2, Menu::DOUBLE, &setOutfeedTunings},
	{outfeedKdStr, 0, -1, &configuration.profile.outfeedKd, 2, Menu::DOUBLE, &setOutfeedTunings},
	{soakTimeStr, 0, -1, &configuration.profile.soakTime, 0, Menu::DOUBLE, NULL},
	{minTempStr, 0, -1, &configuration.profile.minExtrudeTemp, 0, Menu::DOUBLE, NULL},
	{maxTempStr, 0, -1, &configuration.profile.maxTemp, 0, Menu::DOUBLE, NULL},
	{maxPreheatTimeStr, 0, -1, &configuration.profile.maxPreheatTime, 0, Menu::UNSIGNED_LONG, NULL}
};

const Menu::MenuItem nozzleTestItems[] PROGMEM =
{
	{nozzleTestRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitNozzleTest},
	{nozzleTempStr, 0, -1, &nozzleTemp, 1, Menu::DOUBLE_LOCKED, NULL},
	{nozzleSetTempStr, 0, -1, &configuration.profile.nozzleTemp, 0, Menu::DOUBLE, NULL},
	{nozzleModeStr, 0, -1, &nozzleMode, 0, Menu::STRING_LOCKED, &changeNozzleMode}
};

const Menu::MenuItem barrelTestItems[] PROGMEM =
{
	{barrelTestRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitBarrelTest},
	{barrelTempStr, 0, -1, &barrelTemp, 1, Menu::DOUBLE_LOCKED, NULL},
	{barrelSetTempStr, 0, -1, &configuration.profile.barrelTemp, 0, Menu::DOUBLE, NULL},
	{barrelModeStr, 0, -1, &barrelMode, 0, Menu::STRING_LOCKED, &changeBarrelMode}
};

const Menu::MenuItem starveFeederTestItems[] PROGMEM =
{
	{starveFeederTestRootStr, -1, 1, NULL, 0, Menu::TITLE, &exitStarveFeederTest},
	{homeStarveFeederStr, 0, -1, NULL, 0, Menu::ACTION, &homeStarveFeeder},
	{dumpStr, 0, -1, NULL, 0, Menu::ACTION, &dump},
	{feedStr, 0, -1, &feedMode, 0, Menu::STRING_LOCKED, &feed},
	{sendCyclesStr, 0, -1, NULL, 0, Menu::ACTION, &sendCyclesToStarveFeeder},
	{cyclesToSendToStarveFeederStr, 0, -1, &cyclesToSendToStarveFeeder, 0, Menu::INT, NULL},
	{sendTimeStr, 0, -1, NULL, 0, Menu::ACTION, &sendTimeToStarveFeeder},
	{timeToSendToStarveFeederStr, 0, -1, &timeToSendToStarveFeeder, 0, Menu::INT, NULL},
	{gramsPerMinStr, 0, -1, &configuration.profile.gramsPerMin, 2, Menu::FLOAT, NULL},
	{stopStr, 0, -1, NULL, 0, Menu::ACTION, &stopStarveFeeder},
	{starveFeederSlaveAddressStr, 0, -1, &configuration.physical.starveFeederSlaveAddress, 0, Menu::INT, NULL},
	{starveFeederLumpMassStr, 0, -1, &configuration.physical.starveFeederLumpMass, 2, Menu::FLOAT, NULL},
	{starveFeederHomePositionStr, 0, -1, &configuration.physical.starveFeederHomePosition, 0, Menu::INT, NULL},
	{starveFeederDumpPositionStr, 0, -1, &configuration.physical.starveFeederDumpPosition, 0, Menu::INT, NULL},
	{starveFeederStepDelayStr, 0, -1, &configuration.physical.starveFeederStepDelay, 0, Menu::INT, NULL},
	{starveFeederHomingStepDelayStr, 0, -1, &configuration.physical.starveFeederHomingStepDelay, 0, Menu::INT, NULL},
	{starveFeederOverRotationStr, 0, -1, &configuration.physical.starveFeederOverRotation, 0, Menu::INT, NULL},
	{starveFeederDirectionStr, 0, -1, &configuration.physical.starveFeederDirection, 0, Menu::BOOLEAN, NULL},
	{starveFeederVibDutyCycleStr, 0, -1, &configuration.physical.starveFeederVibDutyCycle, 0, Menu::INT, NULL},
	{starveFeederStartupDutyCycleStr, 0, -1, &configuration.physical.starveFeederStartupDutyCycle, 0, Menu::INT, NULL},
	{starveFeederMaxDutyCycleStr, 0, -1, &configuration.physical.starveFeederMaxDutyCycle, 0, Menu::INT, NULL},
	{starveFeederMinFillTimeStr, 0, -1, &configuration.physical.starveFeederMinFillTime, 0, Menu::INT, NULL},
	{starveFeederMaxFillTimeStr, 0, -1, &configuration.physical.starveFeederMaxFillTime, 0, Menu::INT, NULL},
	{starveFeederStartupTimeStr, 0, -1, &configuration.physical.starveFeederStartupTime, 0, Menu::INT, NULL},
	{starveFeederDebounceTimeStr, 0, -1, &configuration.physical.starveFeederDebounceTime, 0, Menu::INT, NULL}
};
#endif
