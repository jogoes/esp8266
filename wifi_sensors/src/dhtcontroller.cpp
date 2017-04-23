#include "dhtcontroller.h"

#include "DHT.h"
#include "fileutils.h"
#include "template.h"

#include <map>

void
DhtController::onValues() {

  float h = m_dht.readHumidity();
  float t = m_dht.readTemperature();

  String temperature;
  String humidity;
  if(isnan(h) || isnan(t)) {
    temperature = "Failed to read temperature from sensor.";
    humidity = "Failed to read humidity from sensor.";
  } else {
    temperature = String(t,0);
    humidity = String(h,0);
  }

  std::map<String, String> sensorsModel;
  sensorsModel["DHTTEMPERATURE"] = temperature;
  sensorsModel["DHTHUMIDITY"] = humidity;
  String dhtTemplate = FileUtils::readFileByName("dht");
  String dhtContent = Template::apply(dhtTemplate, sensorsModel);

  String indexTemplate = FileUtils::readFileByName("index");

  std::map<String, String> model;
  model["CONTENT"] = dhtContent;
  String response = Template::apply(indexTemplate, model);

  ok(response);
}
