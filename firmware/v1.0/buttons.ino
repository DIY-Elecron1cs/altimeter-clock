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
