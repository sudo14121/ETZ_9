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

int x = 0, y = 0;
bool one = 0;

//#define CALIBR
CRGB leds[3];
String codes[TASKS_COUNT] = { "1", "2", "3", "4", "five", "six", "seven", "eight", "nine", "ten", "calibr", "down", "up" };
OLEDMenu menu(29, 27, 26, TASKS_COUNT, codes);
OLEDMenu& ptr = menu;
OLEDMenu* ukazatel = &ptr;
Paint robot(28, 35, 37, { 0, 0 }, 119, ukazatel);

///////////////ввод морзе кнопочкой///////////
int lDot = 10000, lLine = 3 * lDot, lTime = lDot;
#define N 10
int times[N * 2 - 1] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
String input_OPA[N * 2 - 1] = { "", "", "", "", "", "", "", "", "" };

void check_x() {
  static bool last_state = 0;
  uint64_t timer = millis();
  bool current_state = digitalRead(18);
  while (millis() - timer < 2000) {
    current_state = digitalRead(18);
    if (current_state == 1 && last_state == 0) {
      delay(10);
      x++;
      timer = millis();
    }
    last_state = current_state;
  }
  x -= 1;
}

class TASKS {
public:
  TASKS() {
  }
  void doing(int mode) {
    if (mode != -1) {
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

      menu.showMenu();
      menu.setLastTime(millis());
    }
  }

  void first() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
    delay(1200);
    digitalWrite(33, 1);

    robot.goingStartPos(5000);
    robot.drawDot({ 13, 0 }, 5000);
    robot.drawLine({ 35, 0 }, { 63, 0 }, 5000);
    robot.backzone(5000);

    digitalWrite(33, 0);
  }

  void second() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
    digitalWrite(33, 1);

    check_x();
    menu.showText(String(x));
    digitalWrite(33, 0);

    robot.goingStartPos(5000);
    robot.drawMorze(x, { 75, 0 }, 8, 1.5, 6, 2000);

    robot.backzone(5000);
  }

  void third() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
    delay(1200);
    digitalWrite(33, 1);

    robot.goingStartPos(5000);

    if (!one)
      robot.goingFirst(2000);
    else {
      robot.drawDot({ 220, 0 }, 2000);
    }
    robot.backzone(5000);
    digitalWrite(33, 0);
  }

  void fourth() {
    ///////////////УЧИТЫВАТЬ ТОЛЩИНУ ПЕРА!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!///////////////////
    delay(1200);
    digitalWrite(33, 1);

    robot.goingStartPos(5000);

    robot.goingSecond(2000);

    robot.backzone(5000);
    digitalWrite(33, 0);
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

  FastLED.addLeds<WS2812, DOPD3, GRB>(leds, 3);
  FastLED.clear();
  FastLED.setBrightness(150);

  robot.initDrive();
  robot.initSens();
  robot.initServo();
  menu.init();

  pinMode(ANALOG, INPUT);
  pinMode(DIGIT, INPUT_PULLUP);

  pinMode(DOPD3, OUTPUT);

  input_morze();
  for (int j = 0; j < (2 * N - 1); j++) {
    Serial.print(input_OPA[j]);
  }
}

void loop() {
  /*
  if (menu.getSelectedByLED() == 0)
    FastLED.showColor(CRGB::Red);
  else if (menu.getSelectedByLED() == 1)
    FastLED.showColor(CRGB::Orange);
  else if (menu.getSelectedByLED() == 2)
    FastLED.showColor(CRGB::Green);
  else if (menu.getSelectedByLED() == 3)
    FastLED.showColor(CRGB::Yellow);
  else if (menu.getSelectedByLED() == 4)
    FastLED.showColor(CRGB::Purple);
  else if (menu.getSelectedByLED() == 5)
    FastLED.showColor(CRGB::Blue);
  else if (menu.getSelectedByLED() == 6)
    FastLED.showColor(CRGB::Pink);
  else if (menu.getSelectedByLED() == 7)
    FastLED.showColor(CRGB::DeepPink);
  else if (menu.getSelectedByLED() == 8)
    FastLED.showColor(CRGB::Brown);
  else if (menu.getSelectedByLED() == 9)
    FastLED.showColor(CRGB::Gray);
  FastLED.show();

  if (!digitalRead(18) && !one) one = 1;

  menu.update();
  int temp = menu.getSelected();
  //tasks.doing(temp);
  Serial.println(digitalRead(DIGIT));
  Serial.println(one);
  Serial.println(analogRead(ANALOG));
  */
}
