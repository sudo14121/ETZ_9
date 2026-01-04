#include "allclass.h"

void Motor::goToPoint(Point pos, int maxSpeed) {
    targetPos = pos;

    int distance = abs(targetPos.x - nowPos.x);
    if (distance == 0)
      return;

    if (targetPos.x > nowPos.x)
      digitalWrite(DIRPIN, FORWARD);
    else
      digitalWrite(DIRPIN, !FORWARD);

    int razgonDist = min(distance / 2, 50);

    timestep = 2000;
    stepsGo = 0;

    int minTimeStep = 1000000 / maxSpeed;
    if (minTimeStep < 100)
      minTimeStep = 100;

    if (distance < 20) {
      razgonDist = 0;
      timestep = minTimeStep;
    }

    while (stepsGo < distance) {
      digitalWrite(STEPPIN, HIGH);
      delayMicroseconds(timestep);
      digitalWrite(STEPPIN, LOW);
      delayMicroseconds(timestep);

      stepsGo++;

      if (razgonDist > 0) {
        if (stepsGo < razgonDist && timestep > minTimeStep) {
          timestep -= acceleration;
          if (timestep < minTimeStep)
            timestep = minTimeStep;
        } else if (stepsGo >= (distance - razgonDist) && timestep < 2000) {
          timestep += acceleration;
        }
      }
    }

    nowPos = targetPos;
  }
  void Motor::setStart(Point set) {
    nowPos = set;
  }

  void Motor::StepperInit() {
    pinMode(DIRPIN, OUTPUT);
    pinMode(STEPPIN, OUTPUT);
  }

  Point Motor::getPos() {
    return nowPos;
  }