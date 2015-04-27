/*
  Menu.cpp - Library for controlling LCD menus

 Created by Matthew P. Rogge, Februrary 12, 2014.
 Released into the public domain.
 */

#include "Arduino.h"
//#include "MenuData.h"
#include "Menu.h"


Menu::Menu(const MenuItem* menu, int menuSize, LiquidCrystal* lcd, Keypad* kpd)
{
  _menuSize = menuSize;
  _menu = menu;
  //  _root = root;
  _lcd = lcd;
  _kpd = kpd;


  _displayed[0] = 0;
  _firstItem = 1;
  _displayed[1] = 1;
  _currentItem = 1;
  _selectedItem = 1;
}

void Menu::up()
{

  //Move up the menu if possible
  if (_selectedItem == _firstLine) {
    //The selectedItem is on the first line
    if (getPrevious(_selectedItem) != _firstItem) {
      //The selecedItem is the third item or lower.
      //move the first line up one
      _firstLine = getPrevious(_selectedItem);
      _selectedItem = getPrevious(_selectedItem);
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
      _selectedItem = getPrevious(_selectedItem);
    }
  }
  _setDisplay();
  display();
}

void Menu::down()
{
  //move menu down if possible
  if (_displayed[3] == _selectedItem && getNext(_displayed[3]) != -1) {
    //the last line is selected and it has a next
    //move the firstLine down one
    if (_firstLine == _currentTitle) {
      _firstLine = _firstItem;
    }
    else {
      _firstLine = getNext(_firstLine);
    }
    _selectedItem = getNext(_selectedItem);

  }
  else {
    //The line Item wasn't selected
    //Move the selected item down if possible
    if (getNext(_selectedItem) != -1) {
      _selectedItem = getNext(_selectedItem);
    }
  }
  _setDisplay();
  display();
}

void Menu::back()
{
  if (getParent(_currentTitle) != -1) {
    _currentTitle = getParent(_currentTitle);

    _firstLine = _currentTitle;
    _firstItem = getChild(_firstLine);
    _selectedItem = _firstItem;
  }
  _setDisplay();
  display();
}

void Menu::select()
{
  if (pgm_read_word(&_menu[_selectedItem]._action) != NULL) {
    //Call the action if there is any. Super cumbersome way of
    ((void(*)())pgm_read_word(&_menu[_selectedItem]._action))();
  }
  switch (getType(_selectedItem)) {
    case Menu::TITLE:
    case Menu::TITLE_STRING:

      if (getChild(_selectedItem) != -1) {
        //Set old selected item as title and first line
        _currentTitle = _selectedItem;
        _firstLine = _currentTitle;

        //set old selected item's child as firstItem and selectedItem
        _selectedItem = getChild(_selectedItem);
        _firstItem = _selectedItem;

        _setDisplay();
        display();
      }
      break;

    case Menu::VALUE:
    case Menu::BOOLEAN:
    case Menu::INT:
    case Menu::UNSIGNED_LONG:
    case Menu::FLOAT:
    case Menu::DOUBLE:
      _editValue(_selectedItem);
      break;

    case Menu::STRING:
      _editString(_selectedItem);
      break;
  }
}

int Menu::getNext(int item)
{
  //Check if it is the last item to avoid going outside of the array
  int i = item;
  if ((item + 1) >= _menuSize) {
    return -1;
  }

  if ((pgm_read_word(&_menu[item].parent)) == (pgm_read_word(&_menu[item + 1].parent))) {

    return item + 1;
  } else {
    return -1;
  }
}

int Menu::getPrevious(int item) {
  if (item <= 0) {
    return -1;
  }
  if ((pgm_read_word(&_menu[item].parent)) == (pgm_read_word(&_menu[item - 1].parent))) {
    return item - 1;
  } else {
    return -1;
  }
}

int Menu::getParent(int item) {
  return pgm_read_word(&_menu[item].parent);
}

int Menu::getChild(int item) {
  return pgm_read_word(&_menu[item].child);
}

char* Menu::_getText(char* str, int item) {
  strcpy_P(str, (char*) pgm_read_word(&_menu[item].text));
  return str;
}

void Menu::display()
{
  _lcd->clear();
  for (int i = 0; i < 4; i++) {
    int j = 0;
    char* c = _text;
    //if the ith item isn't null and if it has text
    if (_displayed[i] != -1) {
      //If the current line of text text isn't the title,
      // decide whether or not it is selected
      if (_currentTitle != _displayed[i]) {
        // Not the title
        if (_selectedItem == _displayed[i]) {
          *c = '>';
          _selectLineNumber = i;
        }
        else {
          *c = ' ';
        }
        //advance the pointer
        c++;
      }

      // iterate through the item text and add it to the text to be displayed
      _getText(c, _displayed[i]);
      if ((void*)pgm_read_word(&_menu[_displayed[i]].value)) {

        //Move pointer to the end of the _text string and determine index
        int j = 0;
        c = _text;
        while (*c) {
          c++;
          j++;
        }

        // get the index of the first value character
        int valueIndex = 20 - _getLength(_displayed[i]);

        //write spaces between the text and the value
        for (int k = j; k < valueIndex; k++) {
          _text[k] = ' ';
        }

        //copy the value string to _text
        _getValueStr(&_text[valueIndex], _displayed[i]);
      }

      Serial.println(_text);
      _lcd->setCursor(0, i);
      _lcd->print(_text);
    }
  }
  Serial.println("");
}


