#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <PubSubClient.h>
#include <ArduinoJson.h>

// Define MQTT topics
extern const char* mqttupdataTopic;
extern const char* mqttdowndataTopic;

void initializeMQTT();
void connectToMQTT();
void mqttpublishData(unsigned long currentTime, float temperature, float humidity);
void mqttcontrolLed(char* topic, byte* payload, unsigned int length);

extern PubSubClient mqttClient;

#endif // MQTT_MANAGER_H
