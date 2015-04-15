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
      //      switch (_displayed[i]->getType()) {
      //        case MenuItem::BOOLEAN:
      //        case MenuItem::INT:
      //        case MenuItem::UNSIGNED_LONG:
      //        case MenuItem::FLOAT:
      //        case MenuItem::DOUBLE:
      //          _displayed[i]->getValStr(&_text[20 - _displayed[i]->getLength()]);
      //          j = 21;
      //          break;

      //        case MenuItem::VALUE:
      //        case MenuItem::BOOLEAN:
      //          //convert it to a string and insert it into the _text string
      //          _ntos(*(boolean*)_displayed[i]->_value1, &_text[19], _displayed[i]->getType(), _displayed[i]->getPrecision());
      ////          _text[19] = *(boolean*)_displayed[i]->_value1 ? '1' : '0';
      //          j = 21;
      //          break;
      //
      //
      //        case MenuItem::INT:
      //          //find the length of the value
      //          valLength = _displayed[i]->getLength();
      //
      //          //convert it to a string and insert it into the _text string
      //          _ntos(*(int*)_displayed[i]->_value1, &_text[20 - valLength], _displayed[i]->getType(), _displayed[i]->getPrecision());
      ////          _ftoa(&_text[20 - valLength], *(int*)_displayed[i]->_value1, _displayed[i]->getPrecision());
      //          j = 21;
      //          break;
      //
      //
      //        case MenuItem::UNSIGNED_LONG:
      //          //find the length of the value
      //          valLength = _displayed[i]->getLength();
      //
      //          //convert it to a string and insert it into the _text string
      //          _ultostr(*(unsigned long*)_displayed[i]->_value1, &_text[20 - valLength], 10);
      //          j = 21;
      //          break;
      //
      //
      //        case MenuItem::FLOAT:
      //        case MenuItem::DOUBLE:
      //          _text[21] = '\0';//comment out?
      //
      //          //find the length of the value
      //          valLength = _displayed[i]->getLength();
      //
      //          //convert it to a string and insert it into the _text string
      //          _ftoa(&_text[20 - valLength], *(float*)_displayed[i]->_value1, _displayed[i]->getPrecision());
      //          j = 21;
      //            valLength = _displayed[i]->getLength();
      //          _displayed[i]->getValStr(&_text[20-_displayed[i]->getLength()]);
      //          j=21;
      //          break;
      //      }

      _text[j] = '\0'; //Terminate the string with the null character;

      //Display the text
      Serial.println(_text);
      _lcd->setCursor(0, i);
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

char* Menu:: _ftoa(char *a, double f, int precision)
{
  long p[] = {0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
  char *ret = a;
  long integer = (long)f;
  itoa(integer, a, 10);
  while (*a != '\0') a++;//advance pointer to end of integer section.

  if (precision != 0) {
    *a++ = '.';
    int decimal = floor(abs((f - (float)integer) * p[precision]) + 0.5); //float math isn't exact so need to round from next decimal out
    int i = precision - 1;
    while (p[i] >= decimal) {
      *a++ = '0';
      i--;
    }
    if (decimal != 0) {
      itoa(decimal, a, 10);
    }
  }
  return ret;
}

int Menu:: _valueLength(double value, int presision)
{
  int length;
  boolean negative = false;
  unsigned long p[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000
  };
  int i = 1;//Start at 1 because there is always a leading zero.
  if (value < 0) negative = true; // add one space for the negative sign
  value = abs(value);//remove negative if there.
  //divide by progressively larger values until the remainder is zero
  //This gives the number of digits before the decimal

  while (i < 9) {
    if ((unsigned long)value / p[i] == 0) {
      break;
    }
    i++;
  }
  if (negative) i++; // add one space for the negative sign

  if (presision > 0) i = i + presision + 1; //if there is a decimal place include the it and the extra digits
  return i;
}


char* Menu::_ultostr(unsigned long value, char *ptr, int base)
{
  unsigned long t = 0, res = 0;
  unsigned long tmp = value;
  int count = 0;

  if (NULL == ptr) return NULL;
  if (tmp == 0) count++;

  while (tmp > 0) {
    tmp = tmp / base;
    count++;
  }

  ptr += count;

  *ptr = '\0';

  do {
    res = value - base * (t = value / base);
    if (res < 10) {
      * -- ptr = '0' + res;
    } else if ((res >= 10) && (res < 16)) {
      * --ptr = 'A' - 10 + res;
    }
  } while ((value = t) != 0);

  return (ptr);
}

char* Menu::_ntos(double value, char *ptr, MenuItem::ItemType type, int precision) {
  switch (type) {
    case MenuItem::BOOLEAN: //boolean
      *ptr = value > 0 ? '1' : '0';
      return ptr;
      break;

    case MenuItem::INT: //int

      itoa ( value, ptr, 10 );
      return ptr;
      break;

    case MenuItem::UNSIGNED_LONG: //unsigned long
      {
        unsigned long t = 0, res = 0;
        unsigned long tmp = (unsigned long)value;
        unsigned long val = (unsigned long)value;

        int count = 0;

        if (NULL == ptr) return NULL;
        if (tmp == 0) count++;

        while (tmp > 0) {
          tmp = tmp / 10;
          count++;
        }

        ptr += count;

        *ptr = '\0';

        do {
          res = val - 10 * (t = val / 10);
          if (res < 10) {
            * -- ptr = '0' + res;
          } else if ((res >= 10) && (res < 16)) {
            * --ptr = 'A' - 10 + res;
          }
        } while ((val = t) != 0);
        return ptr;
        break;
      }

    case MenuItem::FLOAT:
    case MenuItem::DOUBLE:
      long p[] = {0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
      char *ret = ptr;
      long integer = (long)value;
      itoa(integer, ptr, 10);
      while (*ptr != '\0') ptr++;//advance pointer to end of integer section.

      if (precision != 0) {
        *ptr++ = '.';
        int decimal = floor(abs((value - (float)integer) * p[precision]) + 0.5); //float math isn't exact so need to round from next decimal out
        int i = precision - 1;
        while (p[i] >= decimal) {
          *ptr++ = '0';
          i--;
        }
        if (decimal != 0) {
          itoa(decimal, ptr, 10);
        }
      }
      return ptr;
      break;

  }
}



