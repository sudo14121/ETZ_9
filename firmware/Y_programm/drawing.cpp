#include "allclass.h"

//////////////////////////////////////////////////////////////////
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
void Paint::goToPoint(Point point, int speed) {
  now_position = motors.getPos();
  motors.goToPoint(point, speed);
}
void Paint::yCalibration() {
  sens.yCalibr(motors);
  Point p1 = {motors.getPos().x, 0};
  motors.setStart(p1);
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
void Paint::drawCircle(Point centre, int radius, int speed) {
  motors.goToPoint({ centre.x + radius, centre.y }, speed);
  downBrush();

  int y = 0;

  for (int x = radius; x >= -radius; x--) {
    y = sqrt(radius * radius - x * x);
    motors.goToPoint({ centre.x + x, centre.y + y }, speed);
  }

  for (int x = -radius; x <= radius; x++) {
    y = -sqrt(radius * radius - x * x);
    motors.goToPoint({ centre.x + x, centre.y + y }, speed);
  }

  upBrush();
}
void Paint::drawCircleAng(Point centre, int radius, double startAngle, double angleDegrees, int speed) {
  double startRad = startAngle * M_PI / 180.0;
  double angleRad = angleDegrees * M_PI / 180.0;
  double endRad = startRad + angleRad;

  int startX = centre.x + radius * cos(startRad);
  int startY = centre.y + radius * sin(startRad);

  motors.goToPoint({ startX, startY }, speed);
  downBrush();

  for (double angle = startRad; angle <= endRad; angle += 0.02) {
    int x = centre.x + radius * cos(angle);
    int y = centre.y + radius * sin(angle);
    motors.goToPoint({ x, y }, speed);
  }

  upBrush();
}
void Paint::drawMnogo(Point centre, int sides, int lengh, int speed) {
  float radius = lengh / 2 / sin(M_PI / sides);

  double ang = 2 * M_PI / sides;

  motors.goToPoint({ centre.x + radius * cos(0), centre.y + radius * sin(0) }, speed);
  downBrush();

  for (int i = 1; i <= sides; i++) {
    double angle = i * ang;
    motors.goToPoint({ centre.x + radius * cos(angle), centre.y + radius * sin(angle) }, speed);
  }

  upBrush();
}
void Paint::drawTriangle(Point p1, Point p2, Point p3, int speed) {
  motors.goToPoint(p1, speed);
  downBrush();
  motors.goToPoint(p2, speed);
  motors.goToPoint(p3, speed);
  motors.goToPoint(p1, speed);
  upBrush();
}
void Paint::drawRectangle(Point start, int weight, int height, int speed) {
  motors.goToPoint(start, speed);
  downBrush();
  motors.goToPoint({ start.x + weight, start.y }, speed);
  motors.goToPoint({ start.x + weight, start.y - height }, speed);
  motors.goToPoint({ start.x, start.y - height }, speed);
  motors.goToPoint({ start.x, start.y }, speed);
  upBrush();
}
void Paint::drawStar(Point centre, int radius, int points, int speed) {
  double angleStep = 2 * M_PI / points;
  double startAngle = M_PI / 2;
  int x1 = centre.x + radius * cos(startAngle);
  int y1 = centre.y + radius * sin(startAngle);
  int x2 = centre.x + (radius / 2) * cos(startAngle);
  int y2 = centre.y + (radius / 2) * sin(startAngle);

  motors.goToPoint({ x1, y1 }, speed);
  downBrush();
  motors.goToPoint({ x2, y2 }, speed);

  for (int i = 1; i <= points; i++) {
    double angle = startAngle + i * angleStep;
    x1 = centre.x + radius * cos(angle);
    y1 = centre.y + radius * sin(angle);
    angle += angleStep / 2;
    x2 = centre.x + (radius / 2) * cos(angle);
    y2 = centre.y + (radius / 2) * sin(angle);
    motors.goToPoint({ x1, y1 }, speed);
    motors.goToPoint({ x2, y2 }, speed);
  }
  upBrush();
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
  motors.goToPoint({ 11, 0 }, 2000);
  motors.setStart({ -need, 0 });
}
void Paint::goingFirst(int speed) {
  motors.goToPoint({ 50, 0 }, 5000);
  int plus = 1;
  while (!sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }
  while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }
  while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }
  while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }

  int steppps = 0;
  int start = motors.getPos().x;

  motors.goToPoint({ (start + 5) + need + 1, 0 }, 5000);
  downBrush();
  upBrush();

  motors.goToPoint({ 80, 0 }, 5000);
}
void Paint::goingSecond(int speed) {
  motors.goToPoint({ 50, 0 }, 5000);
  int plus = 1;


  while (!sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
  }

  int nach = 0;

  while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
    nach++;
  }
  while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
    nach++;
  }
  while (sens.ishereblack()) {
    motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
    sens.newpos();
    nach++;
  }

  if (nach > 15) {
    motors.goToPoint({ motors.getPos().x + 5 + need, 0 }, speed);
    downBrush();
    upBrush();

    motors.goToPoint({ motors.getPos().x - 32.5, 0 }, speed);
    downBrush();
    upBrush();

  } else {

    while (!sens.ishereblack()) {
      motors.goToPoint({ motors.getPos().x + plus, 0 }, speed);
      sens.newpos();
    }

    motors.goToPoint({ motors.getPos().x + 34.5 + need, 0 }, speed);
    downBrush();
    upBrush();

    motors.goToPoint({ motors.getPos().x + 34, 0 }, speed);
    downBrush();
    upBrush();
  }
  motors.goToPoint({ 80, 0 }, 5000);
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
void Paint::drawMorze(int letter, Point start_pos, float lenLine, float lendot, float lenBetween, float speed) {
  const char* code = "";

  switch (letter) {

    case 10: code = "-----"; break;
    case 1: code = ".----"; break;
    case 2: code = "..---"; break;
    case 3: code = "...--"; break;
    case 4: code = "....-"; break;
    case 5: code = "....."; break;
    case 6: code = "-...."; break;
    case 7: code = "--..."; break;
    case 8: code = "---.."; break;
    case 9:
      code = "----.";
      break;
      /*
    case 'A': code = ".-"; break;
    case 'B': code = "-..."; break;
    case 'C': code = "-.-."; break;
    case 'D': code = "-.."; break;
    case 'E': code = "."; break;
    case 'F': code = "..-."; break;
    case 'G': code = "--."; break;
    case 'H': code = "...."; break;
    case 'I': code = ".."; break;
    case 'J': code = ".---"; break;
    case 'K': code = "-.-"; break;
    case 'L': code = ".-.."; break;
    case 'M': code = "--"; break;
    case 'N': code = "-."; break;
    case 'O': code = "---"; break;
    case 'P': code = ".--."; break;
    case 'Q': code = "--.-"; break;
    case 'R': code = ".-."; break;
    case 'S': code = "..."; break;
    case 'T': code = "-"; break;
    case 'U': code = "..-"; break;
    case 'V': code = "...-"; break;
    case 'W': code = ".--"; break;
    case 'X': code = "-..-"; break;
    case 'Y': code = "-.--"; break;
    case 'Z': code = "--.."; break;*/
  }

  Point position = start_pos;
  Point end_pos = position;

  for (int i = 0; code[i] != '\0'; i++) {
    char simbol = code[i];
    if (simbol == '.') {
      end_pos = { (int)(position.x + (lendot)), position.y };
      drawLine(position, end_pos, speed);
      position.x = end_pos.x + lenBetween;
    } else if (simbol == '-') {
      Point end_pos = { (int)(position.x + lenLine), position.y };
      drawLine(position, end_pos, speed);
      position.x = end_pos.x + lenBetween;
    }
  }
}
/*  case 'А': code = ".-"; break;
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
    case 'Я': code = ".-.-"; break;*/