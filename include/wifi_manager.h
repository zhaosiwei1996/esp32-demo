#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

void connectWiFi();
void reconnectWiFi();

extern WiFiClient wifiClient;

#endif // WIFI_MANAGER_H
