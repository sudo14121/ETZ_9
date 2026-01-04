#include <Arduino.h>
#include <Servo.h>
#include "move.h"
#include "sensors.h"

class Paint {
public:
  Paint(int servoPin, int dir, int step, Point startPos, int needPlus) {
    SERVO = servoPin;
    DIR = dir;
    STEP = step;
    start = startPos;
    need = needPlus;
    left = Motor("left", 35, 37, startPos, 1);
    right = Motor("right", 69, 67, startPos, 0);
  }
  void initServo() {
    brush.attach(SERVO);
    upBrush();
  }

  void initYStepper() {
    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);
  }

  void initDrive() {
    left.StepperInit();
    right.StepperInit();
  }

  void initSens() {
    sens = Sensors(56, 54);
  }

  void downBrush() {
    brush.write(downPos);
    delay(500);
  }

  void upBrush() {
    brush.write(upPos);
    delay(500);
  }

  void drawLine(Point start, Point finish, int speed) {
    left.goToPoint(start, speed);
    right.goToPoint(start, speed);

    downBrush();
    left.goToPoint(finish, speed);
    right.goToPoint(finish, speed);

    upBrush();
  }

  void drawDot(Point pos, int speed) {
    left.goToPoint(pos, speed);
    right.goToPoint(pos, speed);

    downBrush();
    upBrush();
  }

  void goingStartPos(int speed) {
    while (!sens.ishereblack()) {
      left.goToPoint({ left.getPos().x + 1, 0 }, speed);
      right.goToPoint({ right.getPos().x + 1, 0 }, speed);
    }

    while (sens.ishereblack()) {
      left.goToPoint({ left.getPos().x + 1, 0 }, speed);
      right.goToPoint({ right.getPos().x + 1, 0 }, speed);
    }

    left.setStart({ -need, 0 });
    right.setStart({ -need, 0 });
  }

private:
  int STEP, DIR;
  int SERVO;
  Servo brush;
  int downPos = 0;
  int upPos = 180;
  Point start = { 0, 0 };
  int need = 0;
  Motor left;
  Motor right;
  Sensors sens;
};