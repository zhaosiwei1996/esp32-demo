#ifndef OLEDDISPLAY_H
#define OLEDDISPLAY_H

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

void initializeDisplay();
void updateDisplay(String FormatTime, float temperature, float humidity);


#endif // OLEDDISPLAY_H
