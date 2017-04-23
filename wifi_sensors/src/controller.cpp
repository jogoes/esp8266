
#include "controller.h"
#include "fileutils.h"

#include <ESP8266WebServer.h>

void
Controller::ok(const String& response)
{
  m_server.send(200, "text/html", response);
}

String
Controller::readIndex() {
  return FileUtils::readFile("/index.html");
}
