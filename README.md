# Perfectly Smart Plants

Monitor your plant health in home assistant using moisture, temperature, humidity and illuminance sensors. Using either PlatformIO or EspHome.

This project has two different implementations!
./platformio is a project written in C++, while ./espHome is a project using Esphome - so it mostly contains config files.

## Requirements

- ESP32
- Capacitive Moisture Sensor
- Temperature Sensor
- Humidity Sensor
- Illuminance Sensor
- Hardware to run a Home Assistant Server and the MQTT Broker

## Getting started
This will get you started quickly! 
1) Connect the ESP32 to the sensors
2) Decide which implementation you want to use and go into that directory and run ```docker-compose up -d```
3) In Home Assistant install [Home Assistant Plant Card](https://github.com/Olen/homeassistant-plant)
4) head over to the implementation directory you want to use and follow the rest of the steps there

### PlatformIO

See [README.md](platformio/README.md)

### EspHome

See [EspHome Wiki](espHome/README.md)
