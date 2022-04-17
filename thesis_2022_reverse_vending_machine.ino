#include "CONFIG.h"
#include "PUSHBUTTON.h"
#include "LCD.h"
#include "LOADCELL.h"
#include "PHOTOSENSOR.h"
#include "SERVO.h"
#include "ULTRASONIC.h"

void setup() {

  Serial.begin(9600);

  setupButtons();
  setupLCD();
  setupLoadCell();
  setupPhotoSensor();
  setupServos();
  setupUltrasonic();
  
}

void loop() {

  // This will check if the bin is full.
  while(binIsFull()) {
    if((millis() - blink_rate) >= 500) {
  
      String cursor_1 = "";
      String cursor_2 = "";
     
      if(blink_on) {
        cursor_1 = "THE BIN IS FULL!";
        blink_on = false;
      }
      else blink_on = true;
      
      updateScreen(cursor_1, cursor_2);      
      blink_rate = millis();
      
    }
  }

  // This will check if the object is detected.
  while(!isObject()) {
    if((millis() - blink_rate) >= 500) {
  
      String cursor_1 = "INSERT BOTTLE.";
      String cursor_2 = "Credits: ";
     
      if(blink_on) {
        cursor_2 = String("Credits: " + String((float)(bottleCount*0.25)));
        blink_on = false;
      }
      else blink_on = true;
      
      updateScreen(cursor_1, cursor_2);      
      blink_rate = millis();
      
    }

    if(!isButton()) longPress = millis();
    if(isButton() && (millis() - longPress) >= timeout) calibrationMode();
        
  }
  
  updateScreen(
    "Bottle Detected.",
    ""
  );
  
  delay(500);

  // This will classify PET and non-PET
  if(isPET()) {
    bottleCount++;
    updateScreen(
      "Bottle is PET.",
      ""
    );
    acceptBottle();
  }
  else {      
    updateScreen(
      "Bottle not PET.",
      ""
    );
    rejectBottle();
  }

  // Prompt user to insert more or collect reward.
  if(bottleCount > 0) {    
    
    if(!promptUser(String("PUSH to put more"), timeout)) {
      
      if(promptUser("PUSH to get " + String((float)(bottleCount*0.25)), timeout)) calculateReward();
      else updateScreen("Thank you for", "your Donation.");
      
      bottleCount = 0;
      delay(2000);
      
    }    
    
  }   
}

int promptUser(String message, float timeOut) {
/*
 * This will verify if the user
 * pushed the button or not.
 * Returns True or False
*/

  int counter = timeOut/1000;
  long timer = millis();
  
  while(counter >= 0 && !isButton()) {
    if((millis() - timer) >= 1000) {
      timer = millis();
      updateScreen(
        message,
        "Time Left: " + String(counter) + "s"
      );
      counter--;
    }
  }
  
  delay(500);
  
  if(counter > 0) return 1;
  return 0;

}

void calculateReward() {
/*
 * This will calculate the total reward and update the remaining amount.
*/

//  Get the total amount.
  float totalAmount = totalPeso + (totalCent * 0.25);
  float totalReward = bottleCount * 0.25;

  if(totalAmount == 0) updateScreen("Zero balance.", "Donating ..."); //updateScreen("Not enough", "money left.");
  else {      
    if(totalAmount >= totalReward) { // If the total Amount is sufficient.
      while(totalReward > 0) {
        if(totalReward >= 1 && totalPeso - 1 >= 0) {
          pushPeso();
          bottleCount -= 4;
          totalPeso--;
        }
        else {
          pushCent();
          bottleCount--;
          totalCent--;
        }
        totalReward = bottleCount * 0.25;
        updateScreen("Reward Left:", String(totalReward));
      }
    }
    else { // If the total Amount is insufficient for the Reward.
      updateScreen("We can only give", String(totalAmount) + " reward.");
      while(totalAmount > 0) {
        if(totalPeso > 0) {
          pushPeso();
          totalPeso--;
        }
        if(totalCent > 0) {
          pushCent();
          totalCent--;
        }
        totalAmount = totalPeso + (totalCent * 0.25);
      }
      bottleCount = 0;
    }
    updateScreen("Thank you!", "");
  }
}
