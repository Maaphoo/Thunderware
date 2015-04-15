/*
  MenuItem.h - Library for the items of the LCD menus

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef MenuItem_h
#define MenuItem_h

#include "Arduino.h"

class MenuItem
{
  public:
    enum ItemType {
      TITLE = 0,
      VALUE,
      ACTION,
      BOOLEAN,
      INT,
      UNSIGNED_LONG,
      FLOAT,
      DOUBLE,
      STRING
    } itemType;
    
    union Value {
      boolean* b;
      int* i;
      unsigned long* l;
      float* f;
      double* d;
      char*  str;
    } value1;


    MenuItem();
    MenuItem(MenuItem* previous,
             MenuItem* next,
             MenuItem* Parent,
             MenuItem* child,
             char* text,
             double value,
             void (*action)(),
             boolean doActionOnSelect
            );//constructor
    MenuItem* getPrevious();
    MenuItem* getNext();
    MenuItem* getParent();
    MenuItem* getChild();
    ItemType  getType();
    double    getValue();
    int       getLength();
    void     getValStr(char* ptr);
    int       getPrecision();

    void setPrevious(MenuItem* previous);
    void setNext(MenuItem* next);
    void setParent(MenuItem* parent);
    void setChild(MenuItem* child);
    void setType(ItemType itemType);
    void setValue(double value);
    void setValue(void* val, int precision);
    void setValuePtr(float* val);
    void setPrecision(int precision);
    void setAction(void (*action)());
    void doAction();
    void setupVal(char* text, ItemType itemType, void* valPtr, int precision = 0);

    char* getText();
    void setText(char* text);
    void*    _value1;

  private:
    MenuItem* _previous;
    MenuItem* _next;
    MenuItem* _parent;
    MenuItem* _child;
    ItemType  _itemType;
    char*     _text;
    double    _value;
    int       _precision;
    void (*_action)();
    boolean    _doActionOnSelect;

};

#endif
