


boolean running;

float gramsPerMin = 7.5;
float gramsPerSec = (gramsPerMin/60.0);
unsigned long endTime;
int stepInterval = 400;


void initializeStarveFeeder(){
 pinMode(directionPin ,OUTPUT);
 pinMode(enablePin ,OUTPUT);
 pinMode(stepPin ,OUTPUT);
 digitalWrite(directionPin, HIGH);
 digitalWrite(enablePin, HIGH);
}
 
void runStarveFeeder(){
//  if (millis()<endTime){
  stepMotor();
//  } else {
//    running = false;
//    disableStepper(1); 
//    disableStepper(2); 
//    disableStepper(3);
//    relayOff();
//    nozzleOff();
//    feederOff();
//    currentState = SELECT_PROFILE;
//    return;
//  }
}

 
void stepMotor(){
  static unsigned long now;
  static unsigned long stepTime = 0L;
  now = micros();
  if (running && now>= stepTime){
   PORTL = PORTL | B00001000;
   PORTL = PORTL & B11110111;
   stepTime = now + (long)stepInterval;//this won't be accurate b/c now will not always be spaced out by stepInterval
  }
}

void feederOn(){
//  endTime = millis()+60000L;
  running = true;
  digitalWrite(enablePin, LOW);
}

void feederOff(){
  running = false;
  digitalWrite(enablePin, HIGH);
}

boolean getFeederState(){
  return running;
}


float getFeedRate(){
  return gramsPerMin;
}

void setFeedRate(float feedRate){
  gramsPerMin = feedRate;
  gramsPerSec = (gramsPerMin/60.0);
}

void increaseFeedRate(){
 stepInterval -= 10; 
}

void decreaseFeedRate(){
 stepInterval += 10; 
}


float calcOutfeedRPM(){
 return (gramsPerMin*1.03*1000.0*2.0)/(PI*diaSetPoint*diaSetPoint*ro*PI);
}
