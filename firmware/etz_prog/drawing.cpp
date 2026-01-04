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
  while (!sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + 1, 0 }, speed);
  }

  while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + 1, 0 }, speed);
  }

  motors.setStart({ -need, 0 });
}