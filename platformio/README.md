# Perfectly Smart Plants

Table of Contents

[toc]

## Setup

### MQTT Broker

options to setup MQTT

- Self host e.g. via docker [eclipse-mosquitto](https://hub.docker.com/_/eclipse-mosquitto)
- public mqtt broker *(not recommended)*

### PlatformIO

- cli: install [pio](https://docs.platformio.org/en/stable/core/installation/index.html)
- vscode: [vscode](https://platformio.org/platformio-ide)

#### cmds

```bash
# not needed for vscode extension
pio project init --ide <ide> # see https://docs.platformio.org/en/stable/integration/ide/index.html#desktop-ides

# build & upload perfectly smart plants
pio run -e psp -t upload

# build & upload functionality tests
pio run -e led -t upload
pio run -e wifi -t upload
pio run -e mqtt -t upload
pio run -e moisture -t upload
pio run -e lux -t upload
pio run -e hum-temp-pressure -t upload

# serial monitor
pio device monitor
```
