#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include "properties.h"

#include "WString.h"
#include <vector>

class FileUtils {
public:
  static String readFile(const String& path);

  static String readFileByName(const String& name);
};

#endif
