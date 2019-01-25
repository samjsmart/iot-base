#include <Arduino.h>
#include <FS.h>

class ConfigManager {
  public:
    ConfigManager();
    bool itemExists(String key);
    void deleteItem(String key);
    void setString(String key, String value);
    String getString(String key);
};
