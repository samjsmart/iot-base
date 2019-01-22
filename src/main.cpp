#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "web.h"

const int LED     = D6;
int ledState      = LOW;
ESP8266WebServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  ArduinoOTA.begin();

  //Pretty fly for a WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin("The Smarties", "23March2018");
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  //Add webserver routes
  server.on("/", [](){
    server.send(200, "text/html", page("Index", "<h1>Playground</h1><br><form method=\"POST\" action=\"/led\"><button type=\"submit\" value=\"submit\" class=\"btn btn-primary\">LED Toggle</button></form>"));
  });


  server.on("/led", [](){
     ledState = !ledState;
     digitalWrite(LED, ledState);
     server.sendHeader("Location", String("/"), true);
     server.send ( 302, "text/plain", "");
  });

  //Start webserver
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}
