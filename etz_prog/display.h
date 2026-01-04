#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

    display = new Adafruit_SSD1306(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_CS, OLED_RESET);
  }

  void init() {
    pinMode(upBtn, INPUT);
    pinMode(downBtn, INPUT);
    pinMode(selectBtn, INPUT);

    display->begin(SSD1306_SWITCHCAPVCC);
    display->clearDisplay();
    showMenu();
  }

  void update() {
    if (millis() - lastTime < 200)
      return;

    if (!digitalRead(upBtn)) {
      selected--;
      if (selected < 0)
        selected = modeCount - 1;
      showMenu();
      lastTime = millis();
    }

    if (!digitalRead(downBtn)) {
      selected++;
      if (selected >= modeCount)
        selected = 0;
      showMenu();
      lastTime = millis();
    }

    if (!digitalRead(selectBtn)) {
      modeSelected = selected;
      showSelected();
      lastTime = millis();
    }
  }

  int getSelected() {
    int temp = modeSelected;
    modeSelected = -1;
    return temp;
  }

  void showText(String text) {
    display->clearDisplay();
    display->setTextSize(1);
    display->setTextColor(WHITE);
    display->setCursor(0, 0);
    display->println(text);
    display->display();
  }

  ~OLEDMenu() {
    delete[] modes;
    delete display;
  }

private:
  Adafruit_SSD1306 *display;
  int upBtn, downBtn, selectBtn;
  int selected;
  int modeSelected = -1;
  unsigned long lastTime;
  String *modes;
  int modeCount;

  void showMenu() {
    display->clearDisplay();
    display->setTextSize(1);
    display->setTextColor(WHITE);

    display->setCursor(40, 0);
    display->println("РЕЖИМЫ");

    display->setCursor(0, 20);
    display->print("> ");
    display->println(modes[selected]);

    if (selected < modeCount - 1) {
      display->setCursor(0, 35);
      display->print("  ");
      display->println(modes[selected + 1]);
    }

    if (selected > 0) {
      display->setCursor(0, 10);
      display->print("  ");
      display->println(modes[selected - 1]);
    }

    display->display();
  }

  void showSelected() {
    display->clearDisplay();
    display->setTextSize(1);
    display->setCursor(0, 20);
    display->print("Запуск: ");
    display->println(modes[selected]);
    display->display();
    delay(500);
  }
};