#include <Arduino.h>
#include <ESP8266WebServer.h>

class Web {
 private:
   String logs;

 public:
   void log(String logEntry);
};

String page(String title, String content);
