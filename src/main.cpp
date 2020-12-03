#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(F("Hello, Meow!"));
  lcd.setCursor(0, 1);
  lcd.print(F("Meow meow meow!"));
}

void loop() {
  // put your main code here, to run repeatedly:
}