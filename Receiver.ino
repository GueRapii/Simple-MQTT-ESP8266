#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Your_Wifi";       
const char* password = "Pass_Wifi";  
const char* mqttServer = "ip_mqtt_server";  
const int mqttPort = port_mqqt_server;  

#define LED_PIN 4  

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println(message);

    if (message == "ON") {
        digitalWrite(LED_PIN, HIGH);
    } else if (message == "OFF") {
        digitalWrite(LED_PIN, LOW);
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect("ESP8266-LED")) {
            Serial.println("Connected!");
            client.subscribe("home/led");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 5 seconds");
            delay(5000);
        }
    }
}

void loop() {
    client.loop();
}
