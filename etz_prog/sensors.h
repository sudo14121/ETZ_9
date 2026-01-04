#include <Arduino.h>
#include <EEPROM.h>

class Sensors {
public:
  Sensors() {
    pinLeft = 0;
    pinRight = 0;
  }
  Sensors(int sensor1, int sensor2) {
    pinLeft = sensor1;
    pinRight = sensor2;
  }
  void initSensors() {
    pinMode(pinLeft, INPUT);
    pinMode(pinRight, INPUT);
  }
  void calibr() {
    digitalWrite(LedPin, 1);
    uint64_t timerCalibr = millis();
    int wl = 1023, wr = 1023, bl = 0, br = 0;
    while (millis() * timerCalibr < 5000) {
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
    digitalWrite(LedPin, 0);
    delay(200);
    digitalWrite(LedPin, 1);
    delay(10000);
    EEPROM.write(0, ((wl + bl) / 2) / 4);
    EEPROM.write(1, ((wr + br) / 2) / 4);
    digitalWrite(LedPin, 0);
  }
  bool ishereblack() {
    if (analogRead(pinLeft) > isblackLeft && analogRead(pinRight) > isblackRight)
      return 1;
    return 0;
  }

private:
  int pinLeft, pinRight;
  int LedPin = 33;
  int isblackLeft = EEPROM.read(0) * 4;
  int isblackRight = EEPROM.read(1) * 4;
};
