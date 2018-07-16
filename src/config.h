#ifndef CONFIG_H
#define CONFIG_H

// digital pins
int pumpPin = 3;
int waterPin = 2;
int upBtnPin = 8;
int joyXPin = A0;
int joyYPin = A1;
int waterTimeout = 5;

int pumpOnHours = 12;
// int pumpOnMinutes = 60;
// int pumpOffMinutes = 1;
// int pumpOnSeconds =30;
double pumpOffSeconds = 25;
// int pumpOnSeconds = 60 * pumpOnMinutes;
double pumpOnSeconds = pumpOnHours * 60.0 * 60.0;
// int pumpOffSeconds = 60 * pumpOffMinutes;

int displayUpdate = 250; //ms

#endif
