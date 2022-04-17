#ifndef _LOADCELL_H_
#define _LOADCELL_H_

#include "HX711_ADC.h"

HX711_ADC Loadcell(DOUT, SCK);

void setupLoadCell() {
  float calFactor = 696.0;
  Loadcell.begin();
  Loadcell.start(2000, true);
  if (Loadcell.getTareTimeoutFlag())
      updateScreen(
        "TIMEOUT! PLEASE", 
        "CHECK THE PINS."
      );
  else Loadcell.setCalFactor(calFactor);  
}

int binIsFull() {
/*
 * This will monitor the weight of the Bin.
  Returns True or False
*/
  if (Loadcell.update()) {
    current_weight = Loadcell.getData();
    updateScreen(String(current_weight), "");
    Serial.println(current_weight);
    delay(500);
  }
  return current_weight >= 5000;
}

void calibrationMode() {
  
  updateScreen(
    "  CALIBRATION", 
    "     MODE"
  );
  
  Loadcell.start(timeout, true);
  if (Loadcell.getTareTimeoutFlag() || Loadcell.getSignalTimeoutFlag())
      updateScreen(
        "TIMEOUT! PLEASE", 
        "CHECK THE PINS."
      );  
  else {
    Loadcell.setCalFactor(1.0);
    updateScreen(
      "SETTING CALIBRTN", 
      "FACTOR TO 1.0"
    );
  }
  while (!Loadcell.update());
  Loadcell.tareNoDelay();
  while(Loadcell.getTareStatus() == false) Loadcell.update();

  for(int i=10; i>=0; i--) {
    updateScreen(
      "PUT THE 1kg LOAD", 
      String("ON THE SCALE." + String(i) + "s")
    );
    Loadcell.update();
    delay(1000);    
  }

  float known_mass = 1000.0;
  Loadcell.refreshDataSet();
  float calibrationValue = Loadcell.getNewCalibration(known_mass);

  updateScreen(
    "COMPLETE!", 
    String("CAL VALUE: " + String(calibrationValue))
  );
  
  while(!isButton()) {
    delay(500);
    updateScreen(
      "COMPLETE!", 
      String("WEIGHT: " + String(Loadcell.getData()))
    );
  }

  
}

float getWeight() {
}

#endif
