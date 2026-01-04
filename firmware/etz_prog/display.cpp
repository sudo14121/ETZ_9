#include "allclass.h"

void OLEDMenu::init() {
  pinMode(upBtn, INPUT);
  pinMode(downBtn, INPUT);
  pinMode(selectBtn, INPUT);

  display->begin(SSD1306_SWITCHCAPVCC);
  display->clearDisplay();

  showText("robot redy");
  delay(1000);
  showText("select mode");
}

void OLEDMenu::update() {
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

int OLEDMenu::getSelected() {
  int temp = modeSelected;
  modeSelected = -1;
  return temp;
}

void OLEDMenu::showText(String text) {
  display->clearDisplay();
  display->setTextSize(1);
  display->setTextColor(WHITE);
  display->setCursor(0, 0);
  display->println(text);
  display->display();
}

OLEDMenu::~OLEDMenu() {
  delete[] modes;
  delete display;
}

void OLEDMenu::showMenu() {
  display->clearDisplay();
  display->setTextSize(1);
  display->setTextColor(WHITE);

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

void OLEDMenu::showSelected() {
  display->clearDisplay();
  display->setTextSize(1);
  display->setCursor(0, 20);
  display->print("go: ");
  display->println(modes[selected]);
  display->display();
  delay(500);
}