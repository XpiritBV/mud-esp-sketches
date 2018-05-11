# Xebia MUD 2018: DIY Home Automation
This repo contains sample code that you can use to quickly get up and running with an ESP8266 and some sensors.

1. [Getting started](#getting-started)
1. [Workshop infrastructure](#workshop-infrastructure)
## Getting started
Here's how to get started by setting up your dev environment.

### Install Arduino development environment
1. Download here: https://www.arduino.cc/
2. Follow instructions

### Configure and use the board manager for ESP8266.
1. Go to https://github.com/esp8266/Arduino
1. Follow instructions
1. In the menu select the correct board:
    1. `Tools\Board`: `WeMos D1 R2 & mini`

### Get the sample code
1. Clone https://github.com/XpiritBV/mud-esp-sketches.git

### Run the sample code
1. Open Arduino (e.g. `c:\Program Files (x86)\Arduino\arduino.exe`)
1. Open an ino file
1. Make sure you select the correct COM port and baud rate
    1. `Tools\Port`: `<Your COM port>`
    1. `Tools\Upload Speed`: `115200`
1. Upload the sketch: `Sketch\Upload`
1. Open the serial monitor for debugging information:
    1. `Tools\Serial Monitor`
    1. Make sure to use correct settings for the serial monitor:
        1. `Baud rate`: `115200`
        1. `Line ending`: `No Line Ending`  

## Workshop Infrastructure
We have created a simple infrastructure, based on MQTT, to allow our ESP8266 nodes to communicate. The infrastructure consists of a single MQTT broker, and a bunch of Node-RED instances to implement logic. Each workshop participant can use their own Node-RED instance, so that we don't get in eachothers way. There'as also a web based MQTT client, which can be convenient for testing.

### MQTT Basics
To allow our ESP modules to communicate, we use the [MQ Telemetry Transport](http://mqtt.org/) protocol. The basics for the MQTT protocol are very simple. It is based on publish/subscribe messaging. Each client connects to a MQTT broker to publish and/or subscribe to messages. Each message consists of two parts:
- Topic: Messages are always published to a specific topic. Clients can subscribe to one or more topics to receive the messages published there.
- Payload: The message contents. This can be anything, like a simple string, a number, JSON, or something else, depending on your needs.

### MQTT Broker
Our MQTT broker is running [Eclipse Mosquitto](https://mosquitto.org/). You can reach it at:
- Host: `mudmqtt.westeurope.cloudapp.azure.com`
- Port:
    - `8000`: Websocket port. Use this for connecting from a web wlient, such as the web client we use for testing.
    - `1883`: Default TCP port. Use this to connect from your Arduino code and Node-RED.

### Node-RED
[Node-RED](https://nodered.org/) can be used to implement logic. Node-RED can send and receive MQTT messages, but can also interact with other systems (e.g. web API's). Logic is implemented by writing Javascript functions.
- Host: `mudmqtt.westeurope.cloudapp.azure.com`
- Port: `1891-1905` We have 16 instances running, so that everyone can use their own without interfering with eachother.

When writing Javascript functions, refer to the message topic using `msg.topic`, and to the actual message content as `msg.payload`.

### HiveMQ Websockets Client
The HiveMQ client is convenient for monitoring the MQTT bus. Use it to connect to the MQTT broker.
- URL: http://www.hivemq.com/demos/websocket-client/
- Connect to:
    - Host: `mudmqtt.westeurope.cloudapp.azure.com`
    - Port:`8000`
    - ClientID: choose something to your liking, but it needs to be unique

Monitor your messages by creating a new topic subscription. You can use `#` as a wildcard in the topic. E.g. `testtopic/#` will subscribe to all messages delivered in any of the subtopics of `testtopic`. Just use `#` to subscribe to ALL messages.