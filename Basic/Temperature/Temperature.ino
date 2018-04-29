 /*
  * Connect as follows:
  * Red --> 3v3
  * Black --> Gnd
  * Yellow --> D1
  */

#include <DallasTemperature.h> // Install this one from Library Manager
#include <OneWire.h> // Install this one from Library Manager

#define SENSOR_PIN D1 // We connect the output pin of the PIR to pin D1 of the ESP

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(SENSOR_PIN);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature DS18B20(&oneWire);

char temperatureCString[7];

void setup() {
  Serial.begin(115200);
  DS18B20.begin();
}

void loop() {
  float tempC;
  do {
    DS18B20.requestTemperatures(); 
    tempC = DS18B20.getTempCByIndex(0); //We're assuming there is only one temp sensor here...
    dtostrf(tempC, 2, 2, temperatureCString);
    delay(100);
  } while (tempC == 85.0 || tempC == (-127.0)); // These are the extreme values. If we get these as result, sensor was not ready yet.
  Serial.print("Got temperature: ");
  Serial.println(temperatureCString);
  delay(1000);
  
}
