# Perfectly Smart Plants

Table of Contents

[toc]

## Connect ESP32 to Home Assisstant via MQTT

### Setup MQTT Broker

options to setup MQTT
- Self host e.g. via docker [eclipse-mosquitto](https://hub.docker.com/_/eclipse-mosquitto)
- public mqtt broker *(not recommended)* 

### Setup Arduino IDE

1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Connect ESP32 to your computer
3. In your Arduino IDE go to **File > Preferences**
4. Add the following URL to the "Additional Boards Manager URLs"

```link
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

5. Open the Boards Manager. Go to **Tools > Board > Boards Manager**
6. Search for **ESP32** and press install for **esp32** by **Espressif Systems**
7. Go to **Tools > Manage Libraries...**
8. Search for **PubSubClient** and press install for **PubSubClient** by **Nick O'Leary**
9. Select your Board in **Tools > Board** e.g. **ESP32 Dev Module**
10. Select the Port in **Tools > Port**
11. Open [ESP32 Mqtt implementation](esp32/test/mqtt/mqtt.ino) in Arduino
12. Fill out **LED_PIN**, **ssid**, **password**, **mqtt_server**, **mqtt_topic**, **mqtt_topic_get**, **mqtt_user**, **mqtt_password**, **mqtt_port**
13. Monitor via **Tools > Serial Monitor** if everything is working
14. Click Upload in Arduino IDE


### Setup MQTT for Home Assistant

1. Go to **Settings > Devices & Services** and click **ADD INTEGRATION**
2. Search for **MQTT** and add it
3. Click the new integration and then click **CONFIGURE** and then **RE-CONFIGURE MQTT**
4. Fill out **broker**, **port**, **username** and **password**
5. Add [HASS MQTT configuration](esp32/test/mqtt/configuration.yaml) to your Home Assistant configuration YAML and fill out **command_topic** and **state_topic**
6. Restart Home Assistant
7. On your dashboard, click the kebab button, then **Edit dashboard** and **ADD CARD**
8. Add **Entities Card** and add your MQTT Switch as Entity
