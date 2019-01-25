#include <Arduino.h>
#include <ESP8266WebServer.h>

enum formType {
  RADIO,
  TEXT,
  PASSWORD,
  CHECKBOX
};

class WebManager {
  private:
    ESP8266WebServer* server;

  public:
    WebManager();
    void addRoute(String route, void (*callback)(void));
    void sendHtml(String title,  String content, int httpCode = 200);
    void begin();
    void handle();
};

class FormInput {
  private:
    int type;
    String name;
    String label;
    String* options;
    int optionCount;
    FormInput* nextInput = nullptr;

  public:
    FormInput(int type, String name, String label = "");
    FormInput(int type, String name, String* options, int optionCount, String label = "");
    FormInput* next();
    void setNext(FormInput*);
    String render();
};

class Form {
  private:
    FormInput* firstInput = nullptr;

  public:
    void addInput(int type, String name, String label = "");
    void addInput(int type, String name, String* options, int optionCount, String label = "");
    FormInput* getLastInput();
    String render();
};
