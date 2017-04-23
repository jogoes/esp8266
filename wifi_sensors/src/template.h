#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#include <map>

class Template {

public:
  static String apply(const String& content, std::map<String, String> replacements) {
    String c(content);

    for(auto it = replacements.begin(); it != replacements.end(); it++) {
      auto key = it->first;
      auto value = it->second;
      c.replace("%" + key + "%", value);
    }
    return c;
  }
};

#endif
