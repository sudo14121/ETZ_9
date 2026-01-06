#include <AS5600.h>
#include <Wire.h>

AS5600 encoder;  

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!encoder.begin()) {
    Serial.println("AS5600 не найден!");
    while(1);
  }
  
  encoder.setDirection(AS5600_CLOCK_WISE); 
  
  Serial.println("AS5600 готов!");
  Serial.print("Адрес: 0x");
  Serial.println(encoder.getAddress(), HEX);
}

void loop() {
  float angle = encoder.readAngle();
  Serial.print("Угол: ");
  Serial.print(angle);
  Serial.println("°");
  
  uint16_t raw = encoder.rawAngle();
  Serial.print("RAW: ");
  Serial.println(raw);

  delay(100);
}