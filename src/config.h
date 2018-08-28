#ifndef CONFIG_H
#define CONFIG_H

// digital pins
int pumpPin = 6;
// int waterPin = 2;
// int upBtnPin = 8;
int joyXPin = A0;
int joyYPin = joyXPin+1;
bool joyInvert = false;
int sonicPin = 4;

int sonicSeconds = 30;
int blynkMillis = 1000;

int tankFull = 5;
int tankEmpty = 50;

double pumpOnHours = 0.25;
// int pumpOnMinutes = 60;
// int pumpOffMinutes = 1;
// int pumpOnSeconds =30;
double pumpOffSeconds = 30.0;
// int pumpOnSeconds = 60 * pumpOnMinutes;
double pumpOnSeconds = pumpOnHours * 60.0 * 60.0;
// int pumpOffSeconds = 60 * pumpOffMinutes;

int displayUpdate = 250; //ms

#ifdef BLYNK
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
#endif

#endif
