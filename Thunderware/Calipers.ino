

void initializeCalipers(){
  //initialize calipers
  pinMode(CAL_CLK, INPUT_PULLUP);  // Clock pin = 2
  //digitalWrite(CAL_CLK, HIGH); // Activate Pull-Up Resistor
  pinMode(CAL_DATA, INPUT_PULLUP); // Data pin = 3
  //digitalWrite(CAL_DATA, HIGH); // Activate Pull-Up Resistor
  attachInterrupt(0, dataReceived, RISING);
 }
int bitCount;
int bitCountPrev;

void dataReceived() {  
 cli();
  unsigned char data = (PINE & (1<<PE5)); // read DATA value as soon as possible 
  nowCal = millis();
  if((nowCal - lastInterrupt > 15)) {
    finalValue = value;
    flag = true; 
   bitCountPrev = bitCount;
   bitCount=0;
  }
  value = (value << 1) | data;
  bitCount++;
  lastInterrupt = nowCal;
  sei();
}


void updateDiameter(){
  if (flag == true){

      finalValueReport = finalValue;
       // play arount with the 31 and 10 to see what values work best
      for (i = 31; i>=10;i--){
        bitWrite(finalValueGood, 31-i, bitRead(finalValue, i));
      }      
      reportValue = finalValueGood;

      caliperReading = ((float)(finalValueGood)/3226.84);
      if (caliperReading >1000){
        caliperReading = 0;
      }
//      Serial.print(" Dia: ");
//      Serial.print(caliperReading,3);
//      Serial.print("  ");
//      Serial.println(finalValueGood,BIN);      
      if (caliperCount<7){
      *(diaMeasurements+caliperCount)=caliperReading;
      caliperCount++;
      }
      
      caliperReadingInt =  (caliperReading * 1000L);

      finalValueGood = 0;
      flag = false;
  }
}

static int compareDia(const void *a, const void *b){
  if (*(double*)a>*(double*)b){
    return 1;
  } else if(*(double*)a<*(double*)b){
    return -1;
  }
  return 0;
}

void getMedianDia(){
  qsort (diaMeasurements, 7,sizeof(double), compareDia);
  medianDia = *(diaMeasurements+3);
  caliperCount=0;
}

