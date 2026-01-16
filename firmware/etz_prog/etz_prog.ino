#include "allclass.h"

#define TASKS_COUNT 13
#define STEPSFORONE 3200

#define DIGIT 18
#define ANALOG A4

#define DOPD 42
#define DOPD2 44
#define DOPD3 46
#define DOPA A1
#define DOPA2 A3
#define DOPA3 A5

//#define CALIBR
CRGB leds[3];
String codes[TASKS_COUNT] = { "five lines", "morze sos", "239 morze", "four", "five", "six", "seven", "eight", "nine", "ten", "calibr", "down", "up" };
OLEDMenu menu(29, 27, 26, TASKS_COUNT, codes);
OLEDMenu& ptr = menu;
OLEDMenu* ukazatel = &ptr;
Paint robot(28, 35, 37, { 0, 0 }, 119, ukazatel);

class TASKS {
public:
  TASKS() {
  }
  void doing(int mode) {
    if (mode != -1) {
      if (mode != 10 and mode != 11 and mode != 12)
        robot.goingStartPos(5000);
      switch (mode) {
        case 0:
          FastLED.showColor(CRGB::GREEN);
          FastLED.show();
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
        case 10:
          calibr();
          break;
        case 11:
          down();
          break;
        case 12:
          up();
          break;
      }
      if (mode != 10 and mode != 11 and mode != 12)
        robot.backzone(5000);

      menu.showMenu();
      menu.setLastTime(millis());
    }
  }

  void first() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
    robot.drawLine({ 30, 0 }, { 32, 0 }, 5000);
    robot.drawLine({ 32 + 5 + 2, 0 }, { 38 + 7 + 1, 0 }, 5000);
    robot.drawLine({ 38 + 7 + 9 + 2 + 1, 0 }, { 38 + 7 + 9 + 11 + 1, 0 }, 5000);
    robot.drawLine({ 38 + 7 + 9 + 11 + 13 + 2 + 1, 0 }, { 38 + 7 + 9 + 11 + 13 + 15 + 1, 0 }, 5000);
    robot.drawLine({ 38 + 7 + 9 + 11 + 13 + 15 + 17 + 2 + 1, 0 }, { 38 + 7 + 9 + 11 + 13 + 15 + 17 + 19 + 1, 0 }, 5000);
  }

  void second() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
    robot.drawMorze('С', { 20, 0 }, 12, 6, 2000);
    robot.drawMorze('О', { 58, 0 }, 12, 6, 2000);
    robot.drawMorze('С', { 118, 0 }, 12, 6, 2000);
  }

  void third() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
    robot.drawMorze('2', { 20, 0 }, 6, 4, 2000);
    robot.drawMorze('3', { 66, 0 }, 6, 4, 2000);
    robot.drawMorze('9', { 98, 0 }, 6, 4, 2000);
  }

  void fourth() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
  }

  void fifth() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
  }

  void sixth() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
  }

  void seventh() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
  }

  void eighth() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
  }

  void nineth() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
  }

  void tenth() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
  }

  void calibr() {
    robot.calibr();
    menu.calibr_sens();
  }

  void down() {
    robot.downBrush();
  }

  void up() {
    robot.upBrush();
  }
private:
  uint64_t timer = millis();
};

TASKS tasks;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, 46, GRB>(leds, 3);
  FastLED.clear();
  FastLED.setBrightness(150);

  robot.initDrive();
  robot.initSens();
  robot.initServo();
  menu.init();

  pinMode(ANALOG, INPUT);
  pinMode(DIGIT, INPUT_PULLUP);
}

void loop() {
  FastLED.showColor(CRGB::Orange);
  FastLED.show();
  digitalWrite(33, 1);
  menu.update();
  int temp = menu.getSelected();
  tasks.doing(temp);
  Serial.println(digitalRead(DIGIT));
  Serial.println(analogRead(ANALOG));
}
