
#include "controller.h"
#include "utils/fileutils.h"

#include <webserver.h>

#include "ESP8266WebServer.h"

void
Controller::ok(const String& response)
{
  m_server.getServer().send(200, "text/html", response);
}

String
Controller::readIndex() {
  return FileUtils::readFile("/index.html");
}
