#include "webmanager.h"

WebManager::WebManager() {
  server = new ESP8266WebServer(80);
}

void WebManager::addRoute(String route, void (*callback)()) {
  server->on(route, callback);
}

void WebManager::sendHtml(String title, String content, int httpCode) {

  //TODO: sort this mess out
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
      "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.2.1/css/bootstrap.min.css\">\n"
    "</head>\n"
    "<body>\n"
      "<div style=\"margin:0 auto;max-width:450px;text-align:center;padding:1em 0em;\">\n" + content + "</div>\n"
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

ESP8266WebServer* WebManager::getServer() {
  return server;
}

FormElement::FormElement(int type, String name, String label, String value) {
  this->type  = type;
  this->name  = name;
  this->value = value;

  if(label == "")
    this->label = name;
  else
    this->label = label;
}

FormElement::~FormElement() {
  if(nextElement != nullptr)
    delete nextElement;
}

FormElement* FormElement::next() {
  return nextElement;
}

void FormElement::next(FormElement* nextElement) {
  this->nextElement = nextElement;
}

void FormElement::setValue(String value) {
  this->value = value;
}

String FormElement::render() {
  String html;

  switch (type) {

    case formElement::TITLE:
      html =  "<div class=\"form-group\">\n"
              "<h3>" + name + "</h3><hr>"
              "</div>\n";
    break;

    case formElement::CHECKBOX:
      html =  "<div class=\"form-check\">\n"
              "<input class=\"form-check-input\" type=\"checkbox\" id=\"" + name + "\">\n"
              "<label class=\"form-check-label\" for=\"" + name + "\">" + label + "</label>\n"
              "</div>\n";
    break;

    case formElement::BUTTON:
      html =  "<div class=\"form-group\">\n"
              "<button class=\"btn btn-primary\" type=\"submit\" name=\"" + name + "\" id=\"" + name + "\" value=\"" + name + "\">" + label + "</button>\n"
              "</div>\n";
    break;

    case formElement::PASSWORD:
      html = "<div class=\"form-group\">\n"
             "<label for=\"" + name + "\">" + label + "</label>\n"
             "<input type=\"password\" class=\"form-control\" name=\"" + name + "\" id=\"" + name + "\">\n"
             "</div>\n";
    break;

    case formElement::SUBMIT:
      html =  "<div class=\"form-group\">\n"
              "<button type=\"submit\" class=\"btn btn-primary\">Submit</button>\n"
              "</div>\n";
    break;

    default:
    case formElement::TEXT:
      html = "<div class=\"form-group\">\n"
             "<label for=\"" + name + "\">" + label + "</label>\n"
             "<input type=\"text\" class=\"form-control\" name=\"" + name + "\" id=\"" + name + "\" value=\"" + value + "\">\n"
             "</div>\n";
    break;
  }

  return html;
}

Form::~Form() {
  if(firstElement != nullptr)
    delete firstElement;
}

FormElement* Form::getLastInput() {
  FormElement* currentElement = firstElement;

  while(currentElement->next() != nullptr) {
    currentElement = currentElement->next();
  }

  return currentElement;
}

FormElement* Form::addElement(int type, String name, String label, String value) {
  FormElement* newElement = new FormElement(type, name, label, value);

  if(firstElement == nullptr) {
    firstElement = newElement;
  } else {
    getLastInput()->next(newElement);
  }

  return newElement;
}

FormElement* Form::addSubmit() {
  return addElement(formElement::SUBMIT, "");
}

String Form::render() {
  String content = "<form method=\"post\">";

  FormElement* currentElement = firstElement;

  while(currentElement != nullptr) {
    content     += currentElement->render();
    currentElement = currentElement->next();
  }

  content += "</form>\n";

  return content;
}
