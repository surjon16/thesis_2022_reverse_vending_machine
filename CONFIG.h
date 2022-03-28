#ifndef _CONFIG_H_
#define _CONFIG_H_

#define DOUT          8
#define SCK           9
#define TRIG          10
#define ECHO          11
#define ServoValve    12
#define ServoCoin     13
#define PushButton    A0
#define PhotoSense    A1

const int buffSize = 5;
const int min_distance = 10; // 10cm

long blink_rate;
long longPress;
bool blink_on = true;

int totalPeso = 20; // 20 coins of 1peso by default
int totalCent = 20; // 20 coins of 25cents by default

bool response = false;
int bottleCount = 0;

const float timeout = 5000; // 5 seconds

#endif
