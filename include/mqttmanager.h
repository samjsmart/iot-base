#include <Arduino.h>

class MqttCallback {
  private:
    String        topic;
    void (*callback)(String message);
    MqttCallback* nextCallback = nullptr;

  public:
    MqttCallback(String topic, void (*callback)(String message));
    MqttCallback* next();
    void next(MqttCallback* next);
};

class MqttManager {
  private:
    MqttCallback* firstCallback = nullptr;

  public:
    void on(String topic, void (*callback)(String message));
};
