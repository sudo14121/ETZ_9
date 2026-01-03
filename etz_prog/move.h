#include <Arduino.h>
#include <iostream.h> 

struct Point
{
    int x, y;
};

class Motor
{
public:
    Motor(std::string mName, int dir, int step, Point start)
    {
        name = mName;
        DIRSTEP = dir;
        STEPPIN = step;
        nowPos = start;
    }
    void goToPoint(Point pos, int speed)
    {

    }
    void StepperInit()
    {
        pinMode(DIRPIN, OUTPUT);
        pinMode(STEPPIN, OUTPUT);
    }

private:
    std::string name;
    Point targetPos;
    Point nowPos;
    int stepsNeed;
    int stepsGo;
    int STEPPIN;
    int DIRPIN;
    int timestep = 100;
    void goMotor(int time)
    {
        digitalWrite(STEPPIN, 1);
        delayMicroseconds(timestep);
        digitalWrite(STEPPIN, 0);
        delayMicroseconds(timestep);
    }
}
