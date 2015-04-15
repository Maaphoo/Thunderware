/*
  MenuItem.cpp - Library for activating the buzzer which
      signals changes in the extruder's state and safety
      errors. The buzzer pin is 17

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MenuItem.h"

MenuItem::MenuItem() {}
MenuItem::MenuItem(MenuItem* previous,
                   MenuItem* next,
                   MenuItem* parent,
                   MenuItem* child,
                   char* text,
                   double value,
                   void(*action)(),
                   boolean doActionOnSelect
                  )//constructor)
{
  _previous = previous;
  _next = next;
  _parent = parent;
  _child = child;
  _text = text;
  _value = value;
  _precision = 2;
  _action = action;
  _doActionOnSelect = doActionOnSelect;
  itemType = TITLE; //The default Item type
}

MenuItem* MenuItem::getPrevious() {
  return _previous;
}
MenuItem* MenuItem::getNext() {
  return _next;
}
MenuItem* MenuItem::getParent() {
  return _parent;
}
MenuItem* MenuItem::getChild() {
  return _child;
}
MenuItem::ItemType MenuItem::getType() {
  return _itemType;
}
double MenuItem::getValue() {
  return _value;
}
//void*  MenuItem::getValue(){return _value1;}
int MenuItem::getLength() {
  double tempVal;
  switch (getType()) {
    case MenuItem::BOOLEAN:
      tempVal = *(boolean*)_value1;
      break;

    case MenuItem::INT:
      tempVal = *(int*)_value1;
      break;

    case MenuItem::UNSIGNED_LONG:
      tempVal = *(unsigned long*)_value1;
      break;

    case MenuItem::FLOAT:
    case MenuItem::DOUBLE:
      tempVal = *(double*)_value1;
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

  if (_precision > 0) i = i + _precision + 1; //if there is a decimal place include the it and the extra digits
  return i;
}

void MenuItem::getValStr(char* ptr) {
  char* tempPtr;
  switch (_itemType) {
    case MenuItem::BOOLEAN: //boolean
      *ptr = *(boolean*)_value1 > 0 ? '1' : '0';
      break;

    case MenuItem::INT: //int

      itoa (*(int*)_value1, ptr, 10 );
      break;

    case MenuItem::UNSIGNED_LONG: //unsigned long
      {
        unsigned long t = 0, res = 0;
        unsigned long tmp = *(unsigned long*)_value1;
        unsigned long val = *(unsigned long*)_value1;

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

    case MenuItem::FLOAT:
    case MenuItem::DOUBLE:
      long p[] = {0, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
      char* ret = ptr;
      long integer = *(float*)_value1;
      itoa(integer, ptr, 10);
      while (*ptr != '\0') ptr++;//advance pointer to end of integer section.

      if (_precision != 0) {
        *ptr++ = '.';
        int decimal = floor(abs((*(float*)_value1 - (float)integer) * p[_precision]) + 0.5); //float math isn't exact so need to round from next decimal out
        int i = _precision - 1;
        while (p[i] >= decimal) {
          *ptr++ = '0';
          i--;
        }
        if (decimal != 0) {
          itoa(decimal, ptr, 10);
        }
      }

      break;

  }

}

int MenuItem::getPrecision() {
  return _precision;
}


void MenuItem::setPrevious(MenuItem* previous) {
  _previous = previous;
}
void MenuItem::setNext(MenuItem* next) {
  _next = next;
}
void MenuItem::setParent(MenuItem* parent) {
  _parent = parent;
}
void MenuItem::setChild(MenuItem* child) {
  _child = child;
}
void MenuItem::setType(ItemType type) {
  _itemType = type;
}
void MenuItem::setValue(double value) {
  _value = value;
}
void MenuItem::setValue(void* val, int precision = 0)
{
  switch (_itemType) {
    case MenuItem::BOOLEAN:
      precision = 0;
      *(boolean*)_value1 = (boolean) * (float*)val;

      break;

    case MenuItem::INT:
      *(int*)_value1 = (int) * (float*)val;
      break;

    case MenuItem::UNSIGNED_LONG:
      *(unsigned long*)_value1 = *(unsigned long*)val;
      break;

    case MenuItem::FLOAT:
      *(float*)_value1 = *(float*)val;
      break;

    case MenuItem::DOUBLE:
      *(double*)_value1 = *(double*)val;
      break;

    case MenuItem::STRING: //not sure if this is correct
      *(char*)_value1 = *(char*)val;
      break;

  }
  _precision = precision;
}
void MenuItem::setValuePtr(float* ptr)
{
  if (_itemType == MenuItem::FLOAT) {
    value1.f = ptr;
  }
}
void MenuItem::setPrecision(int precision) {
  _precision = precision;
}
void MenuItem::setAction(void (*action)()) {
  _action = action;
}
void MenuItem::setupVal(char* text,
                        ItemType itemType,
                        void* valPtr,
                        //                   void* val,
                        int precision
                       )
{
  setText(text);
  _itemType = itemType;
  _value1 = valPtr;
  //  setValue(val);
  _precision = precision;
}
void MenuItem::doAction() {
  _action();
}



char* MenuItem::getText() {
  return _text;
}
void MenuItem::setText(char* text) {
  _text = text;
}
