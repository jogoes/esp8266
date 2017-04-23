#include "configurecontroller.h"

#include "properties.h"

#include <ESP8266WebServer.h>

#include "WString.h"

#include <vector>

void
ConfigureController::onConfigure() {
  std::vector<Property> props;
  for(int i = 0; i < m_server.args(); i++) {
    String name = m_server.argName(i);
    String value = m_server.arg(i);
    props.push_back(Property(name, value));
  }

  Properties::write("/config.properties", props);
  ok("Configuration successful, " + String(props.size()) + " properties have been added.");
}
