#include "configmanager.h"

ConfigManager::ConfigManager() {
  // Init SPIFFS
  SPIFFS.begin();

  // Check if FS is formatted
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
  // Construct file path
  String filePath = "/cm-" + key;

  //Delete if exists
  if(SPIFFS.exists(filePath)) {
    SPIFFS.remove(filePath);
  }
}

void ConfigManager::setString(String key, String value) {
  // Construct file path
  String filePath = "/cm-" + key;

  // Remove existing config
  if(SPIFFS.exists(filePath)) {
    SPIFFS.remove(filePath);
  }

  // Open/create the file and write contents
  File file = SPIFFS.open(filePath, "w");
  file.print(value);
  file.flush();
  file.close();
}

String ConfigManager::getString(String key) {
  // Construct file path
  String filePath = "/cm-" + key;

  // Check file exists
  if(!SPIFFS.exists(filePath)) {
    return "";
  }

  // Open file for reading
  File file = SPIFFS.open(filePath, "r");

  //Read contents into string
  String value;
  while(file.available()) {
    value += char(file.read());
  }

  file.close();

  return value;
}
