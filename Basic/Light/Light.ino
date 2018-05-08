#include "BH1750.h"
#include <Wire.h>

/* Connect as follows:
 *  VCC --> 3v3
 *  GND --> GND
 *  SDA --> D2
 *  SCL --> D3
 *  ADD --> Not connected
 *  
  Start the Serial Monitor in the Tools menu.
 */

BH1750 lightMeter;

void setup(){

  Serial.begin(115200);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  // SCL = D3, SDA = D2
  Wire.begin(D2, D3);

  lightMeter.begin();
  Serial.println(F("BH1750 Test"));

  pinMode(D1, OUTPUT);    
}

void loop() {
  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);
  //turn on the LED
  analogWrite(D1, 1024);
}
