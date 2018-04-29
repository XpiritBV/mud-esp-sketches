#include <BH1750.h>
#include <Wire.h>

/* Connect as follows:
 *  VCC --> 3v3
 *  GND --> GND
 *  SDA --> D1
 *  SCL --> D2
 *  ADD --> Not connected
 *  
 *  You need the BH1750 library from here: https://github.com/claws/BH1750
 *  Download repo as ZIP file. Then install in Arduino using Sketch --> Include Library --> Add .ZIP library
 */

BH1750 lightMeter;

void setup(){

  Serial.begin(115200);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  // SCL = D2, SDA = D1
  Wire.begin(D1, D2);

  lightMeter.begin();
  Serial.println(F("BH1750 Test"));

}

void loop() {
  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);

}
