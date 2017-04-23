#ifndef _CONFIGURE_CONTROLLER_H_
#define _CONFIGURE_CONTROLLER_H_

#include "controller.h"

class ESP8266WebServer;

class ConfigureController : public Controller {

public:
  ConfigureController(ESP8266WebServer& server) : Controller(server) {
  }

public:
  void onConfigure();
};

#endif
