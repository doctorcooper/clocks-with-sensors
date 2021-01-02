#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <Adafruit_BME280.h>
#include "digits.h"

#define PERIOD 1000                 // Частота опроса времени
#define SENSOR_PERIOD 60000         // Частота опроса датчиков(1 минута)
#define BME_ADDRESS 0x76            // Адрес i2c модуля датчиков
#define RESET_CLOCK 0               // Флаг для подстройки часов при прошивке

LiquidCrystal_I2C lcd(0x27, 20, 4); // Дисплей
RTC_DS3231 rtc;                     // Часы
Adafruit_BME280 bme;                // Датчик

uint32_t timer = 0;                 // Таймер для времени
uint32_t sensorTimer = 0;           // Таймер для датчиков
DateTime now;                       // Время
uint8_t seconds, minutes, hours;    // Переменные для хранения времени
bool dotFlag;                       // Флаг для точек

// Опрос модуля часов и сохранение в память
void readClock() {
  now = rtc.now();
  seconds = now.second();
  minutes = now.minute();
  hours = now.hour();
}

// Опрос датчиков и вывод на дисплей
void drawSensor() {
  bme.takeForcedMeasurement();
  String temperature = String(bme.readTemperature(), 1);
  String humidity = String(bme.readHumidity(), 1);

  lcd.setCursor(0, 3);
  for (uint8_t i = 0; i < 22; i++) {
    lcd.print(F(" "));              // Очистка нижней строки
  }
  
  lcd.setCursor(0, 3);              // Вывод инфо с датчиков
  lcd.print(F("  "));
  lcd.print(temperature);
  lcd.print(F("\337C"));
  lcd.print(F("   "));
  lcd.print(humidity);
  lcd.print(F("%"));
}
 
// Обработка часов по таймеру
void clockTick() {
  if (millis() - timer >= PERIOD) {
    dotFlag = !dotFlag;
    printDots(&lcd, dotFlag);

    seconds++;
    if (seconds > 59) {
      seconds = 0;
      minutes++;
      if(minutes <= 59) {
        drawClocks(&lcd, hours, minutes);
      }
    }
    if (minutes > 59) {
      readClock();
      drawClocks(&lcd, hours, minutes);
      if (hours > 23) {
        hours = 0;
      }
    }

    do {
      timer += PERIOD;
      if (timer < PERIOD) break;  // переполнение uint32_t
    } while (timer < millis() - PERIOD); // защита от пропуска шага
  }
}

// Обработка датчиков по таймеру
void sensorsTick() {
  if (millis() - sensorTimer >= SENSOR_PERIOD) {
    drawSensor();
    do {
      sensorTimer += SENSOR_PERIOD;
      if (sensorTimer < SENSOR_PERIOD) break;  // переполнение uint32_t
    } while (sensorTimer < millis() - SENSOR_PERIOD); // защита от пропуска шага
  }
}

void setup() {
  Serial.begin(9600);
  rtc.begin();
  bme.begin(BME_ADDRESS, &Wire);
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF);
  lcd.init();
  lcd.backlight();
  loadFont(&lcd);

  if (RESET_CLOCK || rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  readClock();
  drawClocks(&lcd, hours, minutes);
  drawSensor();  
}

void loop() {
  clockTick();
  sensorsTick();
}