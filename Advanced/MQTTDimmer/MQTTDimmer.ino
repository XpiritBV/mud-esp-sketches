#include <PubSubClient.h>
#include <ESP8266WiFi.h>

const char* ssid     = "<your ssid>";
const char* password = "<your wifi password>";
const char* mqtt_server = "<your mqtt broker>";
const char* mqttClientIdPrefix = "nightlight-";
const char* stateBrightnessTopic = "dimmer/state/brightness";     //Publish actual brightness here
const char* stateMotionTopic = "dimmer/state/motion";             //Publish motion here
const char* commandBrightnessTopic = "dimmer/command/brightness"; //Subscribe to this topic to receive brightness changes
const char* commandTopic = "dimmer/command/switch";               //Subscribe to this topic to receive ON/OFF changes
const char* stateTopic = "dimmer/state/switch";                   //Publish ON/OFF state here

// payloads by default (on/off)
const char* LIGHT_ON = "ON";
const char* LIGHT_OFF = "OFF";
int currentBrightness = 0;        //Brightness for the connected LED. Goes from 0 to 255.
bool currentSwitchState = false;  //Whether the LED should be on or not. True = on, false = off.

#define LED_PIN D1 // Pin to which we have connected the LED

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setup() {
  // Set our LED pin as an output pin
  pinMode(LED_PIN, OUTPUT);
  // Make PWM range go from 0 - 255 (255 = max brightness, 0 = off)
  analogWriteRange(255);

  Serial.begin(115200);
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  /* Connect to MQTT broker */
  mqttClient.setServer(mqtt_server, 1883);
  /* Set callback function for when we receive a message */
  mqttClient.setCallback(messageReceivedCallback);
}

void messageReceivedCallback(char* p_topic, byte* p_payload, unsigned int p_length) {
  Serial.print("Message arrived [");
  Serial.print(p_topic);
  Serial.print("] ");

  // concat the payload into a string
  String payload;
  for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }
  Serial.print(payload);
  Serial.println();

  if(String(commandTopic).equals(p_topic)) {
    Serial.println("Message received on command topic");
    setSwitchState(payload);
  } else if (String(commandBrightnessTopic).equals(p_topic)) {
    Serial.println("Message received on brightness topic");
    setBrightness(payload.toInt());
  }
}

void setSwitchState(String newState) {
  if(newState.equals(String(LIGHT_ON))) {
    Serial.println("Switching light on...");
    currentSwitchState = true;
    // Publish new state to state topic
    mqttClient.publish(stateTopic, LIGHT_ON);
  } else if (newState.equals(String(LIGHT_OFF))) {
    Serial.println("Switching light off");
    currentSwitchState = false;
    // Publish new state to state topic
    mqttClient.publish(stateTopic, LIGHT_OFF);
  }
}

void setBrightness(int newBrightness) {
  Serial.print("Setting brightness to: ");
  Serial.println(newBrightness);

  currentBrightness = newBrightness;
  //Convert number back into char array and publish it
  char buf[5];
  sprintf(buf, "%i\n", currentBrightness);
  mqttClient.publish(stateBrightnessTopic, buf);
}

void mqttReconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = mqttClientIdPrefix;
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqttClient.connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      mqttClient.subscribe(commandBrightnessTopic);
      mqttClient.subscribe(commandTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!mqttClient.connected()) {
    mqttReconnect();
  }
  mqttClient.loop();

  //Set PWM for LED to set value
  if(currentSwitchState == true) {
    analogWrite(LED_PIN, currentBrightness);
  } else  {
    analogWrite(LED_PIN, 0);
  }
  
  // Give others a chance to do their work
  yield();
}

