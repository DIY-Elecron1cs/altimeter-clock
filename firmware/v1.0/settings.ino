void settings() {

  if (flagSet == false) {
    if (click(DOWN) == true) {
      pointer = pointer + 1;
      if (pointer >= 4) {
        pointer = 4;
      }
    }
    else if (click(UP) == true) {
      pointer = pointer - 1;
      if (pointer <= 0) {
        pointer = 0;
      }
    }
    printPointer(pointer);

    if (pointer == 0 && (click(LEFT) == true || click(RIGHT) == true)) {    //установка комбинированного режима
      combinationFlag = !combinationFlag;
    }

    if (pointer == 1 && (click(LEFT) == true || click(RIGHT) == true)) {    //установка экрана по умолчанию
      defaultMode = !defaultMode;
    }


    if (pointer == 2 && click(LEFT) == true) {          //уменьшение корректировочного значения
      correctAlt = correctAlt - 1;
      if (correctAlt <= -100) {
        correctAlt = -100;
      }
    }
    else if (pointer == 2 && click(RIGHT) == true) {    //увеличение корректировочного значения
      correctAlt = correctAlt + 1;
      if (correctAlt >= 100) {
        correctAlt = 100;
      }
    }

    if (pointer == 3 && (click(LEFT) == true || click(RIGHT) == true)) {  //выход
      flagSet = false;
      settingsFlag = false;
      oled.clear();
      return;
    }
    else if (pointer == 4 && (click(LEFT) == true || click(RIGHT) == true)) {   //выход и сохранение
      flagSet = false;
      settingsFlag = false;
      oled.clear();
      EEPROM_write();
      return;
    }


  }



  oled.home();
  oled.setScale(1);
  oled.setCursor(10, 0);
  oled.print("режим:  ");   //режим (комбинированный/ручной)
  if (combinationFlag == true) oled.print("КОМБ. ");
  else if (combinationFlag == false) oled.print("РУЧН. ");
  oled.setCursor(10, 1);    //экран по умолчанию
  oled.print("по умолч.:  ");
  if (defaultMode == TIME) oled.print("TIME  ");
  else if (defaultMode == METEO) oled.print("METEO  ");
  oled.setCursor(10, 2);    //корректировка высоты
  oled.print("коррект.:  ");
  oled.print(correctAlt * 5);
  oled.print("   ");
  oled.setCursor(10, 3);    //выход
  oled.print("exit");
  oled.setCursor(10, 4);    //выход и сохранение
  oled.print("exit + save");

  oled.setCursor(0, 6); //отображение высоты
  oled.setScale(2);
  oled.print(pressureToAltitude(bme.readPressure()) + (float(correctAlt) * 5.0));
  oled.print(" ");
  oled.setScale(1);
  oled.print("МНУМ   ");
}


void printPointer(uint8_t ptr) {    //рисуем указатель
  oled.setScale(1);
  oled.setCursor(0, ptr);
  oled.print(">");
  oled.setCursor(0, abs(ptr - 1));
  oled.print(" ");
  oled.setCursor(0, ptr + 1);
  oled.print(" ");
}
