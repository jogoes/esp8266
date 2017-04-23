#include "fileutils.h"

#include "FS.h"

String
FileUtils::readFile(const String& path) {
  File f = SPIFFS.open(path, "r");
  if(!f) {
    Serial.println("opening file '" + path + "' failed.");
    return "";
  } else {
    return f.readString();
  }
}

String
FileUtils::readFileByName(const String& name) {
  return readFile("/" + name + ".html");
}

void
FileUtils::writeProperties(const String& path, std::vector<Property>& properties) {
  File f = SPIFFS.open(path, "w+");
  if(!f) {
    Serial.println("opening file '" + path + "' failed.");
    return;
  }

  String config = "";
  for(auto i = properties.begin(); i != properties.end(); i++) {
    config += (*i).getName() + "=" + (*i).getValue();
    config += "\n";
  }

  f.write((const uint8_t*) config.c_str(), config.length());
  f.close();
}

int
FileUtils::readProperties(const String& path, std::vector<Property>& properties) {
  File f = SPIFFS.open(path, "r");
  if(!f) {
    Serial.println("opening file '" + path + "' failed.");
    return 0;
  }

  String propertiesStr = f.readString();
  int current = 0;
  int next = 0;
  int count = 0;
  while(next >= 0) {
    next = propertiesStr.indexOf('\n', current);
    if(next >= 0) {
      String propValue = propertiesStr.substring(current, next);
      int idx = propValue.indexOf('=');
      if(idx >= 0) {
        String name = propValue.substring(0, idx);
        String value = propValue.substring(idx);
        Property prop(name, value);
        properties.push_back(prop);
        count++;
      }
    }
    current = next + 1;
  }
  f.close();
  return count;
}
