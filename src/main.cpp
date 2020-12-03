#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "digits.h"

#define PERIOD 1000

LiquidCrystal_I2C lcd(0x27, 20, 4);
uint32_t timer = 0; // Таймер для времени
int8_t dminutes = 0; // Единицы минут
bool dotFlag;

void setup() {
  lcd.init();
  lcd.backlight();
  loadFont(&lcd);

  printDigitAt(&lcd, 2, 0);
  printDigitAt(&lcd, 3, 1);
  printDigitAt(&lcd, 0, 2);
  printDigitAt(&lcd, 0, 3);

  lcd.setCursor(0, 3);
  lcd.print(F("   -17\337C     87%")); // TODO : Вывод инфо с датчика
}

void loop() {
  static uint8_t minutes = 0;
  
  if (millis() - timer >= PERIOD) {
    dotFlag = !dotFlag;
    printDots(&lcd, dotFlag);

    if (minutes > 59) {
      minutes = 0;
    }

    dminutes = minutes % 10;
    if (dminutes == 0) { // Если единицы минут == 0, перерисовывем десятки минут
        printDigitAt(&lcd, (minutes / 10), 2);
    }
    printDigitAt(&lcd, dminutes, 3);
    minutes++;

    do {
      timer += PERIOD;
      if (timer < PERIOD) break;  // переполнение uint32_t
    } while (timer < millis() - PERIOD); // защита от пропуска шага
  }
}