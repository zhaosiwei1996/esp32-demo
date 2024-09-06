#include <Arduino.h>
#include "led_manager.h"

const int ledPin = 2;

void initializeLED() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  digitalWrite(ledPin, LOW); // Ensure LED is off initially
}

void controlLED(bool state) {
  digitalWrite(ledPin, state ? HIGH : LOW); // Turn LED on or off
}
