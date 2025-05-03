#include <Arduino.h>
#include "utils.h"
#include "Serial_protocol.h"
#include "WiFi_protocol.h"
#include "MQTT_protocol.h"

String data = "";

void setup() {
  Serial.begin(115200);
  WiFiInitialization();
  BidirectionalInitialization();
  MQTTInitialization();
}

void loop() {
  String data = readBidirectionalMessage();
  parseData(data);

}

