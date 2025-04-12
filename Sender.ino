#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Your_Wifi";       
const char* password = "Pass_Wifi";  
const char* mqttServer = "ip_mqtt_server";  
const int mqttPort = port_mqqt_server;   

#define BUTTON_PIN 5  

WiFiClient espClient;
PubSubClient client(espClient);

bool lastButtonState = HIGH;

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP); 

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    client.setServer(mqttServer, mqttPort);

    while (!client.connected()) {
        Serial.print("Connecting to MQTT...");
        if (client.connect("ESP8266-Button")) {
            Serial.println("Connected!");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" trying again in 5 seconds");
            delay(5000);
        }
    }
}

void loop() {
    bool buttonState = digitalRead(BUTTON_PIN);

    if (buttonState != lastButtonState) {  
        lastButtonState = buttonState;
        
        if (buttonState == LOW) {  
            Serial.println("Button Pressed, sending ON...");
            client.publish("home/led", "ON");
        } else {  
            Serial.println("Button Released, sending OFF...");
            client.publish("home/led", "OFF");
        }

        delay(50);
    }

    client.loop();
}
