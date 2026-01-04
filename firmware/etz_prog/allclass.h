#include <Arduino.h>

#include <EEPROM.h>

#include <Servo.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
  void goToPoint(Point pos, int maxSpeed);
  void setStart(Point set);
  void StepperInit();
  Point getPos();

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
  void calibr();
  bool ishereblack();

private:
  int pinLeft, pinRight;
  int LedPin = 33;
  int isblackLeft = EEPROM.read(0) * 4;
  int isblackRight = EEPROM.read(1) * 4;
};

class Paint {
public:
  Paint(int servoPin, int dir, int step, Point startPos, int needPlus) {
    SERVO = servoPin;
    DIR = dir;
    STEP = step;
    start = startPos;
    need = needPlus;
    left = Motor("left", 35, 37, startPos, 1);
    right = Motor("right", 69, 67, startPos, 0);
  }
  void initServo();
  void initYStepper();
  void initDrive();
  void initSens();
  void downBrush();
  void upBrush();
  void drawLine(Point start, Point finish, int speed);
  void drawDot(Point pos, int speed);
  void goingStartPos(int speed);

private:
  int STEP, DIR;
  int SERVO;
  Servo brush;
  int downPos = 90;
  int upPos = 145;
  Point start = { 0, 0 };
  int need = 0;
  Motor left;
  Motor right;
  Sensors sens;
};

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI 51  // D1
#define OLED_CLK  52  // D0  
#define OLED_DC   24  // DC
#define OLED_CS   23 // CS
#define OLED_RESET 25  // RES

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
  void showText(String text);
  ~OLEDMenu();
  String transliterate(String text);
private:
  Adafruit_SSD1306 *display;
  int upBtn, downBtn, selectBtn;
  int selected;
  int modeSelected = -1;
  unsigned long lastTime;
  String *modes;
  int modeCount;

  void showMenu();
  void showSelected();
};