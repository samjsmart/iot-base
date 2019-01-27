#include "mqttmanager.h"


MqttCallback::MqttCallback(char* topic, void (*callback)(byte* payload, unsigned int length)) {
  this->topic    = topic;
  this->callback = callback;
}

void MqttCallback::next(MqttCallback* nextCallback) {
  this->nextCallback = nextCallback;
}

MqttCallback* MqttCallback::next() {
  return nextCallback;
}

char* MqttCallback::getTopic() {
  return topic;
}

void MqttCallback::invoke(byte* payload, unsigned int length) {
  callback(payload, length);
}

MqttManager::MqttManager(const char* clientID, const char* host, const char* username, const char* password) {
  pubSubClient = new PubSubClient(wifiClient);

  this->clientID  = clientID;
  this->host      = host;
  this->username  = username;
  this->password  = password;

  std::function<void(char*, uint8_t*, unsigned int)> boundCallback = std::bind(&MqttManager::callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

  //TODO: resolve hostname if passed one
  //Convert string to IP
  char buffer[256];
  int   IP[4];
  strcpy(buffer, host);

  IP[0] = atoi(strtok(buffer, "."));
  IP[1] = atoi(strtok(NULL, "."));
  IP[2] = atoi(strtok(NULL, "."));
  IP[3] = atoi(strtok(NULL, "."));

  IPAddress ip(IP[0], IP[1], IP[2], IP[3]);

  pubSubClient->setServer(ip, 1883);
  pubSubClient->setCallback(boundCallback);
}

void MqttManager::on(char* topic, void (*callback)(byte* payload, unsigned int length)) {
  MqttCallback* newCallback = new MqttCallback(topic, callback);

  if(firstCallback == nullptr) {
    firstCallback = newCallback;
  } else {
    getLastCallback()->next(newCallback);
  }
}

MqttCallback* MqttManager::getLastCallback() {
  MqttCallback* currentCallback = firstCallback;

  while(currentCallback->next() != nullptr) {
    currentCallback = currentCallback->next();
  }

  return currentCallback;
}

void MqttManager::reconnect() {
  //TODO: fix the issue with authenticated login
  if(pubSubClient->connect(clientID)) {
    Serial.println("MM - Connected");

    MqttCallback* currentCallback = firstCallback;

    while(currentCallback != nullptr) {
      Serial.printf("MM - Subscribing to: %s\n", currentCallback->getTopic());

      pubSubClient->subscribe(currentCallback->getTopic());
      currentCallback = currentCallback->next();
    }

  } else {
    Serial.printf("MM - Failed to connect - Reason: %i\n", pubSubClient->state());

    return;
  }
}

void MqttManager::callback(char* topic, byte* payload, unsigned int length) {
  MqttCallback* currentCallback = firstCallback;

  while(currentCallback != nullptr) {
    if(!strcmp(topic, currentCallback->getTopic())) {
      currentCallback->invoke(payload, length);

      return;
    }
    currentCallback = currentCallback->next();
  }

}

void MqttManager::handle() {
  if(!pubSubClient->connected()) {
    reconnect();
  }
  pubSubClient->loop();
}
