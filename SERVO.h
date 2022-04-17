#ifndef _SERVO_H_
#define _SERVO_H_

#include <Servo.h>

Servo Valve, Coin;

void setupServos() {
  pinMode(ServoValve, OUTPUT);
  pinMode(ServoCoin, OUTPUT);   
  Valve.attach(ServoValve);
  Coin.attach(ServoCoin);
}

void acceptBottle() {
/*
 * This will set the servo to open the Bin and accept the bottle.
*/ 
  Valve.write(150);
  delay(2500);
  Valve.write(100);
  delay(500);
}

void rejectBottle() {
/*
 * This will set the servo to open the claim area to reject the bottle.
*/ 
  Valve.write(50);
  delay(2500);
  Valve.write(100);
  delay(500);
}

void closeBin() {
/*
 * This will set the servo to close the bin to scan incoming bottles.
*/  
  Valve.write(100);
  delay(500);
}

void pushCent() {
/*
 * This will set the servo to push 25 cents.
*/  
  Coin.write(50);
  delay(300);
  Coin.write(100);
  delay(300);
}

void pushPeso() {
/*
 * This will set the servo to push 1 peso.
*/  
  Coin.write(150);
  delay(300);
  Coin.write(100);
  delay(300);
}

#endif
