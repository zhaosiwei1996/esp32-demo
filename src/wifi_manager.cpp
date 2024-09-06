#include <WiFi.h>
#include "wifi_manager.h"

// Define WiFi settings
const char* ssid = "CMEV_GUEST";
const char* password = "CMEV201811G";

WiFiClient wifiClient;

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("WiFi is not connect");
  }
  Serial.println("Connected to WiFi");
}

void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }
}
