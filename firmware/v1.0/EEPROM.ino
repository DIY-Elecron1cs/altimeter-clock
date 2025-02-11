void EEPROM_write() {
  EEPROM.write(5, correctAlt);
  EEPROM.write(6, defaultMode);
  EEPROM.write(7, combinationFlag);
}

void EEPROM_reading() {
  correctAlt = EEPROM.read(5);
  defaultMode = EEPROM.read(6);
  combinationFlag = EEPROM.read(7);
}
