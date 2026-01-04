#include "allclass.h"

void Paint::initServo()
{
    brush.attach(SERVO);
    brush.write(upPos);
    delay(500);
}

void Paint::initYStepper()
{
    pinMode(DIR, OUTPUT);
    pinMode(STEP, OUTPUT);
}

void Paint::initDrive()
{
    left.StepperInit();
    right.StepperInit();
}

void Paint::initSens()
{
    sens = Sensors(56, 54);
}

void Paint::downBrush()
{
    brush.write(downPos);
    delay(500);
}

void Paint::upBrush()
{
    brush.write(upPos);
    delay(500);
}

void Paint::drawLine(Point start, Point finish, int speed)
{
    left.goToPoint(start, speed);
    right.goToPoint(start, speed);

    downBrush();
    left.goToPoint(finish, speed);
    right.goToPoint(finish, speed);

    upBrush();
}

void Paint::drawDot(Point pos, int speed)
{
    left.goToPoint(pos, speed);
    right.goToPoint(pos, speed);

    downBrush();
    upBrush();
}

void Paint::goingStartPos(int speed)
{
    while (!sens.ishereblack())
    {
        left.goToPoint({left.getPos().x + 1, 0}, speed);
        right.goToPoint({right.getPos().x + 1, 0}, speed);
    }

    while (sens.ishereblack())
    {
        left.goToPoint({left.getPos().x + 1, 0}, speed);
        right.goToPoint({right.getPos().x + 1, 0}, speed);
    }

    left.setStart({-need, 0});
    right.setStart({-need, 0});
}