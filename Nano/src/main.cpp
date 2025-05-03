#include <Arduino.h>
#include "parameter.h"
#include "utils.h"
#include "Serial_protocol.h"
#include "temperature.h"
#include "DO.h"
#include "pH.h"
// #include "lcd.h"

void setup() {
  Serial.begin(115200);
  BidirectionalInitialization();

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
  // showDisplay(randomFloat(), randomFloat(), randomFloat());

}

