Components Doku
===

How to connect a sensor to esp

Adding Components to our Project is easy. We have to add code parts to the yaml file of our esp.
In the espHome documentation we find all the important parts and how to's

# LED

[Doku](https://esphome.io/components/light/fastled.html)

I started with an led, to get a quick success or failure, and to get compfortable with connecting components to my esp

## Hardware
- Solder wires to the **input** side of the LED Strip. its the one with the arrow pointing down
- connect *+5V* to the pin saying *vcc*
- connect *gnd* to the pin saying *gnd*
- connect *din* to a io pin of your choice

## Software

see the [yaml file](./esp_LED.yaml) for a full version,
but the important part is this:

```
...
light:
  - platform: fastled_clockless
    chipset: WS2812B
    pin: GPIO16
    num_leds: 3
    name: "FastLED WS2812B Light"
...
```

just like sensors or other components you connect to the esp,
you just add this part to the yaml.

### Important Changes
- Check what **chipset** you use, while WS2812B is common, make sure its correct.
- Change the **pin** to the pin you use. you find it on the back of the board
- change **num_leds** to the amount of leds you use
- Change the **name** to one of your choice

### Possibilities
if you want, you can add **effects** to the file, to give it diffrent effects, not just a static light

# Sensor

Like with LED's, we start by adding a *sensor* section to the yaml file.

There are 2 Ways we can go, though we can't freely choose which one.
The first one is using a supported sensor. It's easy, but not everything is supported
The second one is a binary sensor, that just passes on the data provided and write our own code to decifer the data.

## Capacative Soil Moisture Sensor v1.2 (Binary Sensor)

### Software Setup
There is no prewritten setup for the soil sensor, even though there are a looot of tutorials. it might be that you might have to configure every sensor to its dry and wet point, but this is just a guess at this point.

im following this [tutorial](https://www.emadashi.com/2021/01/m5-atom-lite-home-assistant-esphome-and-capacitive-soil-sensor/) without implementing the deep sleep just yet, as we first want to figure out if our sensor implementation works.

- ! you cant use any pin: [what pins you can use](https://esphome.io/components/sensor/adc.html)
- set time to 500ms to test

### Tune your values
let the esp run some time in dry conditions. mark down the voltage of your sensor in dry condtion

mine was around 3.08V on average

now test it with sensor in water, be carful about the components
it decends slowly, so wait until its a stable value

mine was around 1.27V on average

i havent found the linear filter to wrook for me

! the attenuationm is very importens, else you wont get any values that change

you want to filter the values you got, so that everything above your dry base value is all 0%, and everything under your whet point, is 100% and everything in between is linear.

I dont know yet how to round the end value, but its not neccesary

see the [yaml file](./esp_soilmoisture.yaml) for reference

# Combining multiple Components

Before we combine multiple components its important to test all the diffrent components seperatly, *especially* if you've never used or worked with them bevore.
Direcly mergin multiple components makes debuggin much harder, very unneccesary.

## Hardware

The more, not difficult, but time consuming and annoying part is the pins. We often only have on **vcc** pin, though all components need one. We solve this by prototyping using a breadboard, where we can connect multiple sensor vcc pins to the one from the ESP32.

for every GPIO pin the components need, allocate one seperate connector row, then connect the ESP's PINS with those rows. We don't want to connect the components pins directly with the ESP, as it would make a giant chaos.

After that you can just write the seperate component yaml parts underneath each other and make sure to test them