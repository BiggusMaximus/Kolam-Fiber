#include "HardwareSerial.h"
HardwareSerial espSerial(1); // Use UART1

void BidirectionalInitialization(){
    espSerial.begin(9600, SERIAL_8N1, 16, 17);
}

String readBidirectionalMessage(){
    String msg = "";
    if (espSerial.available()) {
        msg = espSerial.readStringUntil('\n');
        Serial.println(msg);
    }
    return msg;
}