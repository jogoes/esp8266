#include "ledcontroller.h"

#include "fileutils.h"

#include <Arduino.h>

void
LedController::onLedOff() {
  digitalWrite(m_ledPin, LOW);
  String response = createResponse(0);
  ok(response);
}

void
LedController::onLedOn() {
  digitalWrite(m_ledPin, HIGH);
  String response = createResponse(1);
  ok(response);
}


String
LedController::createResponse(int val) {
  // If we're setting the LED, print out a message saying we did
  String status = "unknown";
  if (val >= 0)
  {
    status = (val)?"on":"off";
  }

  String content = FileUtils::readFileByName("led");
  content.replace("%LEDSTATUS%", status);

  String response = FileUtils::readFileByName("index");
  response.replace("%CONTENT%", content);
  return response;
}
