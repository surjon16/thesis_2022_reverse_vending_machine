#ifndef _PHOTOSENSOR_H
#define _PHOTOSENSOR_H

void setupPhotoSensor() {
  pinMode(PhotoSense, INPUT);
}

int isPET() {
/*
 * Use the photoelectric sensor to check if the bottle is PET.
 * Returns True or False
*/ 
  int data = 0;
  int totalSamples = 100;
  for(int samples=1; samples<=totalSamples; samples++){
    if (digitalRead(PhotoSense)) data++;
    delay(5);
  }
  float average = data/totalSamples;
  if(average >= 0.9) return 0; // 90 Percent non-PET
  else return 1; // PET
  
}

#endif
