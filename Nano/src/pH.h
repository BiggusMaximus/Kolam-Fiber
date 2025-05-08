#include <Arduino.h>
#define PH_PIN A0

float m_pH = -0.0257;
float b_pH = 25.331;

void PHInitialization(){
  pinMode(PH_PIN, INPUT);
}

float readAnalog(){
  return analogRead(PH_PIN);
}

float readAverageAnalogPH(){
  float temp = 0;
  for (size_t i = 0; i < N_SAMPLES; i++)
  {
    temp += analogRead(PH_PIN);
  }
  return temp/N_SAMPLES;
}

float readCalibratedPH(){
  return m_pH * analogRead(PH_PIN) + b_pH;
}

float readAverageCalibratedPH(){
  float temp = 0;
  for (size_t i = 0; i < N_SAMPLES; i++)
  {
    temp += readCalibratedPH();
  }
  return temp/N_SAMPLES;

}