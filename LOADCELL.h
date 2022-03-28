#ifndef _LOADCELL_H_
#define _LOADCELL_H_

#include "HX711_ADC.h"

HX711_ADC Loadcell(DOUT, SCK);

void setupLoadCell() {
  Loadcell.begin();
}

int binIsFull() {
/*
 * This will monitor the weight of the Bin.
  Returns True or False
*/
  return Loadcell.getData() > 5000;
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
