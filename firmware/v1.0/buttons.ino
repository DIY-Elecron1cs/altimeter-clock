bool click(uint8_t pin) {   //быстрый клик. Используется для изменения настроек ШИМ
  static uint32_t timer;
  if (digitalRead(pin) == LOW && millis() - timer > 100) {
    timer = millis();
    return true;
  }
  else {
    return false;
  }
}

bool cansel() {             //нажатие кнопки OK вместе с любой другой. Приводит к возврату на начальный экран
  static uint32_t timer;
  if (digitalRead(OK) == LOW && (digitalRead(LEFT) == LOW || digitalRead(RIGHT) == LOW  || digitalRead(UP) == LOW || digitalRead(DOWN) == LOW) && millis() - timer > 80) {
    timer = millis();
    return (true);
  }
  else {
    return (false);
  }
}