void Menu::reset()
{

  _firstItem = 1;
  _firstLine = 0;
  _selectedItem = 1;
  _displayed[0] = _firstLine;
  _displayed[1] = 1;
  _displayed[2] = getNext(_displayed[1]);
  _displayed[3] = getNext(_displayed[2]);

  display();
}


//_SetDisplay figures out which menu Items are displayed on each of the lines
//could be moved into display()
void Menu::_setDisplay()
{


  _displayed[0] = _firstLine;
  if (_firstLine == _currentTitle) {
    //The first line is a title, so the second line is its child
    _displayed[1] = getChild(_displayed[0]);
  }
  else {
    //The first line is not a title, so the second line is the first line's next
    _displayed[1] = getNext(_displayed[0]);
  }
  _displayed[2] = getNext(_displayed[1]);
  _displayed[3] = getNext(_displayed[2]);
}



void Menu::_editValue(int item) {
  char valueString[21];
  char *valuePtr;//pointer to char in valueString.
  //find the length of the value

  //this is type dependent
  int valLength = _getLength(_selectedItem);
  _lcd->setCursor(20 - valLength, _selectLineNumber);
  for (int i = 0; i < valLength; i++) {
    _lcd->write(' ');
  }

  int textLength = 0;
  // itterate through the item text and add it to the text to be displayed
  char c[21];
  _getText(c, _selectedItem);
  textLength = strlen(c);


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
          _setValue(_selectedItem, &f);//setValue stores the value in it's location
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

void Menu::_setValue(int item, void* f) {
  switch (getType(item)) {
    case BOOLEAN:
      *(boolean*) _getValuePtr(item) = *(boolean*)f;
      break;

    case INT:
      *(int*)_getValuePtr(item) = *(int*)f;
      break;

    case UNSIGNED_LONG:
      *(unsigned long*)_getValuePtr(item) = *(unsigned long*)f;
      break;

    case FLOAT:
      *(float*)_getValuePtr(item) = *(float*)f;
    case DOUBLE:
      *(double*)_getValuePtr(item) = *(double*)f;
      break;
    case STRING:
      Serial.println((char*)_getValuePtr(item));
      strcpy((char*)_getValuePtr(item),(char*)f);
      break;
  }
}


void Menu::_editString(int item) {
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
          _setValue(_selectedItem, &valueString);
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

int Menu::_getLength(int item)
{
  double tempVal;
  switch (getType(item)) {
    case BOOLEAN:
      tempVal = *(boolean*) _getValuePtr(item);
      break;

    case INT:
      tempVal = *(int*)_getValuePtr(item);
      break;

    case UNSIGNED_LONG:
      tempVal = *(unsigned long*)_getValuePtr(item);
      break;

    case FLOAT:
    case DOUBLE:
      tempVal = *(double*)_getValuePtr(item);
      break;
    case STRING:
    case TITLE_STRING:
      return strlen((char*)_getValuePtr(item));
      break;
  }
  int length;
  boolean negative = false;
  unsigned long p[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000
  };
  int i = 1;//Start at 1 because there is always a leading zero.
  if (tempVal < 0) negative = true; // add one space for the negative sign
  tempVal = abs(tempVal);//remove negative if there.
  //divide by progressively larger values until the remainder is zero
  //This gives the number of digits before the decimal

  while (i < 9) {
    if ((unsigned long)tempVal / p[i] == 0) {
      break;
    }
    i++;
  }
  if (negative) i++; // add one space for the negative sign

  if (_getPrecision(item) > 0) i = i + _getPrecision(item) + 1; //if there is a decimal place include the it and the extra digits
  return i;
}

Menu::ItemType Menu::getType(int item)
{
  return  (ItemType)pgm_read_word(&_menu[item].type);
}

int Menu::_getPrecision(int item) {
  return  int pgm_read_word(&_menu[item].precision);
}

void* Menu::_getValuePtr(int item) {
  return (void*) pgm_read_word(&_menu[item].value);
}

char* Menu::_getValueStr(char* str, int item) {
  char* ptr = str;
  switch (getType(item)) {
    case Menu::BOOLEAN: //boolean
      *ptr = *(boolean*)_getValuePtr(item) > 0 ? '1' : '0';
      break;

    case Menu::INT: //int

      itoa (*(int*)_getValuePtr(item), ptr, 10 );
      break;

    case Menu::UNSIGNED_LONG: //unsigned long
      {
        unsigned long t = 0, res = 0;
        unsigned long tmp = *(unsigned long*)_getValuePtr(item);
        unsigned long val = *(unsigned long*)_getValuePtr(item);
        int count = 0;

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
        break;
      }

    case Menu::FLOAT:
    case Menu::DOUBLE:
      {

        long p[] = {0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
        char* ret = ptr;
        long integer = *(float*)_getValuePtr(item);
        itoa(integer, ptr, 10);
        while (*ptr != '\0') ptr++;//advance pointer to end of integer section.
        if (_getPrecision(item) != 0) {
          *ptr++ = '.';
          int decimal = floor(abs((*(float*)_getValuePtr(item) - (float)integer) * p[_getPrecision(item)]) + 0.5); //float math isn't exact so need to round from next decimal out
          int i = _getPrecision(item) - 1;
          while (p[i] >= decimal && i >= 0) { //Not sure why, but the while loop doesn't terminate when p[i] and decimal = to 0 that is why the second condition is needed.
            *ptr++ = '0';
            i--;
          }
          if (decimal != 0) {
            itoa(decimal, ptr, 10);
          }
        }
      }
      break;

    case Menu::STRING:
    case Menu::TITLE_STRING:
      strcpy(str, (char*)_getValuePtr(item));
  }
  return str;
}

