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
  Motor(const char *mName, int dir, int step, int dir2, int step2, Point start, bool forward = 1, bool forward2 = 0) {
    name = mName;
    DIRPIN = dir;
    STEPPIN = step;
    DIRPIN2 = dir2;
    STEPPIN2 = step2;
    nowPos = start;
    FORWARD = forward;
    FORWARD2 = forward2;
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
  int STEPPIN, STEPPIN2;
  int DIRPIN, DIRPIN2;
  int timestep = 1000;
  bool FORWARD = 0;
  bool FORWARD2 = 0;
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
    motors = Motor("left", 35, 37, 69, 67, startPos);
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
  int downPos = 60;
  int upPos = 145;
  Point start = { 0, 0 };
  Point now_position = {0, 0};
  int need = 0;
  Motor motors;
  Sensors sens;
};

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI 51 
#define OLED_CLK  52   
#define OLED_DC   24 
#define OLED_CS   23 
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
  void showText(String text);
  ~OLEDMenu();
  void showMenu();
  void setLastTime(uint64_t timer);
private:
  Adafruit_SSD1306 *display;
  int upBtn, downBtn, selectBtn;
  int selected;
  int modeSelected = -1;
  uint64_t lastTime;
  String *modes;
  int modeCount;

  void showSelected();
};