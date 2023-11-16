#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo servoMotor;

void setup() {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Hello, world!"));
  display.display();

  servoMotor.attach(8); // 서보 모터를 8번 핀에 연결
  servoMotor.write(90); // 서보 모터의 초기 각도를 90도로 설정
}

void loop() {
  if (Serial.available() > 0) {
    char inputChar = Serial.read();

    if (inputChar >= '1' && inputChar <= '5') {
      int angle = (inputChar - '0') * 30; // 입력된 숫자에 해당하는 각도 계산 (1-30, 2-60, 3...)
      servoMotor.write(angle); // 서보 모터를 계산한 각도로 회전

      display.clearDisplay();
      display.setCursor(0, 0);
      display.print("Angle: ");
      display.print(angle);
      display.display();
    }
  }
}