#include "ledcontroller.h"

#include "fileutils.h"
#include "template.h"

#include <Arduino.h>

#include <map>

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
  String status = "unknown";
  if (val >= 0)
  {
    status = (val)?"on":"off";
  }

  String ledTemplate = FileUtils::readFileByName("led");
  std::map<String, String> ledModel;
  ledModel["LEDSTATUS"] = status;
  String ledContent = Template::apply(ledTemplate, ledModel);

  String indexTemplate = FileUtils::readFileByName("index");
  std::map<String, String> contentModel;
  contentModel["CONTENT"] = ledContent;
  return Template::apply(indexTemplate, contentModel);
}
