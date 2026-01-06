#include "allclass.h"

void Paint::initServo() {
  brush.attach(SERVO);
  brush.write(upPos);
  delay(500);
}

void Paint::initYStepper() {
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
}

void Paint::initDrive() {
  motors.StepperInit();
}

void Paint::initSens() {
  sens = Sensors(56, 54);
}

void Paint::downBrush() {
  brush.write(downPos);
  delay(500);
}

void Paint::upBrush() {
  brush.write(upPos);
  delay(500);
}

void Paint::drawLine(Point start, Point finish, int speed) {
  now_position = motors.getPos();
  if (start.x < now_position.x) {
    motors.goToPoint(finish, speed);
    downBrush();
    motors.goToPoint(start, speed);
    upBrush();
  } else {
    {
      motors.goToPoint(start, speed);
      downBrush();
      motors.goToPoint(finish, speed);
      upBrush();
    }
  }
}

void Paint::drawDot(Point pos, int speed) {
  motors.goToPoint(pos, speed);

  downBrush();
  upBrush();
}

void Paint::goingStartPos(int speed) {
  int plus = 1;
  if (motors.getPos().x != 0) {
    plus = -1;
  }
  while (!sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }

  while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }
  if (plus == 1)
    motors.setStart({ -need, 0 });
}

void Paint::backzone(int speed) {
  goingStartPos(speed);
  motors.goToPoint({ -need - 70, 0 }, speed);
}

void Paint::calibr() {
  sens.calibr();
  Serial.println(EEPROM.read(0) * 4);
  Serial.println(EEPROM.read(1) * 4);
}