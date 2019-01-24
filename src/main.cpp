#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include "web.h"
#include "logger.h"


void setup() {
  Serial.begin(9600);

  // Enable OTA updates
  ArduinoOTA.begin();

  // Create wifiManager
  WiFiManager wifiManager;

  // Start wifi connection - Enters blocking loop if config required
  wifiManager.autoConnect("AutoConnectAP");

  //Add webserver routes
  /*server.on("/", [](){
    server.send(200, "text/html", page("Index", "<h1>Playground</h1><br><form method=\"POST\" action=\"/led\"><button type=\"submit\" value=\"submit\" class=\"btn btn-primary\">LED Toggle</button></form>"));
  });*/

  /*server.on("/led", [](){
     ledState = !ledState;
     digitalWrite(LED, ledState);
     server.sendHeader("Location", String("/"), true);
     server.send ( 302, "text/plain", "");
  });*/
}

void loop() {
  ArduinoOTA.handle();
}
