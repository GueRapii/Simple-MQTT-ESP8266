# Simple MQTT ESP8266

This project demonstrates MQTT communication between two ESP8266 boards. One board acts as a **Receiver**, turning an LED ON or OFF based on MQTT messages. The other acts as a **Sender**, publishing messages when a button is pressed or released.

## 🧰 Hardware Required

- 2x ESP8266 boards (NodeMCU, Wemos D1 Mini, etc.)
- 1x Push Button (for the sender)
- 1x LED with resistor (for the receiver)
- Jumper wires and breadboard
- MQTT Broker (e.g., Mosquitto or cloud-based MQTT service)

---

## 📁 Project Structure

- `Receiver.ino` – Controls an LED based on MQTT messages received on topic `home/led`
- `Sender.ino` – Sends MQTT messages when a button is pressed or released

---

## ⚙️ Configuration

Update the following in both `.ino` files to match your network and broker settings:

```cpp
const char* ssid = "Your_Wifi";             // Replace with your WiFi SSID
const char* password = "Pass_Wifi";         // Replace with your WiFi password
const char* mqttServer = "ip_mqtt_server";  // IP address of your MQTT broker
const int mqttPort = change_me_port_mqtt;      // Typically 1883
```

**Pinout:**
- LED should be connected to **GPIO4 (D2)** on the receiver
- Button should be connected to **GPIO5 (D1)** on the sender

---

## 🚀 How to Use

### 1. Set Up MQTT Broker

If you don't have a broker yet, you can install Mosquitto on a Linux machine:

```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients
```

Ensure the broker is running and accessible from both ESP8266 boards.

### 2. Upload Code

- Upload `Receiver.ino` to the receiver ESP8266 board
- Upload `Sender.ino` to the sender ESP8266 board

### 3. Test the Setup

- Power both boards
- When the button is pressed on the sender, it sends `"ON"` to the topic `home/led`
- When released, it sends `"OFF"`
- The receiver listens to the topic and turns the LED ON or OFF accordingly

---

## 🛰️ Communication Flow

```
[Sender] Button Pressed → MQTT → Topic "home/led" → [Receiver] LED ON  
[Sender] Button Released → MQTT → Topic "home/led" → [Receiver] LED OFF
```

---

## 📚 Libraries Used

- [`ESP8266WiFi`](https://arduino-esp8266.readthedocs.io/)
- [`PubSubClient`](https://pubsubclient.knolleary.net/)

Install them via the Arduino IDE Library Manager if you haven’t already.

---

## 🧪 Optional MQTT Testing (PC/Terminal)

You can also test using the command line:

```bash
# Send ON command
mosquitto_pub -h <ip_mqtt_server> -t home/led -m "ON"

# Listen to topic
mosquitto_sub -h <ip_mqtt_server> -t home/led
```

---

## 💡 Future Ideas

- Add more commands like "BLINK"
- Use a sensor instead of a button
- Display LED status on an OLED screen

---

Made with ❤️ by [@GueRapii](https://github.com/GueRapii)
---

## 📝 License

This project is licensed under the [MIT License](LICENSE).  
You are free to use, modify, and distribute this software with proper attribution.

