#include "allclass.h"

void Motor::goToPoint(Point pos, int maxSpeed) {
  targetPos = pos;

  int distance = abs(targetPos.x - nowPos.x);

  distance = stepsperone * (distance / len);
  if (distance == 0)
    return;

  if (targetPos.x > nowPos.x) {
    digitalWrite(DIRPIN, FORWARD);
    digitalWrite(DIRPIN2, FORWARD2);
  } else {
    digitalWrite(DIRPIN, !FORWARD);
    digitalWrite(DIRPIN2, !FORWARD2);
  }

  int razgonDist = distance / 1.2;

  timestep = 800;
  stepsGo = 0;

  int minTimeStep = 1000000 / maxSpeed;
  if (minTimeStep < 20)
    minTimeStep = 120;

  if (distance < 20) {
    razgonDist = 0;
    timestep = minTimeStep;
  }

  while (stepsGo < distance) {
    disp->pause();
    encodercount = enc.getEnc();

    digitalWrite(STEPPIN, HIGH);
    digitalWrite(STEPPIN2, HIGH);
    delayMicroseconds(timestep);
    digitalWrite(STEPPIN, LOW);
    digitalWrite(STEPPIN2, LOW);
    delayMicroseconds(timestep);

    Serial.println(encodercount);
    //if (encodercount > 0)
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
  enc.encinit();

  pinMode(DIRPIN, OUTPUT);
  pinMode(STEPPIN, OUTPUT);
  pinMode(DIRPIN2, OUTPUT);
  pinMode(STEPPIN2, OUTPUT);
}

Point Motor::getPos() {
  return nowPos;
}
