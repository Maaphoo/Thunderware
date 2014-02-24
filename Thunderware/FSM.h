#ifndef FSM_h
#define FSM_h

#include "config.h"
#include "StarveFeeder.h"

char diameterString[6];
char *diameterPtr;//pointer to char in diameterString.

void selectProfile(){
  //Display message on LCD and Computer Screen
//  initializeLCD();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Select a profile.");
  lcd.setCursor(0,1);
  lcd.write("1: 1.75 ABS");
  lcd.setCursor(0,2);
  lcd.write("2: No Auger");
  lcd.setCursor(0,3);
  lcd.write("3: No Heat");


  Serial.println("Select a profile.");
  Serial.println("1: 1.75ABS");
  Serial.println("2: No Auger");
  Serial.println("3: No Heat\n");
  boolean invalid = true;

  while(invalid){
    key = kpd.getKey();

  //Allow for keyboard input as well
  if (Serial.available() > 0) {
    key = (char)Serial.read();
  }

    if (key == '1' || key == '2' || key == '3'){
      invalid = false;
    }
  }
  switch(key){
    case '1':
    {

        //select 1.75 profile
        diaSetPoint = 1.75;
        barrelSetPoint = 220;
        nozzleSetPoint = 210;
        augerRPM = 40;
//        outfeedRPM = 70;
        soakTime = 7;
        setFeedRate(7.5);
        outfeedRPM = calcOutfeedRPM();
        outfeed.setRPM(0);
        //Shift state to preheat.
        currentState = PREHEAT;

    }
      break;

    case '2':
    {
    diaSetPoint = 1.75;
    barrelSetPoint = 0;
    nozzleSetPoint = 0;
    augerRPM = 0 ;
    outfeedRPM = 70;
    soakTime = 5;

        setFeedRate(7.5);
//        outfeedRPM = calcOutfeedRPM();
        outfeed.setRPM(50);

    currentState = EXTRUDE_AUTOMATIC;

    }
      break;

    case '3':
        //select 1.75 profile No Heat
        diaSetPoint = 1.75;
        barrelSetPoint = 0;
        nozzleSetPoint = 0;
        augerRPM = 38;
        outfeedRPM = 70;
        soakTime = 0;

        setFeedRate(7.5);
        outfeedRPM = calcOutfeedRPM();
        outfeed.setRPM(0);



        //Shift state to preheat.
        currentState = EXTRUDE_AUTOMATIC;
    break;

    }
  }

void customProfile(){

}


void extrudeManual(){

}


void extrudeComplete(){

}





double getNumber(char *title, char *subTitle){
//      bool noDecimal = true;
//      lcd.clear();
//      lcd.write(title);
//      lcd.setCursor(0,1);
//      lcd.write(subTitle);
//      lcd.setCursor(0,3);
//      lcd.write("(Esc press <-)");
//      lcd.setCursor(0,2);
//
//      boolean invalid = true;
//      diameterPtr = diameterString;// set pointer to first digit
//
//      while (invalid){
//        key=kpd.waitForKey();//get user input
//
//        switch(key){
//
//          case 'D':
//          //Check to see that a valid diameter was entered
//
//          //return number
//          return atof(diameterString);
//
//          case 'A': //backspace was pressed so go back.
//           if (diameterPtr > diameterString){
//             lcd.setCursor(diameterPtr - diameterString - 1,2);
//             lcd.write(' ');
//             lcd.setCursor(diameterPtr - diameterString - 1,2);
//             diameterPtr--;
//             if (*diameterPtr == '.'){
//              noDecimal = true;
//             }
//
//           } else {//back space was pressed to exit Custom
//            //keep state as selectProfile
//            return -1;
//           }
//
//          case 'B'://invalid do nothing
//           break;
//
//          case 'C'://invalid do nothing
//           break;
//
//          case '#'://invalid do nothing
//           break;
//
//          case '*'://decimal place
//          if (diameterPtr - diameterString < 5 && noDecimal == true){ //Make sure that the diameterString isn't full
//             *diameterPtr = '.';
//             lcd.write('.');
//             diameterPtr++;
//             noDecimal = false;
//          }
//          break;
//
//          default:
//          if (diameterPtr - diameterString < 5){ //Make sure that the diameterString isn't full
//            *diameterPtr = key;
//            diameterPtr++;
//            lcd.write(key);
//          }
//        }
//      }
  return 0.0;
}
#endif // FSM_h


