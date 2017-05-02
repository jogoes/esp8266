#include "configurecontroller.h"

#include "properties.h"

#include <webserver.h>

#include "WString.h"

#include <vector>

#include "ESP8266WebServer.h"


int
ConfigureController::writeProperties(const String& configName) {
  std::vector<Property> props;
  ESP8266WebServer& server = m_server.getServer();

  for(int i = 0; i < server.args(); i++) {
    String name = server.argName(i);
    String value = server.arg(i);
    props.push_back(Property(name, value));
  }

  Properties::write(String("/") + configName + ".properties", props);
  return props.size();
}

void
ConfigureController::onConfigure() {
  int propsWritten = writeProperties("config");
  ok("Configuration successful, " + String(propsWritten) + " properties have been added.");
}

void
ConfigureController::onConfigureThingSpeak() {
  int propsWritten = writeProperties("thingspeak");
  ok("ThingSpeak configuration successful, " + String(propsWritten) + " properties have been added.");
}
