#ifndef _PUSHBUTTON_H
#define _PUSHBUTTON_H

void setupButtons() {  
  pinMode(PushButton, INPUT);
}

int isButton() {
/*
 * Check the button if pushed.
 * Returns True or False
*/
  return digitalRead(PushButton);
}

#endif
