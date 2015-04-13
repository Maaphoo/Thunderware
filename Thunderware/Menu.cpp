/*
  Menu.cpp - Library for controlling LCD menus
 
 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */

#include "Arduino.h"
#include "Menu.h"

Menu::Menu(MenuItem* root, LiquidCrystal* lcd, Keypad* kpd)
{
  _root = root;
  _lcd = lcd;
  _kpd = kpd;
  _firstItem = _root->getChild();
  _firstLine = _root;
  _currentTitle = _root;

  _displayed[0] = _root;
  _displayed[1] = _firstItem;
  _currentItem = _firstItem;
  _selectedItem = _firstItem;
}

void Menu::up()
{

  //Move up the menu if possible
  if (_selectedItem == _firstLine){
    //The selectedItem is on the first line
    if (_selectedItem->getPrevious() != _firstItem){
      //The selecedItem is the third item or lower. 
      //move the first line up one
      _firstLine = _selectedItem->getPrevious();
      _selectedItem = _selectedItem->getPrevious();
    } 
    else {
      // The selectedItem is the secondItem
      //Move up to the title line
      _firstLine = _currentTitle;
      _selectedItem = _firstItem;
    }
  } 
  else {
    //Selected item is not on the first line
    if (_selectedItem!=_firstItem){
      //the selectedItem is not the first item so move selected up
      _selectedItem = _selectedItem->getPrevious();
    }
  }
  _setDisplay();
  display();
}

void Menu::down()
{
  //move menu down if possible
  if (_displayed[3] == _selectedItem && _displayed[3]->getNext()){
    //the last line is selected and it has a next
    //move the firstLine down one
    if (_firstLine == _currentTitle){
      _firstLine = _firstItem;
    } 
    else {
      _firstLine = _firstLine->getNext();
    }
    _selectedItem = _selectedItem->getNext();

  } 
  else {
    //The line Item wasn't selected
    //Move the selected item down if possible
    if (_selectedItem->getNext()){
      _selectedItem = _selectedItem->getNext();
    }
  }
  _setDisplay();
  display();
}

void Menu::back()
{
  if (_currentTitle->getParent() != NULL){
    _currentTitle = _currentTitle->getParent();

    _firstLine = _currentTitle;
    _firstItem = _firstLine->getChild();
    _selectedItem = _firstItem;
  } 
  _setDisplay();
  display();
}

void Menu::select()
{
  switch (_selectedItem->itemType){
    case MenuItem::TITLE:
    if (_selectedItem->getChild()){
      //Set old selected item as title and first line
      _currentTitle= _selectedItem;
      _firstLine = _currentTitle;

      //set old selected item's child as firstItem and selectedItem
      _selectedItem = _selectedItem->getChild();
      _firstItem = _selectedItem;

      _setDisplay();
      display();
    }
    break;

    case MenuItem::ACTION:
      _selectedItem->doAction();
      break;

    case MenuItem::VALUE:
    _editValue();
    break;
  }
}



void Menu::display()
{
  _lcd->clear();
  for (int i=0;i<4;i++){
    int j = 0;
    
    //if the ith item isn't null and if it has text
    if (_displayed[i] != NULL && _displayed[i]->getText() && _displayed[i]->getText()[0] != '\0'){ 
      //If the current line of text text isn't the title,
      // decide whether or not it is selected
      if (_currentTitle != _displayed[i]){
        j=1;//advance
        if (_selectedItem == _displayed[i]){
          _text[0] = '>';
        } 
        else{
          _text[0] = ' ';
        }
      }

      // itterate through the item text and add it to the text to be displayed
      char *c = _displayed[i]->getText();
      while(*c){
        _text[j]=*c;
        *c++;
        j++;
      }

      //if the item is a value, display it's value
      if (_displayed[i]->itemType == MenuItem::VALUE){
        while (j<21){
          _text[j] = ' ';
          j++; 
        }
        _text[21] = '\0';

        //find the length of the value
        int length = _valueLength(_displayed[i]->getValue(), _displayed[i]->getPrecission());

        //convert it to a string and insert it into the _text string
        _ftoa(&_text[20-length],_displayed[i]->getValue(), _displayed[i]->getPrecission());//_displayed[i]->getPrecision()));
        j = 21;
      }
      _text[j]=0; //Terminate the string with the null character;

      //Display the text
      Serial.println(_text);
      _lcd->setCursor(0,i);
      _lcd->write(_text);
    }
  }
  Serial.println("");
}


void Menu::reset()
{

  _firstItem = _root->getChild();
  _firstLine = _root;
  _selectedItem = _root->getChild();
  _displayed[0] = _firstLine;
  _displayed[1] = _root->getChild();
  if (_displayed[1]->getNext() != NULL){
    _displayed [2] = _displayed[1]->getNext();
    if (_displayed[2]->getNext() != NULL){
      _displayed [3] = _displayed[2]->getNext();

    }
  }
  display();
}

