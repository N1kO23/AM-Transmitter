#ifndef SCREEN_MACROS_H
#define SCREEN_MACROS_H

#include <LiquidCrystal_I2C.h>
#include <stdint.h>

void showBootScreen(LiquidCrystal_I2C &lcd);
void showErrorScreen(LiquidCrystal_I2C &lcd);
void updateDisplay(LiquidCrystal_I2C &lcd, uint64_t carrierFreq);

#endif