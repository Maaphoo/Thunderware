///*
//  FSM.cpp - Library for activating the the FSM heater.
//          The FSM heater is a 120 v 130 w heating element powered
//          by an electro-mechanical relay. The relay coil is optically 
//          isolated from the logic circuits and is activated by pin 7.
//      
//  Created by Matthew P. Rogge, Februrary 12, 2014.
//  Released into the public domain.
//*/
//
//#include "Arduino.h"
//#include "FSM.h"
//
//                          
//FSM::FSM(Configuration* configuration) 
//{
//  _configuration = configuration;
//  _currentState = SELECT_PROFILE_SETUP;
//  FSM::state_table[0] = (&FSM::selectProfileSetup);
////  void (*state_table[])()={
////    selectProfileSetup,
////    selectProfile,
////    customProfile,
////    preheat,
////    soak,
////    extrudeManual,
////    extrudeAutomatic,
////    extrudeComplete,
////    safetyShutdown,
////    test
////  };
//}
//
//
//
//void FSM::selectProfileSetup()
//{
//    // ====== Test Menu =========== 
//
//byte foo = 0;
//byte sel = 0;
//unsigned int bar = 1;
//long baz  = 0;
//float bak = 0.0;
//
//  // Create a list of states and values for a select input
//MENU_SELECT_ITEM  sel_ign = { 2, {"Ignore"} };
//MENU_SELECT_ITEM  sel_on  = { 1, {"On"} };
//MENU_SELECT_ITEM  sel_off = { 0, {"Off"} };
//
//MENU_SELECT_LIST  state_list[] = { &sel_ign, &sel_on, &sel_off };
//                                  
//  // the special target for our state input
//  
//                             // TARGET VAR   LENGTH                          TARGET SELECT LIST
//MENU_SELECT state_select = { &sel,           MENU_SELECT_SIZE(state_list),   MENU_TARGET(&state_list) };
//
//  // values to use 
//
//                    //    TYPE            MAX    MIN    TARGET 
//MENU_VALUE foo_value = { TYPE_BYTE,       100,   0,     MENU_TARGET(&foo) };
//MENU_VALUE bar_value = { TYPE_UINT,       10000, 100,   MENU_TARGET(&bar) };
//MENU_VALUE baz_value = { TYPE_LONG,       10000, 1,     MENU_TARGET(&baz) };
//MENU_VALUE bak_value = { TYPE_FLOAT_1000, 0,     0,     MENU_TARGET(&bak) };
//MENU_VALUE sel_value = { TYPE_SELECT,     0,     0,     MENU_TARGET(&state_select) };
//
//                    //        LABEL           TYPE        LENGTH    TARGET
//MENU_ITEM item_checkme  = { {"Byte Edit"},    ITEM_VALUE,  0,        MENU_TARGET(&foo_value) };
//MENU_ITEM item_barme    = { {"UInt Edit"},    ITEM_VALUE,  0,        MENU_TARGET(&bar_value) };
//MENU_ITEM item_bazme    = { {"Long Edit"},    ITEM_VALUE,  0,        MENU_TARGET(&baz_value) };
//MENU_ITEM item_bakme    = { {"Float Edit"},   ITEM_VALUE,  0,        MENU_TARGET(&bak_value) };
//MENU_ITEM item_state    = { {"Select Input"}, ITEM_VALUE,  0,        MENU_TARGET(&sel_value) };
//MENU_ITEM item_testme   = { {"Test Action"},  ITEM_ACTION, 0,        MENU_TARGET(testAction) };
//
//                   //        List of items in menu level
//MENU_LIST root_list[]   = { &item_checkme, &item_barme, &item_bazme, &item_bakme, &item_state, &item_testme };
//
//                  // Root item is always created last, so we can add all other items to it
//MENU_ITEM menu_root     = { {"Root"},        ITEM_MENU,   MENU_SIZE(root_list),    MENU_TARGET(&root_list) };
//
//OMMenuMgr Menu(&menu_root, MENU_KEYPAD);
//  uiClear();
//  
//  Menu.setDrawHandler(uiDraw);
//  Menu.setExitHandler(uiClear);
//  Menu.setKeypadInput(&kpd, &menuKeys, myButtons);
//  Menu.enable(true); 
//}
//
//
//
//
//
//
//
//
//#ifndef FSM_h
//#define FSM_h
//
//#include "config.h"
//#include "StarveFeeder.h"
//
//char diameterString[6];
//char *diameterPtr;//pointer to char in diameterString.
//
//void selectProfileSetup(){
//
//}
//
//void selectProfile(){
// Menu.checkInput();
//
//  
//
////  //Display message on LCD and Computer Screen
//////  initializeLCD();
////  lcd.clear();
////  lcd.setCursor(0,0);
////  lcd.write("Select a profile.");
////  lcd.setCursor(0,1);
////  lcd.write("1: 1.75 ABS");
////  lcd.setCursor(0,2);
////  lcd.write("2: No Auger");
////  lcd.setCursor(0,3);
////  lcd.write("3: No Heat");
////
////
////  Serial.println("Select a profile.");
////  Serial.println("1: 1.75ABS");
////  Serial.println("2: No Auger");
////  Serial.println("3: No Heat\n");
////  boolean invalid = true;
////
////  while(invalid){
////    key = kpd.getKey();
////
////  //Allow for keyboard input as well
////  if (Serial.available() > 0) {
////    key = (char)Serial.read();
////  }
////
////    if (key == '1' || key == '2' || key == '3' || key == 'D'){
////      invalid = false;
////    }
////  }
////  switch(key){
////    case '1':
////    {
////
////        //select 1.75 profile
////        diaSetPoint = 1.75;
////        barrelSetPoint = 220;
////        nozzleSetPoint = 210;
////        augerRPM = 40;
//////        outfeedRPM = 70;
////        soakTime = 7;
//////        setFeedRate(7.5);
//////        outfeedRPM = calcOutfeedRPM();
////        outfeed.setRPM(0);
////        //Shift state to preheat.
////        currentState = PREHEAT;
////
////    }
////      break;
////
////    case '2':
////    {
////    diaSetPoint = 1.75;
////    barrelSetPoint = 0;
////    nozzleSetPoint = 0;
////    augerRPM = 0 ;
////    outfeedRPM = 70;
////    soakTime = 5;
////
//////        setFeedRate(7.5);
//////        outfeedRPM = calcOutfeedRPM();
////        outfeed.setRPM(50);
////
////    currentState = EXTRUDE_AUTOMATIC;
////
////    }
////      break;
////
////    case '3':
////        //select 1.75 profile No Heat
////        diaSetPoint = 1.75;
////        barrelSetPoint = 0;
////        nozzleSetPoint = 0;
////        augerRPM = 38;
////        outfeedRPM = 70;
////        soakTime = 0;
////
//////        setFeedRate(7.5);
//////        outfeedRPM = calcOutfeedRPM();
////        outfeed.setRPM(0);
////
////
////
////        //Shift state to preheat.
////        currentState = EXTRUDE_AUTOMATIC;
////    break;
////    case 'D':
////        currentState = TEST;
////        break;
////    }
//  }
//
//void customProfile(){
//
//}
//
//
//void extrudeManual(){
//
//}
//
//
//void extrudeComplete(){
//
//}
//
//
//
//
//
//double getNumber(char *title, char *subTitle){
////      bool noDecimal = true;
////      lcd.clear();
////      lcd.write(title);
////      lcd.setCursor(0,1);
////      lcd.write(subTitle);
////      lcd.setCursor(0,3);
////      lcd.write("(Esc press <-)");
////      lcd.setCursor(0,2);
////
////      boolean invalid = true;
////      diameterPtr = diameterString;// set pointer to first digit
////
////      while (invalid){
////        key=kpd.waitForKey();//get user input
////
////        switch(key){
////
////          case 'D':
////          //Check to see that a valid diameter was entered
////
////          //return number
////          return atof(diameterString);
////
////          case 'A': //backspace was pressed so go back.
////           if (diameterPtr > diameterString){
////             lcd.setCursor(diameterPtr - diameterString - 1,2);
////             lcd.write(' ');
////             lcd.setCursor(diameterPtr - diameterString - 1,2);
////             diameterPtr--;
////             if (*diameterPtr == '.'){
////              noDecimal = true;
////             }
////
////           } else {//back space was pressed to exit Custom
////            //keep state as selectProfile
////            return -1;
////           }
////
////          case 'B'://invalid do nothing
////           break;
////
////          case 'C'://invalid do nothing
////           break;
////
////          case '#'://invalid do nothing
////           break;
////
////          case '*'://decimal place
////          if (diameterPtr - diameterString < 5 && noDecimal == true){ //Make sure that the diameterString isn't full
////             *diameterPtr = '.';
////             lcd.write('.');
////             diameterPtr++;
////             noDecimal = false;
////          }
////          break;
////
////          default:
////          if (diameterPtr - diameterString < 5){ //Make sure that the diameterString isn't full
////            *diameterPtr = key;
////            diameterPtr++;
////            lcd.write(key);
////          }
////        }
////      }
//  return 0.0;
//}
//
//
//#endif // FSM_h
//

