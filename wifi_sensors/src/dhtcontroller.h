#ifndef _DHT_CONTROLLER_H_
#define _DHT_CONTROLLER_H_

#include "controller.h"

class DHT;
class ESP8266WebServer;

class DhtController : public Controller {

private:
  DHT& m_dht;

public:
  DhtController(ESP8266WebServer& server, DHT& dht) : Controller(server), m_dht(dht) {

  }

public:
  void onValues();

};

#endif
