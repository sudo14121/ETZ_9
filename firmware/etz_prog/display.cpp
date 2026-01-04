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

  display->setCursor(40, 0);
  display->println(transliterate("РЕЖИМЫ"));

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
  display->print(transliterate("выполняется: "));
  display->println(modes[selected]);
  display->display();
  delay(500);
}

String OLEDMenu::transliterate(String text) {
  text.replace("А", "A");
  text.replace("Б", "B");
  text.replace("В", "V");
  text.replace("Г", "G");
  text.replace("Д", "D");
  text.replace("Е", "E");
  text.replace("Ё", "YO");
  text.replace("Ж", "ZH");
  text.replace("З", "Z");
  text.replace("И", "I");
  text.replace("Й", "J");
  text.replace("К", "K");
  text.replace("Л", "L");
  text.replace("М", "M");
  text.replace("Н", "N");
  text.replace("О", "O");
  text.replace("П", "P");
  text.replace("Р", "R");
  text.replace("С", "S");
  text.replace("Т", "T");
  text.replace("У", "U");
  text.replace("Ф", "F");
  text.replace("Х", "H");
  text.replace("Ц", "C");
  text.replace("Ч", "CH");
  text.replace("Ш", "SH");
  text.replace("Щ", "SH");
  text.replace("Ъ", "'");
  text.replace("Ы", "Y");
  text.replace("Ь", "'");
  text.replace("Э", "E");
  text.replace("Ю", "YU");
  text.replace("Я", "YA");
  text.replace("а", "A");
  text.replace("б", "B");
  text.replace("в", "V");
  text.replace("г", "G");
  text.replace("д", "D");
  text.replace("е", "E");
  text.replace("ё", "YO");
  text.replace("ж", "ZH");
  text.replace("з", "Z");
  text.replace("и", "I");
  text.replace("й", "J");
  text.replace("к", "K");
  text.replace("л", "L");
  text.replace("м", "M");
  text.replace("н", "N");
  text.replace("о", "O");
  text.replace("п", "P");
  text.replace("р", "R");
  text.replace("с", "S");
  text.replace("т", "T");
  text.replace("у", "U");
  text.replace("ф", "F");
  text.replace("х", "H");
  text.replace("ц", "C");
  text.replace("ч", "CH");
  text.replace("ш", "SH");
  text.replace("щ", "SH");
  text.replace("ъ", "'");
  text.replace("ы", "Y");
  text.replace("ь", "'");
  text.replace("э", "E");
  text.replace("ю", "YU");
  text.replace("я", "YA");
  return text;
}