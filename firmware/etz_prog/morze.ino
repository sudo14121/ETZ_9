void input_morze() {
  static bool last_state = digitalRead(DIGIT);
  uint64_t timer = millis();
  uint64_t timer2 = millis();
  int i = 0;
  bool current_state = digitalRead(DIGIT);

  while (!digitalRead(DIGIT))
    ;
  while (millis() - timer2 < 8000) {
    current_state = digitalRead(DIGIT);
    if (i != 0 && current_state == 0 && last_state == 1) {
      if (i != 0) {
        times[i] = millis() - timer;
        Serial.println(times[i]);
        i++;
        timer = millis();
        delay(150);
      }
    }
  
    current_state = digitalRead(DIGIT);
    if (current_state == 1 && last_state == 0) {
      times[i] = millis() - timer;
      timer2 = millis();
      Serial.println(times[i]);
      i += 1;
      timer = millis();
      delay(150);
    }
    last_state = current_state;
    delay(100);
  }

  for (int j = 0; j < (2 * N - 1); j++) {
    if (times[j] != 0 && j % 2 == 0)
      lDot = min(lDot, times[j]);
  }

  Serial.println(lDot);
  for (int i = 0; i < (2 * N - 1); i++) {
    if (times[i] != 0)
      if (times[i] < (lDot + lDot / 2) && i % 2 == 0) {
        input_OPA[i] = ".";
      } else if (times[i] < (lDot + lDot / 2)) {
        input_OPA[i] = " ";
      } else if (i % 2 == 0) {
        input_OPA[i] = "—";
      } else {
        input_OPA[i] = "   ";
      }
  }
}