#define SENSOR_PIN D1 // We connect the output pin of the PIR to pin D1 of the ESP

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT); // Set pin to be an input pin
}

void loop() {
  int triggered = digitalRead(SENSOR_PIN); // Read the status of the PIR
  Serial.print("Motion detected: ");
  if(triggered == HIGH) {
    Serial.println("Yes");
  } else {
    Serial.println("No");
  }
  delay(100); // A small delay so that we don't overload the serial console
}
