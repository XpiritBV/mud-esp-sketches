#define ledPin1 D1

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
}

void loop() {
 blinkFiveTimes();
 fadeTwoTimes(); 
}

void blinkFiveTimes()
{
  for(int i = 0; i < 5; i++) {
    digitalSet(ledPin1, HIGH);
    delay(200);
    digitalSet(ledPin1, LOW);
    delay(200);
  }
}

void fadeTwoTimes() {
  for(int i = 0; i< 2; i++)
  {
    fadeUpAndDown(ledPin1);
  }
}

// Uses analogWrite() to write a PWM signal to the output pin. Effectively, this means the LED will be dimmed.
// For an explanation on PWM: https://en.wikipedia.org/wiki/Pulse-width_modulation
void fadeUpAndDown(int ledPin) {
  for(int i = 0; i <= 1023; i++) {
    Serial.print("Setting led pin: ");
    Serial.print(ledPin);
    Serial.print(" to value: ");
    Serial.println(i);
    analogWrite(ledPin, i);
    delay(1); //Pause 1 millisecond, for effect.
  }
  for(int i = 1023; i > 0 ; i--) {
    Serial.print("Setting led pin: ");
    Serial.print(ledPin);
    Serial.print(" to value: ");
    Serial.println(i);
    analogWrite(ledPin, i);
    delay(1); //Pause 1 millisecond, for effect.
  }
}

// Uses digitalWrite() to set output pin to HIGH or LOW value. This means the Led will be on or off.
void digitalSet(int ledPin, int value){
  Serial.print("Setting led pin: ");
  Serial.print(ledPin);
  Serial.print(" to value: ");
  Serial.println(value);
  digitalWrite(ledPin, value);
}

