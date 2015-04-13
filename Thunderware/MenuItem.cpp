/*
  MenuItem.cpp - Library for activating the buzzer which
      signals changes in the extruder's state and safety
      errors. The buzzer pin is 17

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "MenuItem.h"

MenuItem::MenuItem(){}
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
_child= child;
_text = text;
_value = value;
_precision = 2;
_action = action;
_doActionOnSelect = doActionOnSelect;
itemType = TITLE; //The default Item type
 }
 
MenuItem* MenuItem::getPrevious(){return _previous;}
MenuItem* MenuItem::getNext(){return _next;}
MenuItem* MenuItem::getParent(){return _parent;}
MenuItem* MenuItem::getChild(){return _child;}
//ItemType MenuItem::getType(){return _itemType;}
double MenuItem::getValue(){return _value;}
int MenuItem::getPrecission(){return _precision;}


void MenuItem::setPrevious(MenuItem* previous){_previous = previous;}
void MenuItem::setNext(MenuItem* next){_next = next;}
void MenuItem::setParent(MenuItem* parent){_parent = parent;}
void MenuItem::setChild(MenuItem* child){_child = child;}
void MenuItem::setValue(double value){ _value = value;}
void MenuItem::setPrecision(int precision){_precision = precision;}
void MenuItem::setAction(void (*action)()){_action = action;}
void MenuItem::doAction(){_action();}



char* MenuItem::getText(){return _text;}
void MenuItem::setText(char* text){_text = text;}
