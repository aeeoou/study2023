//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);   // 첫번째 줄의 0번째에서 시작
  lcd.print("SEO HYOUNG JONG!");
  lcd.setCursor(0,1); // 두번째 줄의 0번째에서 시작
  lcd.print("   1991 04 09   ");
}


void loop()
{
}
