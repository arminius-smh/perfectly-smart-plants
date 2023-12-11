# Home Assistant

[Tutorial](https://www.home-assistant.io/installation/linux#docker-compose)

## Prep
if neccesary install docker

## main Part

1. make docker home assistant folder
2. create "compose.yml" with following content

```
version: '3'
services:
  homeassistant:
    container_name: homeassistant
    image: "ghcr.io/home-assistant/home-assistant:stable"
    volumes:
      - /PATH_TO_YOUR_CONFIG:/config
      - /etc/localtime:/etc/localtime:ro
      - /run/dbus:/run/dbus:ro
    restart: unless-stopped
    privileged: true
    network_mode: host
    devices:
      - /dev/ttyUSB0:/dev/ttyUSB0
```

3. start docker

> docker compose up -d

you find it under "localhost:8123"

# ESPHome

Same as above, but we can just extend the *compose.yml* with the following:

```
version '3'
services:
    ...
    esphome:
        container_name: esphome
        image: ghcr.io/esphome/esphome
        volumes:
        - ./esp-home/config:/config
        - /etc/localtime:/etc/localtime:ro
        restart: always
        privileged: true
        network_mode: host
    ...
```

and again:

> docker compose up -d

you find it under "0.0.0.0:6052

careful, this is exposed to the network now
consider setting a **password**
[souce](https://esphome.io/guides/getting_started_command_line.html)


```
version '3'
services:
    ...
    esphome:
        ...
        enviroment:
            - USERNAME=test
            - PASSWORD=ChangeMe
        ...
    ...
```
