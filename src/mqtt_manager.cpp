#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "mqtt_manager.h"
#include "led_manager.h"
#include "wifi_manager.h"
#include "time_utils.h"

const char* mqttServer = "192.168.0.107";
const int mqttPort = 1883;
const char* mqttupdataTopic = "monitor_topic";
const char* mqttdowndataTopic = "control_topic";
bool hasProcessedMessage = false; // 追踪是否已处理来自本设备的消息

PubSubClient mqttClient(wifiClient);

void initializeMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  mqttClient.setCallback(mqttcontrolLed);
}

void connectToMQTT() {
  String clientName = "ESP32Client_" + WiFi.macAddress();
  clientName.replace(":", "");

  while (!mqttClient.connected()) {
    if (mqttClient.connect(clientName.c_str())) {
      Serial.println("Connected to MQTT as " + clientName);
      mqttClient.subscribe(mqttdowndataTopic);
    } else {
      Serial.print("Failed to connect MQTT, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqttpublishData(unsigned long unixTime, float temperature, float humidity) {
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["unix_time"] = unixTime;
  jsonDoc["source_ip_address"] = WiFi.localIP().toString();
  jsonDoc["client_mac_address"] = WiFi.macAddress();
  jsonDoc["temperature"] = temperature;
  jsonDoc["humidity"] = humidity;
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  // Serial.println("upload temperature data:");
  // Serial.println(jsonString.c_str());
  mqttClient.publish(mqttupdataTopic, jsonString.c_str());
}

void mqttcontrolLed(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println("download control data:");
  Serial.println(message);
  //获取json的vaule
  StaticJsonDocument<200> jsonDoc;
  StaticJsonDocument<200> responseDoc;
  responseDoc["unix_time"] = getUnixTimestamp();
  responseDoc["source_ip_address"] = WiFi.localIP().toString();
  responseDoc["client_mac_address"] = WiFi.macAddress();
  responseDoc["device"] = "led";

  // 解析下行的JSON消息
  DeserializationError error = deserializeJson(jsonDoc, message);
  if (error) {
    responseDoc["msg"] = "Error: Failed to parse JSON";
    Serial.println("Error: Failed to parse JSON");
  } else {
    // 获取控制LED的设备MAC地址、源IP地址和控制动作
    String clientMacAddress = jsonDoc["client_mac_address"];
    String sourceIpAddress = jsonDoc["source_ip_address"];
    String action = jsonDoc["action"];
    // 获取当前设备的IP地址
    String localIpAddress = WiFi.localIP().toString();
    // 判断消息是否来自本设备的IP地址，如果是，则跳过处理，防止死循环
    if (sourceIpAddress == localIpAddress && !hasProcessedMessage && jsonDoc["device"] == "led") {
      hasProcessedMessage = true; // 标记为已处理
      return; // 退出函数，避免继续处理
    } 
    // 如果消息是针对本设备的，执行LED控制操作
    else if (clientMacAddress == WiFi.macAddress()) {
      hasProcessedMessage = false; // 重置标记
      if (action == "on") {
        controlLED(true); // 打开LED
        responseDoc["action"] = "on";
        responseDoc["msg"] = "success";
      } else if (action == "off") {
        controlLED(false); // 关闭LED
        responseDoc["action"] = "off";
        responseDoc["msg"] = "success";
      } else {
        responseDoc["action"] = "unknown action";
        responseDoc["msg"] = "fail";
      }
    } else {
      responseDoc["msg"] = "fail";
      responseDoc["msg"] = "Not for this device";
    }
  }

  // 序列化响应数据并上传
  String responseString;
  serializeJson(responseDoc, responseString);
  Serial.println("upload control resp:");
  Serial.println(responseString);

  // 发布响应消息到控制主题
  mqttClient.publish(mqttdowndataTopic, responseString.c_str());
}

