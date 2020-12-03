#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PERIOD 1000

LiquidCrystal_I2C lcd(0x27, 20, 4);
uint32_t timer = 0;
bool dotFlag;

uint8_t A[8] = { 0b00011, 0b01111, 0b01111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
uint8_t B[8] = { 0b11000, 0b11110, 0b11110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
uint8_t C[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000 };
uint8_t D[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
uint8_t E[8] = { 0b11111, 0b01111, 0b01111, 0b00011, 0b00000, 0b00000, 0b00000, 0b00000 };
uint8_t F[8] = { 0b11111, 0b11110, 0b11110, 0b11000, 0b00000, 0b00000, 0b00000, 0b00000 };
uint8_t G[8] = { 0b00011, 0b01111, 0b01111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000 };
uint8_t H[8] = { 0b11000, 0b11110, 0b11110, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000 };

// uint8_t A[8] = { 0b00011, 0b00111, 0b01111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
// uint8_t B[8] = { 0b11000, 0b11100, 0b11110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
// uint8_t C[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000 };
// uint8_t D[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
// uint8_t E[8] = { 0b11111, 0b01111, 0b00111, 0b00011, 0b00000, 0b00000, 0b00000, 0b00000 };
// uint8_t F[8] = { 0b11111, 0b11110, 0b11100, 0b11000, 0b00000, 0b00000, 0b00000, 0b00000 };
// uint8_t G[8] = { 0b00011, 0b01111, 0b01111, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000 };
// uint8_t H[8] = { 0b11000, 0b11110, 0b11110, 0b11111, 0b00000, 0b00000, 0b00000, 0b00000 };

// uint8_t A[8] = { 0b00011, 0b01111, 0b01111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
// uint8_t B[8] = { 0b11000, 0b11110, 0b11110, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
// uint8_t C[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000 };
// uint8_t D[8] = { 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111 };
// uint8_t E[8] = { 0b11111, 0b11111, 0b01111, 0b01111, 0b00011, 0b00000, 0b00000, 0b00000 };
// uint8_t F[8] = { 0b11111, 0b11111, 0b11110, 0b11110, 0b11000, 0b00000, 0b00000, 0b00000 };
// uint8_t G[8] = { 0b00011, 0b01111, 0b01111, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000 };
// uint8_t H[8] = { 0b11000, 0b11110, 0b11110, 0b11111, 0b11111, 0b00000, 0b00000, 0b00000 };

void loadClock() {
  lcd.createChar(0, A);
  lcd.createChar(1, B);
  lcd.createChar(2, C);
  lcd.createChar(3, D);
  lcd.createChar(4, E);
  lcd.createChar(5, F);
  lcd.createChar(6, G);
  lcd.createChar(7, H);
}

void printZeroAt(uint8_t position) {
  lcd.setCursor(position, 0); 
  lcd.write(0); 
  lcd.write(2);  
  lcd.write(1);
  lcd.setCursor(position, 1);
  lcd.write(3);
  lcd.setCursor(position + 2, 1);
  lcd.write(3);
  lcd.setCursor(position, 2);
  lcd.write(4);
  lcd.write(2); 
  lcd.write(5);
}

void printOneAt(uint8_t position) {
  lcd.setCursor(position, 0); 
  lcd.write(6); 
  lcd.write(3);  
  lcd.setCursor(position + 1, 1);
  lcd.write(3);
  lcd.setCursor(position, 2);
  lcd.write(2); 
  lcd.write(2); 
  lcd.write(2); 
}

void printTwoAt(uint8_t position) {
  lcd.setCursor(position, 0); 
  lcd.write(6); 
  lcd.write(2);  
  lcd.write(1);
  lcd.setCursor(position, 1);
  lcd.write(0);
  lcd.write(2);
  lcd.write(5);
  lcd.setCursor(position, 2);
  lcd.write(4);
  lcd.write(2); 
  lcd.write(5);
}

void printThreeAt(uint8_t position) {
  lcd.setCursor(position, 0); 
  lcd.write(6); 
  lcd.write(2);  
  lcd.write(1);
  lcd.setCursor(position + 1, 1);
  lcd.write(2); 
  lcd.write(3);
  lcd.setCursor(position, 2);
  lcd.write(4);
  lcd.write(2); 
  lcd.write(5);
}

void printFourAt(uint8_t position) {
  lcd.setCursor(position, 0); 
  lcd.write(3); 
  lcd.setCursor(position + 2, 0);  
  lcd.write(3);
  lcd.setCursor(position, 1);
  lcd.write(4);
  lcd.write(2);
  lcd.write(3);
  lcd.setCursor(position + 2, 2);
  lcd.write(2);
}

void printFiveAt(uint8_t position) {
  lcd.setCursor(position, 0); 
  lcd.write(3);
  lcd.write(2);
  lcd.write(5);
  lcd.setCursor(position, 1);
  lcd.write(2);
  lcd.write(2); 
  lcd.write(1);
  lcd.setCursor(position, 2);
  lcd.write(4);
  lcd.write(2); 
  lcd.write(5);
}

void printDots(bool state) {
  lcd.setCursor(9, 1);
  if (state) {
    lcd.write(2);
  } else {
    lcd.print(F(" "));
  }
  lcd.setCursor(9, 2);
  if (state) {
    lcd.write(2);
  } else {
    lcd.print(F(" "));
  }
}

void setup() {
  lcd.init();
  lcd.backlight();
  loadClock();

  printTwoAt(2);
  printOneAt(5);
  printThreeAt(11);
  printFourAt(14);

  lcd.setCursor(0, 3);
  lcd.print(F("   -17\337C     87%"));
}

void loop() {
  if (millis() - timer >= PERIOD) {
    dotFlag = !dotFlag;
    printDots(dotFlag);
    do {
      timer += PERIOD;
      if (timer < PERIOD) break;  // переполнение uint32_t
    } while (timer < millis() - PERIOD); // защита от пропуска шага
  }
}