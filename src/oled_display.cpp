#include <Adafruit_SSD1306.h>
#include "oled_display.h"
#include <WiFi.h>
#include <NTPClient.h>
#include "time_utils.h" 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initializeDisplay() {
  Wire.begin(15, 2); // Initialize I2C communication
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
}

void updateDisplay(String FormatTime, float temperature, float humidity) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print("WiFi: ");
  display.println(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected");

  display.print("Time: ");
  display.println(FormatTime);

  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");
  display.display();
}
