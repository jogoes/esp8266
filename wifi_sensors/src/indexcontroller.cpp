#include "indexcontroller.h"

#include "fileutils.h"
#include "template.h"
#include "webserver.h"
#include "networkutils.h"

#include <WString.h>
#include <map>

void
IndexController::onIndex() {
  String indexTemplate = FileUtils::readFile("/index.html");
  std::map<String, String> model;
  model["CONTENT"] = "";
  String response = Template::apply(indexTemplate, model);
  ok(response);
}

void IndexController::onScan() {
  int networksFound = NetworkUtils::scanNetwork();
  String response = String(networksFound) + " networks found";
  ok(response);
}
