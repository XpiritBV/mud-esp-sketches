#define ledPin1 D1
#define ledPin2 D2

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  set(ledPin1);
  set(ledPin2);  
  delay(1000);
}

void set(int ledPin){
  Serial.print("Setting led pin: ");
  Serial.println(ledPin);
   analogWrite(ledPin, random(1,1024));
}

