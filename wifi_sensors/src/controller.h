#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

class ESP8266WebServer;
class String;

class Controller {

protected:
  ESP8266WebServer& m_server;

public:
  Controller(ESP8266WebServer& server) : m_server(server) {

  }

public:
  void ok(const String& response);

  String readIndex();
  String readFile(const String& path);
  String readFileByName(const String& name);
};

#endif
