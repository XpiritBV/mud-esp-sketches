#define SENSOR_PIN D1 // We connect the output pin of the sound sensor to pin D1 of the ESP

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT); // Set pin to be an input pin
  Serial.println("Listening for sound...");
}

void loop() {
  int triggered = digitalRead(SENSOR_PIN); // Read the status of the sensor
  
  if(triggered == LOW) { // Sensor pin will be low if sound exceeds threshold
    Serial.println("Sound detected!");
  }
}
