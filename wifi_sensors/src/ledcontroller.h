#ifndef _LED_CONTROLLER_H
#define _LED_CONTROLLER_H

#include "controller.h"

#include "WString.h"

class ESP8266WebServer;

class LedController : public Controller {

private:
  int m_ledPin;

  public:
     LedController(ESP8266WebServer& server, int ledPin) : Controller(server), m_ledPin(ledPin) {
     }

  public:
    void onLedOff();
    void onLedOn();
  private:
    String createResponse(int val);
};

#endif
