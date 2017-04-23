#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include "WString.h"
#include <vector>

class Property {
private:
  String m_name;
  String m_value;

public:
  Property(const String& name, const String& value) : m_name(name), m_value(value) {
  }
  Property(const Property& prop) {
    m_name = prop.m_name;
    m_value = prop.m_value;
  }

public:
  const String& getName() { return m_name; }
  const String& getValue() { return m_value; }
};

class FileUtils {
public:
  static String readFile(const String& path);

  static String readFileByName(const String& name);

  static void writeProperties(const String& path, std::vector<Property>& properties);

  static int readProperties(const String& path, std::vector<Property>& properties);
};

#endif
