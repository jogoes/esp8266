#include "thingspeak.h"

#include "utils/properties.h"

#include <ESP8266WiFi.h>

const char* ThingSpeak::m_server = "api.thingspeak.com";

ThingSpeak::ThingSpeak() : m_initialized(false), m_enabled(false) {
}

void
ThingSpeak::init() {
  if(m_initialized) {
    return;
  }

  std::vector<Property> properties;
  int propertiesRead = Properties::read("/thingspeak.properties", properties);

  for(auto property = properties.begin(); property != properties.end(); property++) {
    if(property->getName() == "api_key") {
      m_apiKey = property->getValue();
    }
    if(property->getName() == "channel_id") {
      m_channelId = property->getValue().toInt();
    }
  }
  m_initialized = true;
}

String
ThingSpeak::printResponse(WiFiClient& wifiClient) {
  int i = 0;
  while((!wifiClient.available()) && (i<100)){
    delay(10);
    i++;
  }
  while(wifiClient.available()) {
    String line = wifiClient.readStringUntil('\r');
    Serial.print(line);
  }
}

void
ThingSpeak::updateFields(const std::vector<Property>& properties) {

  init();

  if(!m_enabled) {
    return;
  }

  WiFiClient wifiClient;
  Serial.print("connecting to ThingSpeak on ");
  Serial.println(m_server);
  if(!wifiClient.connect(m_server, 80)) {
    Serial.println("Failed to connect to server");
    return;
  }

  String body;
  body = String("X-THINGSPEAKAPIKEY") + "=" + m_apiKey;
  for(auto property = properties.begin(); property != properties.end(); property++) {
    body += "&" + property->getName() + "=" + property->getValue();
  }
  //Serial.println("sending body: " + body);

  Serial.println("posting update...");
  wifiClient.print("POST /update HTTP/1.1\n");
  wifiClient.print("Host: api.thingspeak.com\n");
  wifiClient.print("Connection: close\n");
  wifiClient.print("X-THINGSPEAKAPIKEY: " + m_apiKey + "\n");
  wifiClient.print("Content-Type: application/x-www-form-urlencoded\n");
  wifiClient.print("Content-Length: ");
  wifiClient.print(body.length());
  wifiClient.print("\n\n");
  wifiClient.print(body);
  wifiClient.print("\n\n");

  //printResponse(wifiClient);

  wifiClient.stop();
  Serial.println("update done.");
}
