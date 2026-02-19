#include "Arduino.h"
#include "allclass.h"

void Sensors::initSensors() {
  pinMode(pinLeft, INPUT);
  pinMode(pinRight, INPUT);
  pinMode(pinEnd, INPUT_PULLUP);
}
void Sensors::calibr(Motor& c) {
  digitalWrite(34, 1);
  int wl = 1023, wr = 1023, bl = 0, br = 0;
  while (c.getPos().x < 150) {
    c.goToPoint({ c.getPos().x + 1, 0 }, 2500);
    int leftS = analogRead(pinLeft);
    int rightS = analogRead(pinRight);
    if (leftS > bl)
      bl = leftS;
    if (rightS > br)
      br = rightS;
    if (leftS < wl)
      wl = leftS;
    if (rightS < wr)
      wr = rightS;
  }
  digitalWrite(34, 0);
  delay(200);
  digitalWrite(34, 1);
  while(digitalRead(26));
  EEPROM.write(0, ((wl + bl) / 2) / 4);
  EEPROM.write(1, ((wr + br) / 2) / 4);
  digitalWrite(34, 0);
}

void Sensors::yCalibr(Motor& c) {
  digitalWrite(34, 1);
  int xpos = c.getPos().x;
  while (digitalRead(pinEnd)) {
    c.goToPoint({xpos, c.getPos().y - 1 }, 3000);
  }
  digitalWrite(34, 0);
  delay(200);
  digitalWrite(34, 1);
}

bool Sensors::ishereblack() {
  if (analogRead(pinLeft) > isblackLeft) {
    return 1;
  }
  return 0;
}

void Sensors::newpos()
{
  EEPROM.write(2, analogRead(pinLeft) / 4);
  EEPROM.write(3, analogRead(pinRight) / 4);  
}