#ifndef _FILE_UTILS_H_
#define _FILE_UTILS_H_

#include "WString.h"

class FileUtils {
public:
  static String readFile(const String& path);

  static String readFileByName(const String& name);
};

#endif
