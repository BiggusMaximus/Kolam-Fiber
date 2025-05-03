#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(6, 7); // RX, TX

void BidirectionalInitialization(){
    Serial1.begin(9600);
}

String readBidirectionalMessage(){
    String msg = "";
    if (Serial1.available()) {
        msg = Serial1.readStringUntil('\n');
        Serial.println("From Nano: " + msg);
    }
    return msg;
}
