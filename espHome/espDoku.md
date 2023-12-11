ESP32 in Home Assistent
===

# Setup

## SSL

[Tutorial ](https://scotthelme.co.uk/setting-up-https-for-home-assistant/) used

decided to skip this

## ESPHome Dashboard

1. Install as HA add-on
    1. **Settings** > **Add-ons** > **Add-on Store**
    2. Search for *ESPHome*
    3. Install
    4. Set *Show in sidebar* to on
    5. *Start*
    6. *Open Web UI*
2. Edit secrets.yaml
    1. in right upper corner click on secrets
    2. enter your wifi ssid
        - the name of your wifi
        - find it under *settings* > *wifi* > *settings for the wifi you want to choose*
        - ssid can be found under *identity*
        - password under *security*
        - this is for ubuntu 
    - we do this so that the esp knows the network

## Way's to add an esp
### USB Cable connection to User Computer
1. Select *+ New Device*
2. Connect ESP to computer via cable
3. Find out Device Type and choose it
    - ESP32
    - ESP32-S2
    - ESP32-S3
    - ESP32-C3
    - ESP8266
    - Raspberry Pi Pico W
4. Install Config to device
    1. Choose ESPHome Web choice (chrome needed)
    2. Wait for for download to be blue, then click on it to download
    - ! issues: if "Failed to execute 'open' on 'SerialPort': Failed to open serial port." issue: look below
    3. choose right device (a name should apear that makes sense)
    4. choose downloaded firmware
    5. install
5. Find new device
    1. Go Back to HA > ESPHome
    2. Upper Right Corner > *Update All*
    3. Check that no errors

### USB Cable connection to server
1. Select *+ New Device*
2. Connect ESP to server computer via cable
3. Find out Device Type and choose it
    - ESP32
    - ESP32-S2
    - ESP32-S3
    - ESP32-C3
    - ESP8266
    - Raspberry Pi Pico W
4. Install Config to device
    1. Choose to install via cable to server way
    2. choose right device (a name should apear that makes sense)
    3. wait (might take some time)

## Include ESP into Home Assistant;
At last, we need to add the esp into home assistant, as esphome is freestanding and just visually sitting on our HA dashboard.

*Settings* > *Devices & services* > *your device* should appear somewhere there, click *configure*


## issues that can arise

### *"Failed to execute 'open' on 'SerialPort': Failed to open serial port."*

check with
>groups
if *dialout* is a group I (<username>/$USER) am in

the bowser cant access ttyUSB device. you need to add $USER to ttyusb usergroup called *"dialout"*.

>usermod -a -G dialout $USER

check again for dialout group

### *"Error resolving IP address of <devicename>.local. Is it connected to WiFi?"*

some network magic was setup wrong.

- ping <devicename>.local
- write ip into yaml file in following way:


