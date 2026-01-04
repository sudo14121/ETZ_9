#include "allclass.h"

#define TASKS_COUNT 10
#define STEPSFORONE 3200

String codes[TASKS_COUNT] = { "dot", "line5", "line7", "four", "five", "six", "seven", "eight", "nine", "ten" };
OLEDMenu menu(29, 27, 26, TASKS_COUNT, codes);

Paint robot(28, 41, 39, { 0, 0 }, 110);


class TASKS {
public:
  TASKS()
  {
    
  }
  void doing(int mode) {
    if (mode != -1)
      switch (mode) {
        case 0:
          first();
          break;
        case 1:
          second();
          break;
        case 2:
          third();
          break;
        case 3:
          fourth();
          break;
        case 4:
          fifth();
          break;
        case 5:
          sixth();
          break;
        case 6:
          seventh();
          break;
        case 7:
          eighth();
          break;
        case 8:
          nineth();
          break;
        case 9:
          tenth();
          break;
      }
  }

  void first() {
    robot.drawLine({ 2, 0 }, { STEPSFORONE, 0 }, 2000);
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void second() {
    robot.drawDot({800, 0}, 5000);
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void third() {
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void fourth() {
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void fifth() {
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void sixth() {
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void seventh() {
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void eighth() {
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void nineth() {
    menu.showMenu();
    menu.setLastTime(millis());
  }

  void tenth() {
    menu.showMenu();
    menu.setLastTime(millis());
  }
private:
  uint64_t timer = millis();
};

TASKS tasks;

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
  digitalWrite(33, 1);
  menu.update();
  int temp = menu.getSelected();
  tasks.doing(temp);
}