void Menu::_setDisplay()
{


  _displayed[0] = _firstLine;
  if (_firstLine ==_currentTitle){
    //The first line is a title, so the second line is its child
    _displayed[1] = _displayed[0]->getChild();
  }
  else{
    //The first line is not a title, so the second line is its next
    _displayed[1] = _displayed[0]->getNext();
  }
  _displayed[2] = _displayed[1]->getNext();
  if (_displayed[2] != NULL && _displayed[2]->getNext() != NULL){
    _displayed[3] = _displayed[2]->getNext();
  }
  else{
    _displayed[3] = NULL;
  }
}

//void Menu::_editValue()
//{
//  Serial.println(_selectedItem->getText());
//  Serial.print("Current Value: ");
//  Serial.println(_selectedItem->getValue());
//  Serial.print("New Value: ");
//
//  char inData[21]; // Allocate some space for the string
//  char inChar; // Where to store the character read
//  byte index = 0; // Index into array; where to store the character
//  boolean flag = true;
//  while (flag){
//    while(Serial.available() > 0) // Don't read unless
//      // there you know there is data
//    {
//      if(index < 20) // One less than the size of the array
//      {
//        inChar = Serial.read(); // Read a character
//        if (inChar =='D'){
//          Serial.println(inData);
//          _selectedItem->setValue(inData);
//          flag = false;
//          break;
//        }
//        inData[index] = inChar; // Store it
//        index++; // Increment where to write next
//        inData[index] = '\0'; // Null terminate the string
//      }
//
//    }
//  }
//  Serial.println("");
//  delay(2000);
//  display();
//}

void Menu::_editValue(){
  char diameterString[21];
  char *diameterPtr;//pointer to char in diameterString.
  bool noDecimal = true;
  _lcd->clear();
  _lcd->setCursor(0,0);
  _lcd->write(_selectedItem->getText());
  _lcd->setCursor(0,1);
  _lcd->write("Current Val: ");
  _lcd->print(_selectedItem->getValue(),2);  
  _lcd->setCursor(0,3);
  _lcd->write("(Esc press D)");
  _lcd->setCursor(0,2);
  Serial.println("");
  Serial.println(_selectedItem->getText());
  Serial.print("Current Val: ");
  Serial.println(_selectedItem->getValue(),_selectedItem->getPrecission());
  Serial.println("Enter an new value followed by 'D'");
  Serial.println("(Esc press D)");

  boolean invalid = true;
  diameterPtr = diameterString;// set pointer to first digit
  boolean valueBeingEntered = true;
  while (valueBeingEntered){
    while (invalid){
      _key=_kpd->getKey();//get user input

      //Allow for keyboard input as well
      if (Serial.available() > 0) {
        _key = (char)Serial.read();
      }
      if (_key) {
        break;
      }
    }
    switch(_key){

    // case 13 - carriage return from serial 
    //need to select carriage return option 
    //in serial monitor for this to work.
    case 'D':
      //Check to see that a valid diameter was entered

      //return number
      if (diameterPtr != diameterString){
        _selectedItem->setValue(atof(diameterString));
      }
      valueBeingEntered = false;
//      Serial.print(_selectedItem->getText());
//      Serial.print(" = ");
//      Serial.println(_selectedItem->getValue(),_selectedItem->getPrecission());
      Serial.println("");

      break;

    case 'A': //backspace was pressed so go back.
      if (diameterPtr > diameterString){
        _lcd->setCursor(diameterPtr - diameterString - 1,2);
        _lcd->write(' ');
        _lcd->setCursor(diameterPtr - diameterString - 1,2);
        diameterPtr--;
        if (*diameterPtr == '.'){
          noDecimal = true;
        }

      } 
      else {//back space was pressed to exit Custom
        //keep state as selectProfile
        valueBeingEntered = false;
      }

    case 'B'://invalid do nothing
      break;

    case 'C'://invalid do nothing
      break;

    case '#'://invalid do nothing
      break;

    case '*'://decimal place
    case '.'://decimal place
      if (diameterPtr - diameterString < 20 && noDecimal == true){ //Make sure that the diameterString isn't full
        *diameterPtr = '.';
        _lcd->write('.');
        diameterPtr++;
        noDecimal = false;
      }
      break;

    default:
      if (diameterPtr - diameterString < 20){ //Make sure that the diameterString isn't full
        *diameterPtr = _key;
        diameterPtr++;
        _lcd->write(_key);
      }
    }
  }
  display();
}

char* Menu:: _ftoa(char *a, double f, int precision)
{
  long p[] = {
    0,10,100,1000,10000,100000,1000000,10000000,100000000    };

  char *ret = a;
  long heiltal = (long)f;
  itoa(heiltal, a, 10);
  while (*a != '\0') a++;
  *a++ = '.';
  long desimal = abs((long)((f - heiltal) * p[precision]));
  itoa(desimal, a, 10);
  return ret;
}

int Menu:: _valueLength(double value, int presision)
{
  int i = 1;
  int length;
  long p[] = {
    0,10,100,1000,10000,100000,1000000,10000000,100000000    };

  //divide by progressively larger values until the remainder is zero
  //This gives the number of digits before the decimal
  while (i>9){
    if((int)value/p[i] == 0){
      break;
    }
    i++;
  }
  if (presision>0){ //if there is a decimal place include the it and the extra digits
    length = i+presision+1;
  } 
  else {
    length = i;
  }
  return length;
}





