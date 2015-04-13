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
      ACTION
    } itemType;

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
    double getValue();
    int getPrecission();
    
    void setPrevious(MenuItem* previous);
    void setNext(MenuItem* next);
    void setParent(MenuItem* parent);
    void setChild(MenuItem* child);
    void setItemType(ItemType itemType);
    void setValue(double value);
    void setPrecision(int precision);
    void setAction(void (*action)());
    void doAction();
    
    char* getText();
    void setText(char* text);

  private:
    MenuItem* _previous;
    MenuItem* _next;
    MenuItem* _parent;
    MenuItem* _child;
//    ItemType  _itemType;
//    ValueType _valueType;
    char*     _text;
    double    _value;
    int       _precision;
    void (*_action)();
    boolean    _doActionOnSelect;

};

#endif
