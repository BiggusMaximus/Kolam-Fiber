#include <Arduino.h>
#include "parameter.h"
#include "utils.h"
#include "Serial_protocol.h"
#include "temperature.h"
#include "DO.h"
#include "pH.h"
#include "relay.h"
// #include "lcd.h"

void setup() {
  Serial.begin(115200);
  BidirectionalInitialization();
  RelayInitialization();
  TemperatureSensorInitialization();
  PHInitialization();
  DOInitialization();
  // LCDInitialization();

}

void loop() {
  temp = readTemperature();
  DO = readAverageCalibratedDO();
  pH = readAverageCalibratedPH();
  data = DataPreprocessing(pH, DO, temp);

  Serial1.println(data);
  // Serial.println(data);

  // TurnOnRelay();
  // delay(1000);
  // Serial.println("turn off");
  // TurnOffRelay();
  // delay(1000);
  // showDisplay(randomFloat(), randomFloat(), randomFloat());

}

