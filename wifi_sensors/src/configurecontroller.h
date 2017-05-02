#ifndef _CONFIGURE_CONTROLLER_H_
#define _CONFIGURE_CONTROLLER_H_

#include "controller.h"

class WebServer;

class ConfigureController : public Controller {

public:
  ConfigureController(WebServer& server) : Controller(server) {
  }

public:
  void onConfigure();
  void onConfigureThingSpeak();

private:
  int writeProperties(const String& configName);
};

#endif
