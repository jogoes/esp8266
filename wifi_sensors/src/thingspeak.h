#ifndef _THINGS_SPEAK_H_
#define _THINGS_SPEAK_H_

#include "properties.h"
#include <WString.h>
#include <vector>

class WiFiClient;

class ThingSpeak {

private:
  static const char* m_server;

private:
  bool m_initialized;
  bool m_enabled;

private:
  int m_channelId;
  String m_apiKey;

private:
  String printResponse(WiFiClient& wifiClient);

private:
  void init();

public:
  ThingSpeak();

public:
  bool isEnabled() { return m_enabled; }
  void enable() { m_enabled = true; }
  void disable() { m_enabled = false; }

  void updateFields(const std::vector<Property>& properties);
};

#endif
