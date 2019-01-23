#include <Arduino.h>

class Logger
{
 private:
   String logs;

 public:
   void log(String logEntry);
};
