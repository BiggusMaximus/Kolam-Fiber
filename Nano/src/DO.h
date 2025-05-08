#include <Arduino.h>
#define DO_PIN A6


float m_DO = 0.0118;
float b_DO = 2.4185;

void DOInitialization(){
  pinMode(DO_PIN, INPUT);
}

float readAnalogDO(){
  return analogRead(DO_PIN);
}

float readAverageAnalogDO(){
  float temp = 0;
  for (size_t i = 0; i < N_SAMPLES; i++)
  {
    temp += analogRead(DO_PIN);
  }
  return temp/N_SAMPLES;
}

float readCalibratedDO(){
  return m_DO * analogRead(DO_PIN) + b_DO;
}

float readAverageCalibratedDO(){
  float temp = 0;
  for (size_t i = 0; i < N_SAMPLES; i++)
  {
    temp += readCalibratedDO();
  }
  return temp/N_SAMPLES;

}