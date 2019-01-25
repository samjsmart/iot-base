#include "webmanager.h"

WebManager::WebManager() {
  server = new ESP8266WebServer(80);
}

void WebManager::addRoute(String route, void (*callback)()) {
  server->on(route, callback);
}

void WebManager::sendHtml(String title, String content, int httpCode) {
  server->send(
    httpCode,
    "text/html",
    "<!DOCTYPE html>\n"
    "<html lang=\"en\">\n"
    "<head>\n"
      "<meta charset=\"utf-8\">\n"
      "<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
      "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
      "<title>" + title + "</title>\n"
      "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">\n"
      "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css\">\n"
    "</head>\n"
    "<body>\n"
      "<div style=\"margin:0 auto;max-width:900px;text-align:center;\">\n" + content + "</div>\n"
    "</body>\n"
    "</html>"
  );
}

void WebManager::begin() {
  server->begin();
}

void WebManager::handle() {
  server->handleClient();
}

FormInput::FormInput(int type, String name, String label) {
  this->type = type;
  this->name = name;

  if(!label)
    this->label = name;
  else
    this->label = label;
}

FormInput::FormInput(int type, String name, String* options, int optionCount, String label) {
  this->type        = type;
  this->name        = name;
  this->options     = options;
  this->optionCount = optionCount;

  if(!label)
    this->label = name;
  else
    this->label = label;
}

FormInput* FormInput::next() {
  return nextInput;
}

void FormInput::setNext(FormInput* nextInput) {
  this->nextInput = nextInput;
}

String FormInput::render() {
  String html;

  switch (type) {
    case RADIO:
    break;


    case CHECKBOX:
      html =  "<div class=\"form-check\">\n"
              "<input class=\"form-check-input\" type=\"checkbox\" id=\"" + name + "\">\n"
              "<label class=\"form-check-label\" for=\"" + name + "\">" + label + "</label>\n"
              "</div>\n";
    break;

    default:
    case TEXT:
      html = "<div class=\"form-group\">\n"
             "<label for=\"" + name + "\">" + label + "</label>\n"
             "<input type=\"text\" class=\"form-control\" id=\"" + name + "\">\n"
             "</div>\n";
    break;
  }

  return html;
}

FormInput* Form::getLastInput() {
  FormInput* currentItem = firstInput;

  while(currentItem->next() != nullptr) {
    currentItem = currentItem->next();
  }

  return currentItem;
}

void Form::addInput(int type, String name, String label) {
  if(firstInput == nullptr) {
    firstInput = new FormInput(type, name, label);
  } else {
    getLastInput()->setNext(new FormInput(type, name, label));
  }
}

void Form::addInput(int type, String name, String* options, int optionCount, String label) {
  if(firstInput == nullptr) {
    firstInput = new FormInput(type, name, label);
  } else {
    getLastInput()->setNext(new FormInput(type, name, options, optionCount, label));
  }
}

String Form::render() {
  String content = "<form action=\"post\">";
  Serial.println("WM - Rendering");

  FormInput* currentItem = firstInput;

  while(currentItem != nullptr) {
    content     += currentItem->render();
    currentItem = currentItem->next();
  }

  content += "</form>";

  return content;
}
