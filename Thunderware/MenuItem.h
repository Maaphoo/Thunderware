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
      TITLE = 0, //Menu items are titles by default because TITLE is the first in the enum.
      VALUE,
      ACTION,
      BOOLEAN,
      INT,
      UNSIGNED_LONG,
      FLOAT,
      DOUBLE,
      STRING
    } itemType;
   
    MenuItem();
    MenuItem(MenuItem* previous,
             MenuItem* next,
             MenuItem* Parent,
             MenuItem* child,
             char* text,
             void (*action)(),
             boolean doActionOnSelect
            );//constructor
    MenuItem* getPrevious();
    MenuItem* getNext();
    MenuItem* getParent();
    MenuItem* getChild();
    ItemType  getType();
    int       getLength();
    void      getValStr(char* ptr);
    int       getPrecision();
    void setPrevious(MenuItem* previous);
    void setNext(MenuItem* next);
    void setParent(MenuItem* parent);
    void setChild(MenuItem* child);
    void setType(ItemType itemType);
    void setValue(void* val, int precision);
    void setPrecision(int precision);
    void setAction(void (*action)());
    void doAction();
    void setDoActionOnSelect(boolean act);
    boolean getDoActionOnSelect();
    void setupVal(char* text, ItemType itemType, void* valPtr, int precision = 0);
    void setText(char* text);

    char* getText();
    void*    _value1;

  private:
    MenuItem* _previous;
    MenuItem* _next;
    MenuItem* _parent;
    MenuItem* _child;
    ItemType  _itemType;
    char*     _text;
    int       _precision;
    void (*_action)();
    boolean    _doActionOnSelect;

};

#endif
