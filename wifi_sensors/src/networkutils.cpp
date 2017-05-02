#include "networkutils.h"

#include <ESP8266WiFi.h>

int
NetworkUtils::scanNetwork() {
  Serial.println("scan start");

 // WiFi.scanNetworks will return the number of networks found
 int n = WiFi.scanNetworks();
 Serial.println("scan done");
 if (n == 0) {
   Serial.println("no networks found");
   return 0;
 } else {
   Serial.print(n);
   Serial.println(" networks found");
   for (int i = 0; i < n; ++i) {
     // Print SSID and RSSI for each network found
     Serial.print(i + 1);
     Serial.print(": ");
     Serial.print(WiFi.SSID(i));
     Serial.print(" (");
     Serial.print(WiFi.RSSI(i));
     Serial.print(")");
     Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
     delay(10);
   }
 }
 Serial.println("");
 return n;
}
