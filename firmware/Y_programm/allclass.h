#include <Arduino.h>

#include <EEPROM.h>

#include <Servo.h>

#include<FastLED.h> 

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <AS5600.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI 51
#define OLED_CLK 52
#define OLED_DC 24
#define OLED_CS 23
#define OLED_RESET 25

class OLEDMenu {
public:
  OLEDMenu(int upPin, int downPin, int selectPin, int count, String modeNames[]) {
    upBtn = upPin;
    downBtn = downPin;
    selectBtn = selectPin;
    modeCount = count;

    modes = new String[modeCount];
    for (int i = 0; i < modeCount; i++) {
      modes[i] = modeNames[i];
    }

    selected = 0;
    lastTime = 0;

    display = new Adafruit_SSD1306(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
  }

  void init();
  void update();
  int getSelected();
  int getSelectedByLED();
  void showText(String text);
  void showMenu();
  void setLastTime(uint64_t timer);
  void calibr_sens();
  void sensorsdisp();
  void drawcar();
  void marvel();
  void start();
  void pause();

private:
  Adafruit_SSD1306* display;
  int upBtn, downBtn, selectBtn;
  int selected = 0;
  int modeSelected = -1;
  uint64_t lastTime;
  String* modes;
  int modeCount;

  void showSelected();
};

class encoder {
public:
  encoder() {
    encnow = 0;
    encold = 0;
    count = 0;
  }
  void encinit();
  bool count_enc();
  int32_t getEnc();
  void setEnc(int angle);

private:
  AS5600 enc;
  volatile int encnow;
  volatile int encold;
  volatile int count;
};

struct Point {
  int x, y;
};

class Motor {
public:
  Motor() {
    name = "мотор";
    nowPos = { 0, 0 };
    FORWARD = 1;
  }
  Motor(const char* mName, int dir, int step, int dir2, int step2, int dir3, int step3, Point start, OLEDMenu* display, bool forward = 0, bool forward2 = 1) {
    name = mName;
    DIRPIN = dir;
    STEPPIN = step;
    DIRPIN2 = dir2;
    STEPPIN2 = step2;
    DIRPIN3 = dir3;
    STEPPIN3 = step3;
    nowPos = start;
    FORWARD = forward;
    FORWARD2 = forward2;
    disp = display;
  }
  void goToPoint(Point pos, int maxSpeed);
  void setStart(Point set);
  void StepperInit();
  Point getPos();

private:
  //encoder enc;
  const char* name;
  Point targetPos = {0, 0};
  Point nowPos;
  int stepsGo = 0;
  int STEPPIN, STEPPIN2, STEPPIN3;
  int DIRPIN, DIRPIN2, DIRPIN3;
  int timestep = 2000;
  bool FORWARD = 0;
  bool FORWARD2 = 0;
  bool FORWARD3 = 0;
  int acceleration = 5;
  float len = 137.5;
  int stepsperone = 3200;
  volatile int encodercount = 0;

  OLEDMenu* disp;
};

class Sensors {
public:
  Sensors() {
    pinLeft = 0;
    pinRight = 0;
  }
  Sensors(int sensor1, int sensor2) {
    pinLeft = sensor1;
    pinRight = sensor2;
  }
  void initSensors();
  void calibr(Motor& c);
  bool ishereblack();
  void newpos();

private:
  int pinLeft, pinRight;
  int LedPin = 33;
  int isblackLeft = EEPROM.read(0) * 4;
  int isblackRight = EEPROM.read(1) * 4;
};

class Paint {
public:
  Paint(int servoPin, int dir, int step, Point startPos, int needPlus, OLEDMenu* display) {
    SERVO = servoPin;
    DIR = dir;
    STEP = step;
    start = startPos;
    need = needPlus;
    motors = Motor("motors", 41, 39, 69, 67, 37, 35, startPos, display);
  }
  void initServo();
  void initYStepper();
  void initDrive();
  void initSens();
  void downBrush();
  void upBrush();
  void drawLine(Point start, Point finish, int speed);
  void drawDot(Point pos, int speed);
  void drawLines(Point pos1, int lenLine, int lenBetweenLines, int countLines, int speed);
  void drawDots(Point pos, int lenBetweenDots, int countDots, int speed);
  void goingStartPos(int speed);
  void backzone(int speed);
  void calibr();
  void testsens();
  void drawMorze(int letter, Point start_pos, float lenLine, float lendot, float lenBetween, float speed);
  void goingFirst(int speed);
  void goingSecond(int speed);
  void goToPoint(Point point, int speed);

private:
  int STEP, DIR;
  int SERVO;
  Servo brush;
  int downPos = 0;
  int upPos = 50;
  Point start = { 0, 0 };
  Point now_position = { 0, 0 };
  int need = 0;
  Motor motors;
  Sensors sens;
};