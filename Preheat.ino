void preheat(){
  //delay(4000);//Wait for 12 power to come on line. Remove later.
  now = millis();
  computeTime = now+2000L;
  reportTime = now+1000L;
  

  //Display info on LCD
  displayPreheatScreen();

  barrelPID.SetMode(MANUAL);
  barrelHeater.setDutyCycle(80);//go full bore until close to the set temperature

  barrelPID.SetTunings(consKp, consKi, consKd);

 boolean initialRise=true;

 // reportSettings();
// reportCurrentMeasurements();

  //While the temperature is more than three degrees away from the setpoint
  while(barrelTemp < barrelSetPoint-3){  
  
  key = kpd.getKey();
  
  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }
  
  switch(key){
    case 'B'://increase Tempature setpoint
     { 
      lcd.clear();
      lcd.write("Increase temp to:");
      lcd.setCursor(0,1);
      barrelSetPoint = barrelSetPoint+5;
      char tempSetPointString[10];
      dtostrf(barrelSetPoint, 1,2,tempSetPointString);
      lcd.write(tempSetPointString);
              
      Serial.print("Increased barrelTemp set point to: ");
      Serial.println(barrelTemp);
  
      break;
     } 
    case 'C'://decrease temp set point
     { 
      lcd.clear();
      lcd.write("Decrease temp to:");
      lcd.setCursor(0,1);
      barrelSetPoint = barrelSetPoint-5;
      char tempSetPointString[10];
      dtostrf(barrelTemp, 1,2,tempSetPointString);
      lcd.write(tempSetPointString);
  
      Serial.print("Decreased temp set point to: ");
      Serial.println(barrelTemp);
  
      break;
     } 
   
     case '1'://Skip soaking period
      barrelSetPoint = barrelSetPoint+5;
      Serial.print("TempSetPoint increased to: ");
      Serial.println(barrelTemp);
      
      break;
    case '4':
      barrelSetPoint = barrelSetPoint-5;
      Serial.print("TempSetPoint decreased to: ");
      Serial.println(barrelSetPoint);
      break;
     
     case'8':
     consKp+=.1;
      Serial.print("Kp increased to: ");
      Serial.println(consKp);
      barrelPID.SetTunings(consKp,consKi,consKd);
      break;
      
    case '0':
      consKp-=.1;
      Serial.print("Kp decreased to: ");
      Serial.println(consKp);
      barrelPID.SetTunings(consKp,consKi,consKd);
      break;    
  
      case 'A':
      barrelHeater.off();
      nozzleHeater.off();
      currentState = SELECT_PROFILE;
      return;
      
      case 'D':
      lcd.begin(20, 4);
      break;
      
      case '*':
      currentState = SOAK;
      return;
  }
    now = millis();
    barrelHeater.activate();

    if (alternateThermistors){
      barrelTh.sampleTemp();
      alternateThermistors = !alternateThermistors;
    }else{
      nozzleTh.sampleTemp();
      alternateThermistors = !alternateThermistors;
    }

    updateDiameter();    
        
    if (now>=computeTime){
      barrelTemp = barrelTh.getTemp();
      nozzleTemp =nozzleTh.getTemp();
     
      if(barrelTemp>(barrelSetPoint-7) && initialRise){
        barrelPID.SetTunings(consKp, consKi, consKd);
//        barrelPID.SetMode(MANUAL);
//        barrelDutyCycle=20;
        barrelPID.SetMode(AUTOMATIC);        
        Serial.println();
        initialRise = false;
      }

      barrelPID.Compute();
      barrelHeater.setDutyCycle(barrelDutyCycle);
      nozzlePID.Compute();

      nozzleHeater.setPWM(nozzleDutyCycle);
//      setNozzlePWM();
      
      if (heaterError()) {return;}

      getMedianDia();

      computeTime += 2000;
    }

    if (now >= reportTime){

    //Safety check

    reportCurrentMeasurements();
    reportTime = now+1000L;
    displayPreheatScreen();
    } 
  }
  barrelHeater.off();
  nozzleHeater.off();
//  atTempSetPointSound();
  currentState = SOAK;
}

