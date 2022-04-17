#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

void setupUltrasonic() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

int isObject() {
/*
 * Check the ultrasonic sensor to verify if the bottle is present.
 * Returns True or False
*/  
  
  int tempBuffer[buffSize];
  
  for(int x=0; x<buffSize; x++) {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(20);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(20);
    tempBuffer[x] = pulseIn(ECHO, HIGH) / 58.2; // in Centimeters
    delay(50);
  }
  
  for(int y=0; y<buffSize; y++)
    for(int x=0; x<buffSize-1; x++)
      if (tempBuffer[x] > tempBuffer[x+1]) {
        int temp        = tempBuffer[x+1];
        tempBuffer[x+1] = tempBuffer[x];
        tempBuffer[x]   = temp;
      }

  if(tempBuffer[round(buffSize/2)] < min_distance) return 1;
  return 0;
  
}

#endif
