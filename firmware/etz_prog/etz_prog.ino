#include "allclass.h"

#define TASKS 10

String codes[TASKS] = { "dot", "line5", "line7", "four", "five", "six", "seven", "eight", "nine", "ten" };
OLEDMenu menu(29, 27, 26, TASKS, codes);

Paint robot(28, 41, 39, { 0, 0 }, 11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  robot.initDrive();
  robot.initSens();
  robot.initServo();
  menu.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  menu.update();
}
