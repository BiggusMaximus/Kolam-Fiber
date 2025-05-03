#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is conntec to the Arduino digital pin 4
#define ONE_WIRE_BUS 4

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void TemperatureSensorInitialization(){
    sensors.begin();
}

float readTemperature(){
    return sensors.requestTemperatures(); 
}

float readMeanTemperature(){
    float temp = 0;
    for (size_t i = 0; i < N_SAMPLES; i++)
    {
        temp += sensors.requestTemperatures(); 
    }
    
    return temp/100;
}