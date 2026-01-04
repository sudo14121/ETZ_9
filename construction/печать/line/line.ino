void init_button() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}
void calibr() {
  int whiteL = 1023, whiteR = 1023, blackL = 0, blackR = 0;
  uint32_t timer = millis();
  while (millis() - timer < 3000) {
    motorRPM(-V / 1.5, V / 1.5);
    sensL = analogRead(SENS_L);
    sensR = analogRead(SENS_R);

    if (sensL < whiteL) {
      whiteL = sensL;
    } if (sensL > blackL) {
      blackL = sensL;
    }

    if (sensR < whiteR) {
      whiteR = sensR;
    } if (sensR > blackR) {
      blackR = sensR;
    }
  }
  grayL = (whiteL + blackL) / 2;
  grayR = (whiteR + blackR) / 2;
  stop_motor();
  EEPROM.write(0, grayL / 4);
  EEPROM.write(1, grayR / 4);
}

void line_to_cross() {
  sensL = analogRead(SENS_L);
  sensR = analogRead(SENS_R);
  while (sensL < grayL || sensR < grayR) {
    sensL = analogRead(SENS_L);
    sensR = analogRead(SENS_R);
    err = sensR - sensL - grayR + grayL;
    u = err * K;
    motorRPM(V + u, V - u);
  }
  motor(0, 0);
}
void line_by_time() {
  uint32_t timer = millis();
  sensL = analogRead(SENS_L);
  sensR = analogRead(SENS_R);
  while (millis() - timer < 320) {
    sensL = analogRead(SENS_L);
    sensR = analogRead(SENS_R);
    err = sensR - sensL - grayR + grayL;
    u = err * K;
    motorRPM(V + u, V - u);
  }
  motor(0, 0);
}

void turnL() {
  motorRPM(-V, V, 700);
  sensL = analogRead(SENS_L);
  sensR = analogRead(SENS_R);
  while (sensR < grayR) {
    sensL = analogRead(SENS_L);
    sensR = analogRead(SENS_R);
    motorRPM(-V, V);
  }
  motorRPM(V, -V, 175);
  stop_motor();
}
void turnR() {
  motorRPM(V, -V, 400);
  sensL = analogRead(SENS_L);
  sensR = analogRead(SENS_R);
  while (sensL < grayL) {
    sensL = analogRead(SENS_L);
    sensR = analogRead(SENS_R);
    motorRPM(V, -V);
  }
  motorRPM(-V, V, 100);
  stop_motor();
}
void move_by_dist(int dist, int vel){
  static int current_dist;
  dist = dist / (2 * PI * RADIUS) * TICKS_PER_ROTATE;
  encL = 0;
  encR = 0;
  while (abs(encL + encR) / 2 < abs(dist)){
    current_dist = encL / TICKS_PER_ROTATE * 2 * PI * RADIUS;
    motorRPM(vel, vel);
  }
  motor(0, 0);
}
void turn(int angle, int vel){
  int dist = angle * GAUGE / RADIUS / 2;
  encL = 0;
  while (abs(encL) < abs(dist)){
    motorRPM(abs(vel) * sign(angle), -abs(vel) * sign(angle));
  }
  stop_motor();
}

int sign(int in){
  return in / abs(in);
}
