#include "configmanager.h"

ConfigManager::ConfigManager() {
  SPIFFS.begin();

  if(!SPIFFS.exists("/formatted")) {
    Serial.println("CM - File system not formatted");

    if(SPIFFS.format()) {
      Serial.println("CM - Format successful");

      File file = SPIFFS.open("/formatted", "w");
      file.print("y");
      file.flush();
      file.close();
    } else {
      Serial.println("CM - Format unsuccessful");
    }
  } else {
    Serial.println("CM - File already formatted");
  }
}

bool ConfigManager::itemExists(String key) {
    return SPIFFS.exists("/cm-" + key);
}

void ConfigManager::deleteItem(String key) {
  String filePath = "/cm-" + key;

  if(SPIFFS.exists(filePath)) {
    SPIFFS.remove(filePath);
  }
}

void ConfigManager::setString(String key, String value) {
  String filePath = "/cm-" + key;

  if(SPIFFS.exists(filePath)) {
    SPIFFS.remove(filePath);
  }

  File file = SPIFFS.open(filePath, "w");
  file.print(value);
  file.flush();
  file.close();
}

String ConfigManager::getString(String key) {
  String filePath = "/cm-" + key;

  if(!SPIFFS.exists(filePath)) {
    return "";
  }

  File file = SPIFFS.open(filePath, "r");

  String value;
  while(file.available()) {
    value += char(file.read());
  }

  file.close();

  return value;
}
