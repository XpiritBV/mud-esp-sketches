#define RELAY_PIN D1 // The relay is on the shield is connected to pin D1 on the ESP

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT); // Set pin to be an output pin
}

void loop() {
  // Just switch the relay on and off every 10 seconds
  Serial.println("Switching relay on...");
  digitalWrite(RELAY_PIN, HIGH);
  delay(10000);
  Serial.println("Switching relay off...");
  digitalWrite(RELAY_PIN, LOW);
  delay(10000);
}
