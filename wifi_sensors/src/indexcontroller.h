#ifndef _INDEX_CONTROLLER_H
#define _INDEX_CONTROLLER_H

#include "controller.h"

class IndexController : public Controller {

public:
  IndexController(WebServer& server) : Controller(server) {}

public:
  void onIndex();
  void onScan();
};

#endif
