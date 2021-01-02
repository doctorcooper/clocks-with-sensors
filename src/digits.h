#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

// Fonts
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

void loadFont(LiquidCrystal_I2C* lcd) {
  lcd->createChar(1, B);
  lcd->createChar(2, C);
  lcd->createChar(0, A);
  lcd->createChar(3, D);
  lcd->createChar(4, E);
  lcd->createChar(5, F);
  lcd->createChar(6, G);
  lcd->createChar(7, H);
}

void clearDigit(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0);
  lcd->print(F("   "));
  lcd->setCursor(position, 1);
  lcd->print(F("   "));
  lcd->setCursor(position, 2);
  lcd->print(F("   "));
}

void printZeroAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(0); 
  lcd->write(2);  
  lcd->write(1);
  lcd->setCursor(position, 1);
  lcd->write(3);
  lcd->setCursor(position + 2, 1);
  lcd->write(3);
  lcd->setCursor(position, 2);
  lcd->write(4);
  lcd->write(2); 
  lcd->write(5);
}

void printOneAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(6); 
  lcd->write(3);  
  lcd->setCursor(position + 1, 1);
  lcd->write(3);
  lcd->setCursor(position, 2);
  lcd->write(2); 
  lcd->write(2); 
  lcd->write(2); 
}

void printTwoAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(6); 
  lcd->write(2);  
  lcd->write(1);
  lcd->setCursor(position, 1);
  lcd->write(0);
  lcd->write(2);
  lcd->write(5);
  lcd->setCursor(position, 2);
  lcd->write(4);
  lcd->write(2); 
  lcd->write(5);
}

void printThreeAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(6); 
  lcd->write(2);  
  lcd->write(1);
  lcd->setCursor(position + 1, 1);
  lcd->write(2); 
  lcd->write(3);
  lcd->setCursor(position, 2);
  lcd->write(4);
  lcd->write(2); 
  lcd->write(5);
}

void printFourAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(3); 
  lcd->setCursor(position + 2, 0);  
  lcd->write(3);
  lcd->setCursor(position, 1);
  lcd->write(4);
  lcd->write(2);
  lcd->write(3);
  lcd->setCursor(position + 2, 2);
  lcd->write(2);
}

void printFiveAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(3);
  lcd->write(2);
  lcd->write(5);
  lcd->setCursor(position, 1);
  lcd->write(2);
  lcd->write(2); 
  lcd->write(1);
  lcd->setCursor(position, 2);
  lcd->write(4);
  lcd->write(2); 
  lcd->write(5);
}

void printSixAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(0); 
  lcd->write(2);  
  lcd->write(7);
  lcd->setCursor(position, 1);
  lcd->write(3);
  lcd->write(2); 
  lcd->write(1);
  lcd->setCursor(position, 2);
  lcd->write(4);
  lcd->write(2); 
  lcd->write(5);
}

void printSevenAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(4);
  lcd->write(2);
  lcd->write(3);
  lcd->setCursor(position + 1, 1);
  lcd->write(0);
  lcd->write(5);
  lcd->setCursor(position + 1, 2);
  lcd->write(2);
}

void printEightAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(0); 
  lcd->write(2);  
  lcd->write(1);
  lcd->setCursor(position, 1);
  lcd->write(3);
  lcd->write(2);
  lcd->write(3);
  lcd->setCursor(position, 2);
  lcd->write(4);
  lcd->write(2); 
  lcd->write(5);
}

void printNineAt(LiquidCrystal_I2C* lcd, uint8_t position) {
  lcd->setCursor(position, 0); 
  lcd->write(0); 
  lcd->write(2);  
  lcd->write(1);
  lcd->setCursor(position, 1);
  lcd->write(4);
  lcd->write(2); 
  lcd->write(3);
  lcd->setCursor(position, 2);
  lcd->write(4);
  lcd->write(2); 
  lcd->write(5);
}

void printDigitAt(LiquidCrystal_I2C* lcd, uint8_t digit, uint8_t position) {
    uint8_t order;
    switch (position)
    {
    case 0: // Смещения для цифр
        order = 2;
        break;
    case 1:
        order = 5;
        break;
    case 2:
        order = 11;
        break;
    case 3:
        order = 14;
        break;
    default:
        break;
    }
    clearDigit(lcd, order);
    switch (digit)
    {
    case 0:
        printZeroAt(lcd, order);
        break;
    case 1:
        printOneAt(lcd, order);
        break;
    case 2:
        printTwoAt(lcd, order);
        break;
    case 3:
        printThreeAt(lcd, order);
        break;
    case 4:
        printFourAt(lcd, order);
        break;
    case 5:
        printFiveAt(lcd, order);
        break;
    case 6:
        printSixAt(lcd, order);
        break;
    case 7:
        printSevenAt(lcd, order);
        break;
    case 8:
        printEightAt(lcd, order);
        break;
    case 9:
        printNineAt(lcd, order);
        break;
    default:
        break;
    }
}

void printDots(LiquidCrystal_I2C* lcd, bool state) {
  lcd->setCursor(9, 1);
  if (state) {
    lcd->write(2);
  } else {
    lcd->print(F(" "));
  }
  lcd->setCursor(9, 2);
  if (state) {
    lcd->write(2);
  } else {
    lcd->print(F(" "));
  }
}

void drawClocks(LiquidCrystal_I2C* lcd, uint8_t hours, uint8_t minutes) {
  if (hours < 10) {
    printDigitAt(lcd, 0, 0);
    printDigitAt(lcd, hours, 1);
  } else {
    uint8_t hour = hours % 10;
    printDigitAt(lcd, hour, 1);
    printDigitAt(lcd, (hours - hour) / 10, 0);
  }

  if (minutes < 10) {
    printDigitAt(lcd, 0, 2);
    printDigitAt(lcd, minutes, 3);
  } else {
    uint8_t minute = minutes % 10;
    printDigitAt(lcd, minute, 3);
    printDigitAt(lcd, (minutes - minute) / 10, 2);
  }
}