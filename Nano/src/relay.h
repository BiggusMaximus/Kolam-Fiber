#define RELAY_PIN 2

void RelayInitialization(){
    pinMode(RELAY_PIN, OUTPUT);
}

void TurnOnRelay(){
    digitalWrite(RELAY_PIN, HIGH);
}

void TurnOffRelay(){
    digitalWrite(RELAY_PIN, LOW);
}