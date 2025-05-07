#include <WiFi.h>
#include <PubSubClient.h>   

WiFiClient espClient;
PubSubClient client(espClient);

const char *mqtt_broker = "broker.emqx.io";
const char *topic = "mqtt";
const int mqtt_port = 1883;


void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
}

void MQTTInitialization(){
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str())) {
            Serial.println("Public EMQX MQTT broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }

}

void MQTTsend(float pH, float DO, float temp) {
    client.publish("bakfiber/sensor/ph", String(pH, 2).c_str());
    client.publish("bakfiber/sensor/do", String(DO, 2).c_str());
    client.publish("bakfiber/sensor/tp", String(temp, 2).c_str());
}

void MQTTSubscribe(){
    client.subscribe("bakfiber/control");
}
