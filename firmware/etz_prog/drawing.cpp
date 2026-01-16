#include "allclass.h"

void Paint::initServo() {
  brush.attach(SERVO);
  brush.write(upPos);
  delay(500);
}

void Paint::initYStepper() {
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
}

void Paint::initDrive() {
  motors.StepperInit();
}

void Paint::initSens() {
  sens = Sensors(56, 54);
}

void Paint::downBrush() {
  brush.write(downPos);
  delay(500);
}

void Paint::upBrush() {
  brush.write(upPos);
  delay(500);
}

void Paint::drawLine(Point start, Point finish, int speed) {
  now_position = motors.getPos();
  if (start.x < now_position.x) {
    motors.goToPoint(finish, speed);
    downBrush();
    motors.goToPoint(start, speed);
    upBrush();
  } else {
    {
      motors.goToPoint(start, speed);
      downBrush();
      motors.goToPoint(finish, speed);
      upBrush();
    }
  }
}

void Paint::drawDot(Point pos, int speed) {
  motors.goToPoint(pos, speed);

  downBrush();
  upBrush();
}

void Paint::drawLines(Point pos, int lenLine, int lenBetweenLines, int countLines, int speed) {
  for (int i = 0; i < countLines; i++) {
    drawLine(pos, { pos.x + lenLine, 0 }, speed);
    pos = { motors.getPos().x + lenBetweenLines, 0 };
  }
}

void Paint::drawDots(Point pos, int lenBetweenDots, int countDots, int speed) {
  for (int i = 0; i < countDots; i++) {
    drawDot(pos, speed);
    pos = { motors.getPos().x + lenBetweenDots, 0 };
  }
}

void Paint::goingStartPos(int speed) {
  int plus = 1;
  while (!sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }
  /*while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }*/
  motors.setStart({ 0, 0 });
  motors.goToPoint({ 21, 0 }, 2000);
  motors.setStart({ -need, 0 });
}

void Paint::backzone(int speed) {
  while (!sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x - 1, 0 }, speed);
    sens.newpos();
  }
  motors.goToPoint({ -need - 52, 0 }, speed);
}

void Paint::calibr() {
  sens.calibr(motors);
  Serial.println(EEPROM.read(0) * 4);
  Serial.println(EEPROM.read(1) * 4);
  motors.goToPoint({ 0, 0 }, 5000);
}

void Paint::testsens() {
  sens.newpos();
}
void Paint::drawMorze(char letter, Point start_pos, float lenLine, float lenBetween, float speed) {
  char* code;

  switch (letter) {
    case 'S': code = "..."; break;
    case 'А': code = ".-"; break;
    case 'Б': code = "-..."; break;
    case 'В': code = ".--"; break;
    case 'Г': code = "--."; break;
    case 'Д': code = "-.."; break;
    case 'Е': code = "."; break;
    case 'Ё': code = "."; break;
    case 'Ж': code = "...-"; break;
    case 'З': code = "--.."; break;
    case 'И': code = ".."; break;
    case 'Й': code = ".---"; break;
    case 'К': code = "-.-"; break;
    case 'Л': code = ".-.."; break;
    case 'М': code = "--"; break;
    case 'Н': code = "-."; break;
    case 'О': code = "---"; break;
    case 'П': code = ".--."; break;
    case 'Р': code = ".-."; break;
    case 'С': code = "..."; break;
    case 'Т': code = "-"; break;
    case 'У': code = "..-"; break;
    case 'Ф': code = "..-."; break;
    case 'Х': code = "...."; break;
    case 'Ц': code = "-.-."; break;
    case 'Ч': code = "---."; break;
    case 'Ш': code = "----"; break;
    case 'Щ': code = "--.-"; break;
    case 'Ъ': code = "--.--"; break;
    case 'Ы': code = "-.--"; break;
    case 'Ь': code = "-..-"; break;
    case 'Э': code = "..-.."; break;
    case 'Ю': code = "..--"; break;
    case 'Я': code = ".-.-"; break;
    case '0': code = "-----"; break;
    case '1': code = ".----"; break;
    case '2': code = "..---"; break;
    case '3': code = "...--"; break;
    case '4': code = "....-"; break;
    case '5': code = "....."; break;
    case '6': code = "-...."; break;
    case '7': code = "--..."; break;
    case '8': code = "---.."; break;
    case '9': code = "----."; break;
  }

  Point position = start_pos;
  Point end_pos = position;

  for (int i = 0; code[i] != '\0'; i++) {
    char simbol = code[i];
    if (simbol == '.') {
      end_pos = { position.x + (lenLine / 3), position.y };
      drawLine(position, end_pos, speed);
      position.x = end_pos.x + lenBetween;
    } else if (simbol == '-') {
      Point end_pos = { position.x + lenLine, position.y };
      drawLine(position, end_pos, speed);
      position.x = end_pos.x + lenBetween;
    }
  }
}