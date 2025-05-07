#include <Arduino.h>
#include "utils.h"
#include "Serial_protocol.h"
#include "WiFi_protocol.h"
#include "MQTT_protocol.h"

String data = "";

unsigned long lastPublishTime = 0;  
const long publishInterval = 1000;

void setup() {
  Serial.begin(115200);
  WiFiInitialization();
  BidirectionalInitialization();
  MQTTInitialization();
}

void loop() {
  String data = readBidirectionalMessage();
  if (data.length() > 0) {
    parseData(data);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - lastPublishTime >= publishInterval) {
    MQTTsend(pH, DO, temp);

    lastPublishTime = currentMillis;
  }

  client.loop();
}

