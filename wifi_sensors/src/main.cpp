#include "ledcontroller.h"
#include "dhtcontroller.h"

#include "fileutils.h"

#include <ESP8266WiFi.h>

#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "FS.h"
#include "DHT.h"

/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = 14; // Thing's onboard, green LED
const int ANALOG_PIN = A0; // The only analog pin on the Thing
const int DIGITAL_PIN = 12; // Digital pin to be read

ESP8266WebServer server(80);

LedController ledController(server, LED_PIN);

#define DHTTYPE DHT11
const int DHTPIN = 13;
DHT dht(DHTPIN, DHTTYPE);

DhtController dhtController(server, dht);

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
  String response = FileUtils::readFile("/index.html");
  response.replace("%CONTENT%", "");
  server.send(200, "text/html", response);
}

void configureHandlers() {
  server.on("/", handleIndex);
	server.on("/led/0", handleLed0);
  server.on("/led/1", handleLed1);
  server.on("/read", handleRead);
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
