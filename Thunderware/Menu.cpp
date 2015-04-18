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
  if (_selectedItem == _firstLine) {
    //The selectedItem is on the first line
    if (_selectedItem->getPrevious() != _firstItem) {
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
    if (_selectedItem != _firstItem) {
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
  if (_displayed[3] == _selectedItem && _displayed[3]->getNext()) {
    //the last line is selected and it has a next
    //move the firstLine down one
    if (_firstLine == _currentTitle) {
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
    if (_selectedItem->getNext()) {
      _selectedItem = _selectedItem->getNext();
    }
  }
  _setDisplay();
  display();
}

void Menu::printSelected()
{
  //for testing
  //  char value[20];
  //  _selectedItem->getValStr(value);
  //  Serial.println(_selectedItem->getPrecision());
  //  Serial.println(*(float*)_selectedItem->_value1,_selectedItem->getPrecision() );

}
void Menu::back()
{
  if (_currentTitle->getParent() != NULL) {
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
  switch (_selectedItem->getType()) {
    case MenuItem::TITLE:
      if (_selectedItem->getDoActionOnSelect()) {
        _selectedItem->doAction();
      }
      if (_selectedItem->getChild()) {
        //Set old selected item as title and first line
        _currentTitle = _selectedItem;
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
    case MenuItem::BOOLEAN:
    case MenuItem::INT:
    case MenuItem::UNSIGNED_LONG:
    case MenuItem::FLOAT:
    case MenuItem::DOUBLE:
      _editValue();
      break;

    case MenuItem::STRING:
      _editString();
      break;
  }
}


void Menu::display()
{
  _lcd->clear();
  for (int i = 0; i < 4; i++) {
    int j = 0;

    //if the ith item isn't null and if it has text
    if (_displayed[i] != NULL && _displayed[i]->getText() && _displayed[i]->getText()[0] != '\0') {
      //If the current line of text text isn't the title,
      // decide whether or not it is selected
      if (_currentTitle != _displayed[i]) {
        j = 1; //advance
        if (_selectedItem == _displayed[i]) {
          _text[0] = '>';
          _selectLineNumber = i;
        }
        else {
          _text[0] = ' ';
        }
      }

      // itterate through the item text and add it to the text to be displayed
      char *c = _displayed[i]->getText();
      while (*c) {
        _text[j] = *c;
        *c++;
        j++;
      }

      //Blank out any old characters
      while (j < 20) {
        _text[j] = ' ';
        j++;
      }

      int valLength;
      if ((int)_displayed[i]->_value1) {
        _displayed[i]->getValStr(&_text[20 - _displayed[i]->getLength()]);
        j = 21;
      }
      
      _text[j] = '\0'; //Terminate the string with the null character;

      //Display the text
      Serial.println(_text);
      _lcd->setCursor(0, i);
      _lcd->print(_text);
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
  if (_displayed[1]->getNext() != NULL) {
    _displayed [2] = _displayed[1]->getNext();
    if (_displayed[2]->getNext() != NULL) {
      _displayed [3] = _displayed[2]->getNext();

    }
  }
  display();
}

void Menu::_setDisplay()
{


  _displayed[0] = _firstLine;
  if (_firstLine == _currentTitle) {
    //The first line is a title, so the second line is its child
    _displayed[1] = _displayed[0]->getChild();
  }
  else {
    //The first line is not a title, so the second line is its next
    _displayed[1] = _displayed[0]->getNext();
  }
  _displayed[2] = _displayed[1]->getNext();
  if (_displayed[2] != NULL && _displayed[2]->getNext() != NULL) {
    _displayed[3] = _displayed[2]->getNext();
  }
  else {
    _displayed[3] = NULL;
  }
}



void Menu::_editValue() {
  char valueString[21];
  char *valuePtr;//pointer to char in valueString.
  //find the length of the value

  //this is type dependent
  int valLength = _selectedItem->getLength();
  _lcd->setCursor(20 - valLength, _selectLineNumber);
  for (int i = 0; i < valLength; i++) {
    _lcd->write(' ');
  }

  int textLength = 0;
  // itterate through the item text and add it to the text to be displayed
  char *c = _selectedItem->getText();
  while (*c) {
    *c++;
    textLength++;
  }

  _lcd->setCursor(textLength + 3, _selectLineNumber);
  _lcd->blink();

  boolean noDecimal = true;
  boolean invalid = true;
  int precision = 0;
  valuePtr = valueString;// set pointer to first digit
  boolean valueBeingEntered = true;
  while (valueBeingEntered) {
    while (invalid) {
      _key = _kpd->getKey(); //get user input

      //Allow for keyboard input as well
      if (Serial.available() > 0) {
        _key = (char)Serial.read();
      }
      if (_key) {
        break;
      }
    }
    switch (_key) {

      // case 13 - carriage return from serial
      //need to select carriage return option
      //in serial monitor for this to work.
      case 'CR' :
      case 'D':
        //Check to see that a valid diameter was entered

        //terminate string
        *valuePtr == '\0';

        //return number
        if (valuePtr != valueString) {
          float f = atof(valueString);//make the value into a float no matter what it is
          _selectedItem->setValue(&f, precision);//setValue corrects the type of the value
        }
        valueBeingEntered = false;
        _lcd->noBlink();

        break;

      case 'A': //backspace was pressed so go back.
        if (valuePtr > valueString) {
          valuePtr--;
          _lcd->setCursor(textLength + 3 + (valuePtr - valueString), _selectLineNumber);
          _lcd->write(' ');
          _lcd->setCursor(textLength + 3 + (valuePtr - valueString), _selectLineNumber);
          if (precision > 0 && *valuePtr != '.') precision--;
          if (*valuePtr == '.') {
            noDecimal = true;
          }
          *valuePtr = '\0';

        }
        else {//back space was pressed to exit Custom
          //keep state as selectProfile
          valueBeingEntered = false;
        }
        break;

      case '-':
      case 'B'://negitive
        if (valuePtr == valueString) { //Make sure that it is the first key
          *valuePtr = '-';
          valuePtr++;
          _lcd->write('-');
        }

        break;

      case 'C'://invalid do nothing
        break;

      case '#'://invalid do nothing
        break;

      case '*'://decimal place
      case '.'://decimal place
        if (valuePtr - valueString < 19 && noDecimal == true) { //Make sure that the valueString isn't full
          *valuePtr = '.';
          _lcd->write('.');
          valuePtr++;
          noDecimal = false;
        }
        break;

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        if (valuePtr - valueString < 20) { //Make sure that the valueString isn't full
          *valuePtr = _key;
          valuePtr++;
          if (!noDecimal) {
            precision++;
          }
          _lcd->write(_key);
        }
    }
  }
  display();
}

void Menu::_editString() {
  char valueString[14];
  char *valuePtr = valueString;//pointer to char in valueString.

  //Clear out any characters that might be in the way
  _lcd->setCursor(6, _selectLineNumber);
  for (int i = 6; i < 20; i++) {
    _lcd->write(' ');
  }
  char character = 64;
  _lcd->setCursor(6, _selectLineNumber);
  _lcd->write(character);
  _lcd->setCursor(6, _selectLineNumber);
  _lcd->blink();

  boolean invalid = true;
  valuePtr = valueString;// set pointer to first character
  boolean valueBeingEntered = true;
  int charPos = 6;
  while (valueBeingEntered) {
    while (invalid) {
      _key = _kpd->getKey(); //get user input

      //Allow for keyboard input as well
      if (Serial.available() > 0) {
        _key = (char)Serial.read();
      }
      if (_key) {
        break;
      }
    }
    switch (_key) {

      case '1'://up

        if (character < 126) {
          character++;
        } else {
          character = 32;
        }

        _lcd->print(character);
        _lcd->setCursor(charPos, _selectLineNumber);
        break;

      case '2'://down
        if (character > 32) {
          character--;
        } else {
          character = 126;
        }

        _lcd->print(character);
        _lcd->setCursor(charPos, _selectLineNumber);
        break;

      case '3'://select
        if (charPos < 20 && character != 64) {
          *valuePtr = character;
          valuePtr++;
          charPos++;
          _lcd->write(character);
          _lcd->setCursor(charPos, _selectLineNumber);
          _lcd->write(character);
          _lcd->setCursor(charPos, _selectLineNumber);
        } else if (character == 64) {
            *valuePtr = 0;//terminate the string
          Serial.print("valueString: ");
          Serial.println(valueString);
          _selectedItem->setValue(&valueString,0);
          valueBeingEntered = false;
          _lcd->noBlink();
        }
        break;


      case '4'://back
        if (valuePtr > valueString) {
          valuePtr--;
          _lcd->write(' ');
          charPos--;
          _lcd->setCursor(charPos, _selectLineNumber);
          character = *valuePtr;
          _lcd->write(character);
          _lcd->setCursor(charPos, _selectLineNumber);
        }
        else {//back space was pressed to exit Custom
          //keep state as selectProfile
          valueBeingEntered = false;
        }
        break;
    }
  }
  display();
}



