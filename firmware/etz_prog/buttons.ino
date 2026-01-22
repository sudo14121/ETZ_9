
/*
void check_y() {
  static bool last_state = 0;
  bool current_state = digitalRead(44);
  if (current_state == 1 && last_state == 0) {
    delay(10);
    y++;
  }
  last_state = current_state;
}*/
void init_x_y() {
  pinMode(18, INPUT_PULLUP);
  //pinMode(44, INPUT_PULLUP);
}