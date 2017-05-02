#ifndef _DHT_CONTROLLER_H_
#define _DHT_CONTROLLER_H_

#include "controller.h"

class DHT;
class WebServer;

class DhtController : public Controller {

private:
  DHT& m_dht;

public:
  DhtController(WebServer& server, DHT& dht);

public:
  void onValues();

};

#endif
