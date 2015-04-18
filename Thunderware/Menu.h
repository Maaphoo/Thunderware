/*
  Menu.h - Library for controlling LCD menus

  Created by Matthew P. Rogge, Februrary 12, 2014.
  Released into the public domain.
*/
#ifndef Menu_h
#define Menu_h

#include "Arduino.h"
#include "MenuItem.h"
#include <LiquidCrystal.h>
#include <Keypad.h>

class MenuItem;
class LiquidCrystal;
class Keypad;
class Menu
{
  public:
    Menu(MenuItem* root, LiquidCrystal* lcd, Keypad* kpd);
    void up();
    void down();
    void back();
    void select();
    void reset();
    void display();
    void printSelected();
    
  private:
    void      _setDisplay();
    void      _editValue();
    void      _editString();
    int       _selectLineNumber;
    
    MenuItem* _firstItem;
    MenuItem* _root;
    MenuItem* _selectedItem;
    MenuItem* _firstLine;
    MenuItem* _currentItem;
    MenuItem* _currentTitle;
    MenuItem* _nextItem;
    MenuItem* _displayed[4];
    
    LiquidCrystal* _lcd;
    Keypad* _kpd;
    char _key;
    
    char*     _title[21];
    char      _text[21];//holds a line of text for the LCD
};

#endif
