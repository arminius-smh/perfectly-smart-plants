Creating and Managing Automations
===

# General Setup

*Settings* > *Automations & scenes* > (*Automations*) > *+ Create Automation* > *Create new automation*

Automation has 3 main Parts
**Triggers**
What should happen to trigger the automation

**Conditions**
optional

can prevent actions to start after trigger happens
Muss oder muss nicht oder aehnliche bedingungen erfuellt sein

**Actions**
Result of automation. what happens after trigger happens

Let't make a quick example of a automation, and then dive deeper into the 3 Parts.

### Example

| Part      | As "Code"     | Wert                          |
|-          |-              |-                              |
| Trigger   | **If**        | Die Zeit ist 9 Uhr Morgends   | 
| Condition | **But not**   | -  |
| Action    | **Then**      | Schalte das Licht an          |

Code:

```
type: turn_on
device_id: <someID>
entity_id: <anotherID>
domain: light
```

### Triggers

The Part for us relevant: Sensors

We choose *Device* as Trigger and then choose the device our sensor is connected to. As trigger we choose the sensor with the addition "voltage changes". (Might be diffrent for other sensors? i have only tested with one).
We get the Option to choose *Above* or *Below*. For a simple Plant Watering Project we want to choose Below, as we are interested when the soil gets dry.
A Duration is also not important for as, as we expect the values to just Drop in a linear way.


### Conditions

We don't need to set conditions yet, but in the future check for water tank fullness might be an idea.

### Actions

Here we want to choose *Device* too and then the device the reacting agent, in my first case a Light, is connected.

As Action I chose flashing, to "alert" the plant parent that their child is thirsty.

### Actual Code:

alias: Plant M < 40 -> Alert
description: ""
trigger:
  - type: voltage
    platform: device
    device_id: <esp ID>
    entity_id: <sensor ID>
    domain: sensor
    below: 40
condition: []
action:
  - device_id: <esp ID>
    domain: light
    entity_id: <light ID>
    type: flash
mode: single
