int pumpPin = 3;
int waterPin = 2;
int waterTimeout = 5;

// int pumpOnHours = 1;
int pumpOnMinutes = 60;
// int pumpOffMinutes = 1;
// int pumpOnSeconds =30;
int pumpOffSeconds = 75;
int pumpOnSeconds = 60 * pumpOnMinutes;
// int pumpOnSeconds = 60 * 60 * pumpOnHours;
// int pumpOffSeconds = 60 * pumpOffMinutes;

int displayUpdate = 250; //ms

unsigned char menuIndicator = '>';
