#include <Arduino.h>
#include <ESP8266WebServer.h>

enum formElement {
  TITLE,
  TEXT,
  PASSWORD,
  CHECKBOX,
  BUTTON,
  SUBMIT
};

class WebManager {
  private:
    ESP8266WebServer* server;

  public:
    WebManager();
    ESP8266WebServer* getServer();
    void              addRoute(String route, void (*callback)(void));
    void              sendHtml(String title,  String content, int httpCode = 200);
    void              begin();
    void              handle();
};

class FormElement {
  private:
    int          type;
    String       name;
    String       label;
    String       value;
    String*      options;
    int          optionCount;
    FormElement* nextElement = nullptr;

  public:
    ~FormElement();
    FormElement(int type, String name, String label = "", String value = "");
    FormElement* next();
    void         next(FormElement*);
    void         setValue(String value);
    String       render();
};

class Form {
  private:
    FormElement* firstElement = nullptr;

  public:
    ~Form();
    FormElement* addElement(int type, String name, String label = "", String value = "");
    FormElement* addSubmit();
    FormElement* getLastInput();
    String       render();
};
