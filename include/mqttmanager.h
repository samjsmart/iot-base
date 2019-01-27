#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MqttCallback {
  private:
    char* topic;
    void (*callback)(byte* payload, unsigned int length);
    MqttCallback* nextCallback = nullptr;

  public:
    MqttCallback(char* topic, void (*callback)(byte* payload, unsigned int length));
    MqttCallback* next();
    void next(MqttCallback* nextCallback);
    char* getTopic();
    void invoke(byte* payload, unsigned int length);
};

class MqttManager {
  private:
    const char*        host;
    const char*        clientID;
    const char*        username;
    const char*        password;
    WiFiClient    wifiClient;
    PubSubClient* pubSubClient;
    MqttCallback* firstCallback = nullptr;

  public:
    MqttManager(const char* clientID, const char* host, const char* username = "", const char* password = "");
    void on(char* topic, void (*callback)(byte* payload, unsigned int length));
    MqttCallback* getLastCallback();
    void callback(char* topic, byte* payload, unsigned int length);
    void handle();
    void setHost(char* host);
    void setUsername(char* username);
    void setPassword(char* password);
    void reconnect();
};
