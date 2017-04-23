#include "ledcontroller.h"
#include "dhtcontroller.h"
#include "configurecontroller.h"

#include "fileutils.h"
#include "properties.h"
#include "template.h"

#include <map>

#include <ESP8266WiFi.h>

#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "FS.h"
#include "DHT.h"

const int LED_PIN = 14;

ESP8266WebServer server(80);

LedController ledController(server, LED_PIN);

#define DHTTYPE DHT11
const int DHTPIN = 13;
DHT dht(DHTPIN, DHTTYPE);

DhtController dhtController(server, dht);

ConfigureController configureController(server);

const char *ssid = "ESPServer";
const char *password = "simpleandeasy";

String createResponse(int val);

void handleLed0() {
  ledController.onLedOff();
}

void handleLed1() {
  ledController.onLedOn();
}

void handleRead() {
  dhtController.onValues();
}

void handleIndex() {
  String indexTemplate = FileUtils::readFile("/index.html");
  std::map<String, String> model;
  model["CONTENT"] = "";
  String response = Template::apply(indexTemplate, model);
  server.send(200, "text/html", response);
}

void handleConfigure() {
  configureController.onConfigure();
}

void configureHandlers() {
  server.on("/", handleIndex);
  server.on("/led/0", handleLed0);
  server.on("/led/1", handleLed1);
  server.on("/read", handleRead);
  server.on("/configure", handleConfigure);
}

void setup() {
  pinMode(LED_PIN, OUTPUT);

	delay(1000);
	Serial.begin(115200);

  Serial.println("files found:");
  SPIFFS.begin();
  Dir dir = SPIFFS.openDir("/");
  while(dir.next()) {
    Serial.println(dir.fileName());
  }

  std::vector<Property> properties;
  int result = Properties::read("/config.properties", properties);
  Serial.print("properties read: ");
  Serial.println(result);

  Serial.println("initializing DHT...");
  dht.begin();
  Serial.println("done.");

	Serial.println();
	Serial.println("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid/*, password*/);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
  configureHandlers();
	server.begin();
	Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
