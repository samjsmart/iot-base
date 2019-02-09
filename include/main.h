#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>

#include "webmanager.h"
#include "configmanager.h"
#include "mqttmanager.h"

#define PROJECT_NAME "LightBox"
#define WIFI_AP      "LightBoxAP"

const int LED = D1;

WiFiManager wifiManager;

/*
 * Use pointers so that we can control when managers are
 * constructed and ensure that it isn't before wifiManager
 * has finished doing it's thang.
 */
ConfigManager* configManager;
WebManager*    webManager;
MqttManager*   mqttManager;

// Manage device configuration
Form         configForm;
FormElement* mqttHostForm;
FormElement* mqttUserForm;
FormElement* mqttPassForm;
FormElement* mqttTopicForm;

// Control form
Form         controlForm;

// MQTT Stuff
String      stateTopic;
String      commandTopic;
