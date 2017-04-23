#include "configurecontroller.h"

#include <Arduino.h>
#include "fileutils.h"

#include <ESP8266WebServer.h>

#include "WString.h"

#include <vector>

void
ConfigureController::onConfigure() {
  String ssid = m_server.arg("ssid");
  String password = m_server.arg("password");

  std::vector<Property> props;
  props.push_back(Property("ssid", ssid));
  props.push_back(Property("password", password));

  FileUtils::writeProperties("/config.properties", props);
  ok("configuration successful.");
}
