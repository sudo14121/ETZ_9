#include "allclass.h"

void encoder::encinit()
{
    Wire.begin();

    if (!enc.begin())
    {
        Serial.println("AS5600 не найден!");
        while (1);
    }

    enc.setDirection(AS5600_CLOCK_WISE);
}

bool encoder::count_enc()
{
    encold = encnow;
    encnow = enc.readAngle();
    if (abs(encold - encnow) > 3)
    {
        count ++;
        return 1;
    }
    return 0;
}

int32_t encoder::getEnc()
{
    encold = encnow;
    encnow = enc.readAngle();
    return encnow;
}

void encoder::setEnc(int angle)
{
    encnow = angle;
    encold = angle;
}