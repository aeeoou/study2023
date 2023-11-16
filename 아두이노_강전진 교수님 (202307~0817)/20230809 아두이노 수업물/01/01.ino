#include <Wire.h>   // I2C통신을 사용하기 때문에 아두이노의 I2C 통신용  라이브러리가 필요
#include <Adafruit_GFX.h>   // Adafruit의 그래픽 관련 라이브러리
#include <Adafruit_SSD1306.h>   // SSD1306 제어용 라이브러리
#include <DHT11.h>

#define DHTPIN 4

#define SCREEN_WIDTH 128   // OLED 디스플레이의 가로 픽셀수
#define SCREEN_HEIGHT 64   // OLED 디스플레이의 세로 픽셀수
#define OLED_RESET 4   // 리셋핀이 있는 OLDE의 리셋핀에 연결할 아두이노의 핀 번호

DHT11 dht(A0);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  float temp, humi; 
  int result = dht.read(humi, temp);
  if (result == 0)  /* 온습도가 잘측정이되서 result변수에 0이라는 값이 들어오면 

                       if문이 실행됩니다.

                    */ 
  {
    Serial.print("temperature:"); 
    Serial.print(temp); //온도값이 출력됩니다.

    Serial.print(" humidity:");
    Serial.print(humi); //습도값이 출력됩니다.

    Serial.println();
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(F("Temperature: "));
  display.print(temp);
  display.println(F(" *C"));
  display.display();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 40);
    display.print(F("Humidity: "));
    display.print(humi);
    display.println(F(" *C"));
    display.disaply();

    display.display();
    display.clearDisplay();
  delay(2000);
}