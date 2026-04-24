#include "screenMacros.h"

void showBootScreen(LiquidCrystal_I2C &lcd)
{
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print("OH7DNE");

  lcd.setCursor(3, 1);
  lcd.print("Null Radio");

  delay(2000);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("AM Transmitter");

  lcd.setCursor(1, 1);
  lcd.print("Starting...");
}

void showErrorScreen(LiquidCrystal_I2C &lcd)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Si5351 Missing");

  lcd.setCursor(0, 1);
  lcd.print("Retrying...");
}

void updateDisplay(LiquidCrystal_I2C &lcd, uint64_t carrierFreq)
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Carrier Freq:");

  lcd.setCursor(0, 1);

  float mhz = carrierFreq / 1000000.0;
  lcd.print(mhz, 3);
  lcd.print(" MHz");
}