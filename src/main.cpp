#include <Wire.h>
#include <si5351.h>
#include <LiquidCrystal_I2C.h>

#define SDA_PIN 6
#define SCL_PIN 7

#define ENC_CLK 2
#define ENC_DT 3

LiquidCrystal_I2C lcd(0x27, 16, 2);
Si5351 si5351;

bool si5351Connected = false;

const uint64_t stepSize = 1000ULL; // 1 kHz steps
int lastCLKState;

unsigned long lastActivityTime = 0;
const unsigned long backlightTimeout = 10000; // 10 seconds
bool backlightOn = true;

// TODO: Add ways to change the carrier frequency and to turn the transmitter on/off.
uint64_t carrierFreq = 6000000ULL; // 6 MHz
bool transmitterOn = true;

void showBootScreen()
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

void showErrorScreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Si5351 Missing");

  lcd.setCursor(0, 1);
  lcd.print("Retrying...");
}

void updateDisplay()
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Carrier Freq:");

  lcd.setCursor(0, 1);

  float mhz = carrierFreq / 1000000.0;
  lcd.print(mhz, 3);
  lcd.print(" MHz");
}

void updateFrequency()
{
  si5351.set_freq(carrierFreq * 100ULL, SI5351_CLK0);
}

bool initSi5351()
{
  if (si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0))
  {
    si5351.set_freq(carrierFreq, SI5351_CLK0);
    si5351.output_enable(SI5351_CLK0, transmitterOn ? 1 : 0);
    return true;
  }
  return false;
}

void setup()
{
  Wire.begin(SDA_PIN, SCL_PIN);

  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lastActivityTime = millis();

  showBootScreen();
  delay(2000);

  lastCLKState = digitalRead(ENC_CLK);
}

void loop()
{
  if (!si5351Connected)
  {
    if (initSi5351())
    {
      si5351Connected = true;
      updateDisplay();
    }
    else
    {
      showErrorScreen();
      delay(2000);
      return;
    }
  }

  int currentCLKState = digitalRead(ENC_CLK);

  if (currentCLKState != lastCLKState && currentCLKState == LOW)
  {

    // Wake LCD if asleep
    if (!backlightOn)
    {
      lcd.backlight();
      backlightOn = true;
    }

    lastActivityTime = millis();

    if (digitalRead(ENC_DT) != currentCLKState)
    {
      carrierFreq += stepSize;
    }
    else
    {
      if (carrierFreq > stepSize)
      {
        carrierFreq -= stepSize;
      }
    }

    updateFrequency();
    updateDisplay();
  }

  lastCLKState = currentCLKState;

  // Turn off backlight after timeout
  if (backlightOn && (millis() - lastActivityTime > backlightTimeout))
  {
    lcd.noBacklight();
    backlightOn = false;
  }
}