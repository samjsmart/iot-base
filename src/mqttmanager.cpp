#include "mqttmanager.h"


MqttCallback::MqttCallback(String topic, void (*callback)(String message)) {
  this->topic    = topic;
  this->callback = callback;
}

void MqttCallback::next(MqttCallback* next) {
  this-> nextCallback = nextCallback;
}

MqttCallback* MqttCallback::next() {
  return nextCallback;
}

void MqttManager::on(String topic, void (*callback)(String message)) {
  firstCallback = new MqttCallback(topic, callback);
}
