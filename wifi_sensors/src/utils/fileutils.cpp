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
