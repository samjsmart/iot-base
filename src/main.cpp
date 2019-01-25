#include "main.h"
/*
 * Use pointes so that we can control when managers are
 * constructed and ensure that it isn't before wifiManager
 * has finished doing it's thang.
 */
ConfigManager* configManager;
WebManager* webManager;

Form configForm;

// Create wifiManager
WiFiManager wifiManager;

void handleIndex() {
  webManager->sendHtml("Title Page", "<h1>Hi</h1>");
}

void handleConfig() {
  webManager->sendHtml("test", configForm.render());
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

  // Add webserver routes
  webManager->addRoute("/", handleIndex);
  webManager->addRoute("/config", handleConfig);

  //Create config form
  //String options[] = {"Male", "Female"};
  configForm.addInput(formType::TEXT, "username", "Username");
  configForm.addInput(formType::TEXT, "password", "Password");
  configForm.addInput(formType::TEXT, "email", "Email");
  configForm.addInput(formType::CHECKBOX, "rememberme", "Remember me");

  // Away we go
  webManager->begin();
}

void loop() {
  ArduinoOTA.handle();
  webManager->handle();
}
