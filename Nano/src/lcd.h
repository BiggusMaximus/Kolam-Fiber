#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
unsigned long lastSendTime = 0;
int CLEAR_PERIOD = 1000;

void LCDInitialization() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();   
  lcd.print("Initialize LCD");
}

void showDisplay(float pH, float DO, float temp) {
    if (millis() - lastSendTime > CLEAR_PERIOD) {
        lcd.clear();                 // clear display
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
        lcd.print("pH: " + String(pH));        // print message at (0, 0)
        lcd.setCursor(0, 1);         // move cursor to   (2, 1)
        lcd.print("DO: " + String(DO)); // print message at (2, 1)
        lcd.setCursor(8, 0);         // move cursor to   (2, 1)
        lcd.print("Temp: " + String(temp) + " C"); // print message at (2, 1)

        lastSendTime = millis();
    }


}