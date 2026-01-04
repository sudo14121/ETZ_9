#include <Arduino.h>

struct Point {
  int x, y;
};

class Motor {
public:
  Motor() {
    name = "мотор";
    DIRPIN = 0;
    STEPPIN = 0;
    nowPos = { 0, 0 };
    FORWARD = 1;
  }
  Motor(const char *mName, int dir, int step, Point start, bool forward) {
    name = mName;
    DIRPIN = dir;
    STEPPIN = step;
    nowPos = start;
    FORWARD = forward;
  }
  void goToPoint(Point pos, int maxSpeed) {
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
  void setStart(Point set) {
    nowPos = set;
  }

  void StepperInit() {
    pinMode(DIRPIN, OUTPUT);
    pinMode(STEPPIN, OUTPUT);
  }

  Point getPos() {
    return nowPos;
  }

private:
  const char *name;
  Point targetPos;
  Point nowPos;
  int stepsGo;
  int STEPPIN;
  int DIRPIN;
  int timestep = 100;
  bool FORWARD = 0;
  int acceleration = 5;
};
