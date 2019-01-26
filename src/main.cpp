#include "main.h"

// Create wifiManager
WiFiManager wifiManager;

/*
 * Use pointers so that we can control when managers are
 * constructed and ensure that it isn't before wifiManager
 * has finished doing it's thang.
 */
ConfigManager* configManager;
WebManager* webManager;

// Manage device configuration
Form         configForm;
FormElement* mqttHostForm;
FormElement* mqttUserForm;
FormElement* mqttPassForm;

void createConfigForm() {
  configForm.addElement(formElement::TITLE, "MQTT");
  mqttHostForm = configForm.addElement(formElement::TEXT, "mqtthost",     "Host",     configManager->getString("mqtthost"));
  mqttUserForm = configForm.addElement(formElement::TEXT, "mqttusername", "Username", configManager->getString("mqttusername"));
  mqttPassForm = configForm.addElement(formElement::TEXT, "mqttpassword", "Password", configManager->getString("mqttpassword"));
}

// Homepage
void handleIndex() {
  webManager->sendHtml("Title Page", "<h1>Hi</h1>");
}

// Configuration page
void handleConfig() {

  if(webManager->getServer()->method() == HTTP_POST) {
    ESP8266WebServer* server = webManager->getServer();

    mqttHostForm->setValue(server->arg("mqtthost"));
    mqttUserForm->setValue(server->arg("mqttusername"));
    mqttPassForm->setValue(server->arg("mqttpassword"));

    configManager->setString("mqtthost",     server->arg("mqtthost"));
    configManager->setString("mqttusername", server->arg("mqttusername"));
    configManager->setString("mqttpassword", server->arg("mqttpassword"));
  }

  webManager->sendHtml("Configuration", configForm.render());
}

void setup() {
  // Standard innit
  Serial.begin(9600);

  // Enable OTA updates
  ArduinoOTA.begin();

  // Start wifi connection - Enters blocking loop if config required
  wifiManager.autoConnect(WIFI_AP);

  // We have WiFi, lets move on
  configManager = new ConfigManager;
  webManager    = new WebManager;

  // Create the config form once the Managers are created
  createConfigForm();

  // Add webserver routes
  webManager->addRoute("/", handleIndex);
  webManager->addRoute("/config", handleConfig);

  // Away we go
  webManager->begin();
}

void loop() {
  ArduinoOTA.handle();
  webManager->handle();
}
