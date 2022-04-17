#ifndef _LCD_H_
#define _LCD_H_

#include "LiquidCrystal.h"

LiquidCrystal LCD(7, 6, 5, 4, 3, 2); // PIN ASSIGNMENTS FOR LCD TO ARDUINO

void setupLCD() {
  LCD.begin(16, 2);
}

void updateScreen(String cursor_1, String cursor_2) {
/*
 * This will update the LCD screen
 * Accepts Strings to display on first row and second row.
*/
  LCD.clear();  
  LCD.setCursor(0,0);
  LCD.print(cursor_1);
  LCD.setCursor(0,1);
  LCD.print(cursor_2);
}

#endif
