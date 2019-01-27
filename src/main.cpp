#include "main.h"

void createConfigForm() {
  configForm.addElement(formElement::TITLE, "MQTT");
  mqttHostForm = configForm.addElement(formElement::TEXT,     "mqtthost",     "Host",     configManager->getString("mqtthost"));
  mqttUserForm = configForm.addElement(formElement::TEXT,     "mqttusername", "Username", configManager->getString("mqttusername"));
  mqttPassForm = configForm.addElement(formElement::PASSWORD, "mqttpassword", "Password", configManager->getString("mqttpassword"));
  configForm.addSubmit();
}

void createControlForm() {
  controlForm.addElement(formElement::TITLE, "Control");
  controlForm.addElement(formElement::BUTTON, "On");
  controlForm.addElement(formElement::BUTTON, "Off");
}

void handleIndex() {
  webManager->sendHtml(PROJECT_NAME, "<h1>" PROJECT_NAME "</h1><hr><a href=\"/control\" class=\"btn btn-primary w-100 mb-3\">Control</a><a href=\"/config\" class=\"btn btn-primary w-100 mb-3\">Configuration</a>");
}

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

void handleControl() {
  if(webManager->getServer()->method() == HTTP_POST) {
    ESP8266WebServer* server = webManager->getServer();

    if(server->hasArg("On"))
      digitalWrite(LED, HIGH);
    else
      digitalWrite(LED, LOW);
  }

  webManager->sendHtml("Control", controlForm.render());
}

void setup() {
  // Standard innit
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  // Enable OTA updates
  ArduinoOTA.begin();

  // Start wifi connection - Enters blocking loop if config required
  wifiManager.autoConnect(WIFI_AP);

  // We have WiFi, lets move on
  configManager = new ConfigManager;
  webManager    = new WebManager;

  // Create the forms once the Managers are created
  createConfigForm();
  createControlForm();

  // Add webserver routes
  webManager->addRoute("/",        handleIndex);
  webManager->addRoute("/config",  handleConfig);
  webManager->addRoute("/control", handleControl);

  // Away we go
  webManager->begin();
}

void loop() {
  ArduinoOTA.handle();
  webManager->handle();
}
