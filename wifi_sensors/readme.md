## WiFi enabled querying sensors on the NodeMCU

This project demonstrates using a NodeMCU devkit as an access point for querying sensors and controlling a connected LED.

The [Platform IO](http://platformio.org/) development environment in combination with the [Arduino Core](https://github.com/esp8266/Arduino) 
was used for implementation.

See below for how to connect the NodeMCU devkit:

|NodeMCU|DHT11|LED|
|---|---|---|
|3.3V|VCC   |   |
|GND|GND|   |
|D7|Data|   |
|D5|   |Kathode   |
|GND| |Anode via Resistor|

For running the NodeMCU devkit standalone connect Vin to 5V and GND to GND of an external power source.

### TODO
* the current implementation doesn't connect to a WiFi, this is required to send the sensor data to somewhere else 
* in order to get the device working in other WiFis there must be a way to configure SSID and password.
Currently, the implementations spans its own access point through which by connecting via HTTP it's already possible to 
set configuration parameters. But this is currently not used for anything else.
* collect sensor data and send to an IoT platform (e.g. ThingSpeak)
