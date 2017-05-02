#include "ledcontroller.h"
#include "dhtcontroller.h"
#include "configurecontroller.h"
#include "indexcontroller.h"

#include "fileutils.h"
#include "properties.h"
#include "template.h"

#include <map>

#include "DHT.h"
#include "thingspeak.h"
#include "FS.h"
#include "webserver.h"

#include "ESP8266WebServer.h"

const int LED_PIN = 14;

DHT dht(13, DHT11);

ESP8266WebServer espServer(80);

WebServer server(espServer);

LedController ledController(server, LED_PIN);

DhtController dhtController(server, dht);

ConfigureController configureController(server);

IndexController indexController(server);

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
  indexController.onIndex();
}

void handleScanNetwork() {
  indexController.onScan();
}

void handleConfigure() {
  configureController.onConfigure();
}

void handleConfigureThingSpeak() {
  configureController.onConfigureThingSpeak();
}

void configureHandlers() {
  ESP8266WebServer& espServer = server.getServer();

  espServer.on("/", handleIndex);
  espServer.on("/scan", handleScanNetwork);
  espServer.on("/led/0", handleLed0);
  espServer.on("/led/1", handleLed1);
  espServer.on("/read", handleRead);
  espServer.on("/configure", handleConfigure);
  espServer.on("/configurethingspeak", handleConfigureThingSpeak);
}

ThingSpeak thingSpeak;

unsigned long lastUpdate = millis();

void setup() {
  delay(1000);
	Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  Serial.println("initializing DHT...");
  dht.begin();
  Serial.println("done.");

  Serial.println("checking filesystem...");
  SPIFFS.begin();
  Serial.println("files found:");
  Dir dir = SPIFFS.openDir("/");
  while(dir.next()) {
    Serial.println(dir.fileName());
  }
  Serial.println("done.");

  Serial.println("reading config.properties...");
  std::vector<Property> properties;
  int result = Properties::read("/config.properties", properties);
  Serial.print("properties read: ");
  Serial.println(result);
  Serial.println("done.");

  configureHandlers();
  server.start(properties);

  // for now don't send data to ThingSpeak
  thingSpeak.disable();
}

void loop()
{
  server.getServer().handleClient();

  if(thingSpeak.isEnabled()) {
    unsigned long current = millis();
    if(current - lastUpdate > 10000) {
      lastUpdate = current;
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      std::vector<Property> fields;
      String temperature = String(t,0);
      String humidity = String(h,0);
      fields.push_back(Property("field2", humidity));
      fields.push_back(Property("field1", temperature));
      thingSpeak.updateFields(fields);
    }
  }
}
