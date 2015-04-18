#include <avr/pgmspace.h>
const char string_0[] PROGMEM = "Main Menu";   // "String 0" etc are strings to store - change to suit.
const char string_1[] PROGMEM = "This is a test String";
const char string_2[] PROGMEM = "String 2";
const char string_3[] PROGMEM = "String 3";
const char string_4[] PROGMEM = "String 4";
const char string_5[] PROGMEM = "String 5";


// Then set up a table to refer to your strings.

const char* const string_table[] PROGMEM = {string_0, 
                                          string_1, 
                                          string_2,  
                                          string_3, 
                                          string_4,
                                          string_5
//                                          string_6,
//                                          string_7,
//                                          string_8,
//                                          string_9,
//                                          string_10,
//                                          string_11,
//                                          string_12,
//                                          string_13,
                                          
                                          };

char buffer[30];    // make sure this is large enough for the largest string it must hold


     // Necessary casts and dereferencing, just copy.
