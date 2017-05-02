#include "webserver.h"

#include "properties.h"

#include <ESP8266WebServer.h>

void
WebServer::configureWebServer(const std::vector<Property>& properties) {
	Serial.println("Configuring access point...");
  // TODO get this from configuration
  const char *ssidESP = "ESPServer";
  const char *passwordESP = "simpleandeasy";

  WiFi.mode(WIFI_AP_STA);
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssidESP/*, passwordESP*/);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  m_server.begin();
	Serial.println("HTTP server started");
}

void
WebServer::configureWiFiClient(const std::vector<Property>& properties) {
  Serial.println("configuring WiFi client...");
  String ssid = Properties::getValue("ssid", properties);
  String password = Properties::getValue("password", properties);
  Serial.println("ssid and password read.");
  Serial.println("'" + ssid + "'");
  Serial.println("'" + password + "'");
  Serial.println("connecting to WiFi...");
  WiFi.begin(ssid.c_str(), password.c_str());
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("local IP address: ");
  Serial.println(WiFi.localIP());
}

void
WebServer::start(const std::vector<Property>& properties) {
  configureWebServer(properties);
  //configureWiFiClient(properties);
}
