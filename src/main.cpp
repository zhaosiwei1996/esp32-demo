#include <Arduino.h>
#include "oled_display.h"
#include "wifi_manager.h"
#include "mqtt_manager.h" 
#include "led_manager.h"
#include "sensor.h"
#include "time_utils.h"

void setup() {
  Serial.begin(9600); // Initialize serial communication
  initializeSensor();   // Initialize DHT sensor
  // initializeDisplay();  // Initialize OLED display
  initializeLED(); // Initialize LED
  connectWiFi();      // ConnectWiFi
  initializeMQTT();     // Initialize MQTT client
}

void loop() {
  // Get current time and sensor readings
  // String FormatTime = getFormattedTime();
  unsigned long unixTime = getUnixTimestamp();
  float temperature = readTemperature();
  float humidity = readHumidity();
  // Update OLED display
  // updateDisplay(FormatTime, temperature, humidity);
  
  reconnectWiFi(); // Ensure WiFi is connected
  if (!mqttClient.connected()) {
    connectToMQTT(); // Reconnect to MQTT if needed
  }

  mqttpublishData(unixTime, temperature, humidity);
  mqttClient.loop(); // Process incoming MQTT messages
  
  delay(1000); // Update every 1 second
}