void soak(){
  buzzer.setMsg(SOAKING);//Sound the buzzer to indicate the Soak Temperature has been reached
  now = millis();
  computeTime = now+2000L;
  reportTime = now+1000L;
  


  barrelPID.SetTunings(consKp, consKi, consKd);
  barrelPID.SetMode(MANUAL);
  barrelDutyCycle = 30;
  barrelPID.SetMode(AUTOMATIC);

  now=millis();
  goTime=now + soakTime*60L*1000L; 

  lcd.clear();

  Serial.print("Soaking Barrel at set point for ");
  Serial.print(soakTime);
  Serial.println(" minutes.");
  displaySoakScreen();



  while(now < goTime){
  
    key = kpd.getKey();

    //Allow for keyboard input as well
    if (Serial.available() > 0) {
      key = (char)Serial.read();
    }
    switch(key){
      case 'A':
         barrelHeater.off();
         nozzleHeater.off();
         currentState = SELECT_PROFILE;
         return;
         
      case 'B'://increase Tempature setpoint
       { 
        lcd.clear();
        lcd.write("Increase temp to:");
        lcd.setCursor(0,1);
        barrelSetPoint = barrelSetPoint+5;
        char tempSetPointString[10];
        dtostrf(barrelSetPoint, 1,2,tempSetPointString);
        lcd.write(tempSetPointString);
                
        Serial.print("Increased temp set point to: ");
        Serial.println(barrelSetPoint);

        break;
       } 
      case 'C'://decrease temp set point
       { 
        lcd.clear();
        lcd.write("Decrease temp to:");
        lcd.setCursor(0,1);
        barrelSetPoint = barrelSetPoint-5;
        char tempSetPointString[10];
        dtostrf(barrelSetPoint, 1,2,tempSetPointString);
        lcd.write(tempSetPointString);

        Serial.print("Decreased temp set point to: ");
        Serial.println(barrelSetPoint);

        break;
       } 
     case '*'://Skip soaking period
      {
        lcd.clear();
        lcd.write("Skip Soak?");
        lcd.setCursor(0,1);
        lcd.write("Press * to Skip");
        lcd.setCursor(0,2);
        lcd.write("Press D to continue");
        boolean noInput = true;
        while (noInput){
          barrelHeater.activate();
          key = kpd.getKey();
          //Allow for keyboard input as well
          if (Serial.available() > 0) {
            key = (char)Serial.read();
          }
          if (key == '*'){
            currentState = EXTRUDE_AUTOMATIC;
            return;
          }
          if (key == 'D'){
            noInput = false;
          }
        }
        Serial.println("Pressed * or D");
       break;
      }
       
       case '1'://Increase soak time by 1 min
           lcd.clear();
           lcd.write("Increasing Time");
           goTime = goTime+1000L*60L;

       break;
       case '4'://Decrease soak time by 1 min
           goTime = goTime-1000L*60L;
           if (goTime-now < 0){
             currentState = EXTRUDE_AUTOMATIC;
             return;
           lcd.clear();
           lcd.write("Decreasing Time");
           } 
       break; 

       case '7':
       
       if (barrelPID.GetMode() == MANUAL){
        barrelPID.SetMode(AUTOMATIC);
        Serial.print("Barrel PID set to Automatic");       
       }else{
        barrelPID.SetMode(MANUAL);
        Serial.print("Barrel PID set to Manual");       
       }
       
       break;
       
       case'8':
        consKp+=.1;
        Serial.print("ConsKp increased to: ");
        Serial.println(consKp);
        barrelPID.SetTunings(consKp,consKi,consKd);
        break;
        
      case '0':
        consKp-=.1;
        Serial.print("ConsKp decreased to: ");
        Serial.println(consKp);
        barrelPID.SetTunings(consKp,consKi,consKd);
        break;
      
           
       case'9':
        consKi+=.001;
        Serial.print("consKi increased to: ");
        Serial.println(consKi);
        barrelPID.SetTunings(consKp,consKi,consKd);
        break;
        
      case '#':
        consKi-=.001;
        Serial.print("consKi decreased to: ");
        Serial.println(consKi);
        barrelPID.SetTunings(consKp,consKi,consKd);
        break;
    
      case 'D':
      lcd.begin(20, 4);
      break;    
        

    }

    now=millis();
    barrelHeater.activate();
   
    if (alternateThermistors){
      barrelTh.sampleTemp();
      alternateThermistors = !alternateThermistors;
    }else{
      nozzleTh.sampleTemp();
      alternateThermistors = !alternateThermistors;
    }

    
    updateDiameter();
    
    if (now>=computeTime){
      
      barrelTemp = barrelTh.getTemp();
      nozzleTemp =nozzleTh.getTemp();
      
      barrelPID.Compute();
      barrelHeater.setDutyCycle(barrelDutyCycle);
      nozzlePID.Compute();
      nozzleHeater.setPWM(nozzleDutyCycle);
//      setNozzlePWM();
      
      getMedianDia();
      
      computeTime += 2000;
    }
    
    //Reporting status during heat up
    if (now >= reportTime){

    //Safety check
    if (heaterError()) {return;}

    //reportHeaterStatus1();
     reportCurrentMeasurements();
     reportTime = now+1000L;
     displaySoakScreen();

    }
  }
  
  Serial.println("Finished Soaking");
  barrelHeater.off();
  nozzleHeater.off();
//  soakCompleteSound();
  currentState = EXTRUDE_AUTOMATIC;
}

void displayPreheatScreen(){
    lcd.clear();
    char tempString[10];
    dtostrf(barrelSetPoint, 3,0,tempString);
    lcd.write("Preheating to ");
    lcd.write(tempString);
    lcd.write(" C");  

    lcd.setCursor(0,2);
    lcd.write("Current temp: ");
    updateTemp(15,2);
    lcd.write(" C");
} 

void updateTemp(int col, int row){
  lcd.setCursor(col,row);
  char tempInputString[10];
  dtostrf(barrelTemp, 3,0,tempInputString);
  lcd.write(tempInputString);
  }

void  displaySoakScreen(){
  lcd.clear();
  lcd.write("Soaking at ");
  char tempString[10];
  dtostrf(barrelSetPoint, 3,0,tempString);
  lcd.write(tempString);
  lcd.write(" C.");
  lcd.setCursor(0,1);
  lcd.write("Time: ");
  updateTime(6,1);
  lcd.setCursor(0,2);
  lcd.write("Temp: ");
  updateTemp(6,2);
  }
  
void updateTime(int col, int row){
  int timeLeft = (goTime-now)/1000;
  int minutes = timeLeft/60;
  int seconds = timeLeft%60;
  char minString[3];
  char secString[3];
  dtostrf(minutes, 2,0,minString);
  dtostrf(seconds, 2,0,secString);
  lcd.setCursor(col,row);
  lcd.write(minString);
  lcd.write(":");
  if (seconds<10){
     secString[0] = '0';
  }  
  lcd.write(secString);
}
  
void getPreheatInput(){

}

void getSoakInput(){

}

