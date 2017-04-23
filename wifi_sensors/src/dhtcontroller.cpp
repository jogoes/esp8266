#include "dhtcontroller.h"

#include "DHT.h"
#include "fileutils.h"

void
DhtController::onValues() {

  String content = FileUtils::readFileByName("dht");

  float h = m_dht.readHumidity();
  float t = m_dht.readTemperature();
  if(isnan(h)|| isnan(t)) {
    content.replace("%DHTTEMPERATURE%", "Failed to read temperature from sensor.");
    content.replace("%DHTHUMIDITY%", "Failed to read humidity from sensor.");
  } else {
    content.replace("%DHTTEMPERATURE%", String(t, 0));
    content.replace("%DHTHUMIDITY%", String(h, 0));
  }
  
  String response = FileUtils::readFileByName("index");
  response.replace("%CONTENT%", content);
  ok(response);
}
