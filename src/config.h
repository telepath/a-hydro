#ifndef CONFIG_H
#define CONFIG_H

// digital pins
int pumpPin = 5;
int waterPin = 2;
// int upBtnPin = 8;
int joyXPin = A0;
int joyYPin = joyXPin+1;
bool joyInvert = true;
int waterTimeout = 5;

double pumpOnHours = 0.25;
// int pumpOnMinutes = 60;
// int pumpOffMinutes = 1;
// int pumpOnSeconds =30;
double pumpOffSeconds = 30;
// int pumpOnSeconds = 60 * pumpOnMinutes;
double pumpOnSeconds = pumpOnHours * 60.0 * 60.0;
// int pumpOffSeconds = 60 * pumpOffMinutes;

int displayUpdate = 250; //ms

#endif
