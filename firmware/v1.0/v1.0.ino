
/*---пины кнопок---*/
#define UP 2
#define DOWN 5
#define LEFT 4
#define RIGHT 3
#define OK 6

/*---режимы---*/
#define TIME 0
#define METEO 1
#define COMBINATION 2
#define SETTINGS 3

#define PERIOD 3000

#define SET_MODE 0
#define SET_DEFAULT 1
#define SET_ALTITUDE 2
#define SET_CANCEL 3

#define MIN_BAT 634
#define MAX_BAT 820

#define DEBUG_BAT 0

/*---библиотеки---*/
#include <Wire.h>
#include <RTClib.h>
#include <GyverOLED.h>
#include <GyverBME280.h>
#include <EEPROM.h>

/*---объекты---*/
RTC_DS3231 rtc;
GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
GyverBME280 bme;

char daysOfTheWeek[7][12] = { "ВС", "ПН", "ВТ", "СР", "ЧТ", "ПТ", "СБ" };

bool light = false;
bool sleep = false;
bool defaultMode;
bool mode;
bool settingsFlag = false;
bool combinationFlag = false;
int correctAlt;

static bool flagSet = false;
uint8_t set_mode = SET_MODE;
int pointer = 0;

int inp;
int battery;
uint32_t bat_timer;

byte grad[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};


void setup() {
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(OK, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(12, HIGH);
  oled.init();
  oled.clear();

  bme.setMode(NORMAL_MODE);
  bme.begin();

#if DEBUG_BAT == 1
  Serial.begin(9600);
#endif

  EEPROM_reading();
  mode = defaultMode;
}

void loop() {
  if (settingsFlag == false) {
    if (sleep == false && light == false) {
      if (combinationFlag == false) {
        if (mode == TIME) {
          dispData();
        }
        else if (mode == METEO) {
          dispMeteo();
        }
        if (click(LEFT) || click(RIGHT)) {
          oled.clear();
          mode = !mode;
        }
      }
      else if (combinationFlag == true) {
        static uint32_t timer;
        if (millis() - timer >= PERIOD) {
          timer = millis();
          mode = !mode;
          oled.clear();
        }
        if (mode == TIME) {
          dispData();
        }
        else if (mode == METEO) {
          dispMeteo();
        }
      }
    }
    else if (sleep == true && light == false) {
      sleep_mode();
    }
    else if (light == true && sleep == false) {
      light_mode();
    }
    else if (light == true && sleep == true) {
      sleep = false;
      light = false;
    }
  }
  else {
    settings();
  }
  if (click(OK)) {
    oled.clear();
    settingsFlag = true;
  }
  if (settingsFlag == false) {
    if (click(UP) == true) {
      oled.clear();
      sleep = !sleep;
    }
    else if (click(DOWN) == true) {
      oled.clear();
      light = !light;
    }
  }
}

void dispData() {
  DateTime now = rtc.now();
  String len1 = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  String len2 = String(now.day()) + "." + String(now.month()) + "." + String(now.year()) + " (" + String(daysOfTheWeek[now.dayOfTheWeek()]) + ")";
  oled.setCursor(int((128 - (len1.length() * 10)) / 2) - 20, 0);
  oled.setScale(2);
  oled.print(" ");
  oled.print(len1);
  oled.print("   ");
  oled.setCursor(int((128 - (len2.length() * 5)) / 2) - 12, 5);
  oled.setScale(1);
  oled.print("  ");
  oled.print(len2);
  oled.print("  ");
  if (millis() - bat_timer >= 300) {
    bat_timer = millis();
    draw_battery();
  }
}

void sleep_mode() {
  DateTime now = rtc.now();
  String len1 = String(now.hour()) + ":" + String(now.minute());
  oled.setCursorXY(int((128 - (len1.length() * 15)) / 2) - 25, 20);
  oled.setScale(3);
  oled.print(" ");
  oled.print(len1);
  oled.print("   ");
  if (click(LEFT) == true || click(RIGHT) == true) {
    oled.clear();
    sleep = false;
  }
}

void light_mode() {
  oled.fill(0b11111111);
  if (click(LEFT) == true || click(RIGHT) == true) {
    oled.clear();
    light = false;
  }
}

void dispMeteo() {
  oled.setCursor(0, 0); //отображение высоты
  oled.setScale(2);
  oled.print(pressureToAltitude(bme.readPressure()) + (float(correctAlt) * 5.0));
  oled.print(" ");
  oled.setScale(1);
  oled.print("МНУМ   ");
  oled.setScale(1);     //отображение температуры
  oled.setCursor(0, 3);
  oled.print("t: ");
  oled.print(bme.readTemperature());
  oled.print(" ");
  oled.drawByte(0b00000110);
  oled.drawByte(0b00001001);
  oled.drawByte(0b00001001);
  oled.drawByte(0b00000110);
  oled.drawByte(0b00000000);
  oled.print("C ");
  oled.setCursor(0, 5); //отображение влажности
  oled.print("h: ");
  oled.print(bme.readHumidity());
  oled.print(" % ");
  oled.setCursor(0, 7); //отображение давление
  oled.print("p: ");
  oled.print(pressureToMmHg(bme.readPressure()));
  oled.print(" мм.рт.ст.");
}

void draw_battery() {

  //inp = (int)(analogRead(A0) + 5);
  inp = analogRead(A0);

#if DEBUG_BAT == 1
  Serial.println(inp);
#endif

  if (inp < MIN_BAT) {
    battery = 0;
  }
  else if (inp > MAX_BAT) {
    battery = 100;
  }
  else if (inp >= MIN_BAT && inp <= MAX_BAT) {
    battery = map(inp, MIN_BAT, MAX_BAT, 0, 100);
  }
  oled.setScale(1);

  oled.setCursor(41, 7);


  oled.drawByte(0b11111111);
  if (map(battery, 0, 100, 0, 10) == 0) {
    for (int i = 0; i < 10; i++) {
      oled.drawByte(0b10000001);
    }
  }
  else if (map(battery, 0, 100, 0, 10) == 100) {
    for (int i = 0; i < 10; i++) {
      oled.drawByte(0b11111111);
    }
  }
  else {
    for (int i = 0; i < map(battery, 0, 100, 0, 10); i++) {
      oled.drawByte(0b11111111);
    }
    for (int i = 0; i < 10 - map(battery, 0, 100, 0, 10); i++) {
      oled.drawByte(0b10000001);
    }
  }
  oled.drawByte(0b11111111);
  oled.drawByte(0b00111100);
  oled.drawByte(0b00111100);
  if (battery < 10) {
    oled.print("   ");
  }
  else if (battery >= 10 && battery < 100) {
    oled.print("  ");
  }
  else if (battery >= 100) {
    oled.print(" ");
  }
  oled.print(battery);
  oled.print("%      ");
}
