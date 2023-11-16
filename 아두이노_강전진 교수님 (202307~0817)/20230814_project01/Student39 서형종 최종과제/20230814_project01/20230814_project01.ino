#include <Wire.h>                         // 아두이노 보드에서 I2C 통신을 수행하는데 사용되는 라이브러리
#include <LiquidCrystal_I2C.h>
#include <Servo.h>                        // 서보모터 라이브러리 사용
#include <Adafruit_GFX.h>                 // Adafruit의 그래픽 관련 라이브러리
#include <Adafruit_SSD1306.h>             // SSD1306 제어용 라이브러리

#define TRIG 9            // 초음파 보내는 TRIG 핀 설정
#define ECHO 8            // 초음파 받는 ECHO 핀 설정
#define SCREEN_WIDTH 128  // OLED 디스플레이의 가로 픽셀수
#define SCREEN_HEIGHT 64  // OLED 디스플레이의 세로 픽셀수
#define OLED_RESET 4      // OLED 4번 핀

Adafruit_SSD1306 display (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 0x3C);    // 디스플레이 객체 생성
LiquidCrystal_I2C lcd(0x27, 16, 2);                                                 // 0x3F I2C 주소를 가지고 있는 16x2 LCD 객체를 생성 (I2C 주소는 LCD에 맞게 수정해야함)
Servo mysv;     

int red = 10;             // RGB 빨강색 10번 핀
int green = 11;           // RGB 초록색 11번 핀
int blue = 12;            // RGB 파랑색 12번 핀

void setup()
{
  Serial.begin(9600);               // PC모니터로 센서 값을 확인하기 위해서 시리얼 통신을 정의함
  pinMode(TRIG, OUTPUT);            // 초음파 TRI핀
  pinMode(ECHO, INPUT);             // 초음파 ECHO핀

  pinMode(red, OUTPUT);             // RGB LED - Red 핀을 OUTPUT으로 설정
  pinMode(green, OUTPUT);           // RGB LED - Green 핀을 OUTPUT으로 설정
  pinMode(blue, OUTPUT);            // RGB LED - Blue 핀을 OUTPUT으로 설정

  //pinMode(2, OUTPUT);               // LED핀 OUTPUT으로 설정
  //pinMode(3, OUTPUT);               // LED핀 OUTPUT으로 설정


  lcd.init();                       // I2C LCD를 초기화
  lcd.backlight();                  // I2C LCD의 백라이트를 킨다.

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  pinMode(13, OUTPUT);                // 수동부저 연결 13번

  mysv.attach(7);                     // 서보모터 연결 7번
  mysv.write(0);                      // 서보모터 초기 각도
}

void loop()
{
  long duration, distance;

  digitalWrite(TRIG, LOW);    
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  digitalWrite(13, LOW);                                 // 초기 상태에서 부저를 끈다.

  duration = pulseIn(ECHO, HIGH);                        // 물체에 반사되어 돌아온 초음파의 시간을 변수에 저장

  distance = duration * 17 / 1000;
  // 34,000*초음파가 물체로부터 반사되어 돌아오는 시간 / 1,000,000 / 2 (왕복 값이 아니라 편도 값이기 때문에 나누기 2를 한다)
  // 초음파센서의 거리 값이 위 계산과 동일하게 cm로 환산되는 계산 공식

  Serial.println(duration );                             // 초음파가 반사되어 돌아오는 시간을 보여줌
  Serial.print("\nDIstance : ");
  Serial.print(distance);                                // 측정된 물체로부터 거리 값(cm값)을 보여줌
  Serial.println(" cm");             
  delay(100);                                            // 1초마다 측정 값을 보여줌

  display.clearDisplay();                  
  display.setTextSize(2);                  // 글씨 사이즈
  display.setTextColor(SSD1306_WHITE);     
  display.setCursor(0, 0);                 // I2C OLED LCD 모듈
  display.print("Height: ");               // I2C OLED LCD 모듈
  display.setCursor(0, 40);                // 두번째 문구 시작점, 픽셀수로 설정함 (0~128픽셀)
  display.print(distance);                 // 측정한 거리 값
  display.println(" cm");                  // 측정한 거리 값 + cm
  display.display();                       

  
  if (distance > 70 && distance <= 110)        // 측정 거리 70~110cm 사이면 방에 들어올 수 없다.
  {
    digitalWrite(red, HIGH);                   // 70cm 이상, 110cm 이하 일 때 RGB 빨강 LED 점등
    digitalWrite(green, LOW);                  // * 초음파 센서를 높이 230cm에 설치하였기 때문에 측정 거리 수치를 70~110cm 로 설정
    digitalWrite(blue, LOW);

    tone(13, 500);                             // 70cm 이상, 110cm 이하 일 때 부저 On

    lcd.setCursor(0, 0);
    lcd.print(" Hey! you can't ");             // 70~110cm 사이 일 때 "Hey! you can't come in!" 문구를 출력하여 방에 들어올 수 없음을 나타냄
    lcd.setCursor(0, 1);
    lcd.print("    come in!    ");

    mysv.write(180);                            // 70cm 이상, 110cm 이하 일 때 서보모터 각도 70도로 설정

    delay(1000);

  } else if (distance > 0 && distance <= 70) {  // 측정 거리 0~70cm 사이면 방에 들어올 수 있다.
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);           // 0~70cm 사이일 때 RGB 초록 RED 점등
    digitalWrite(blue, LOW);             // * 초음파 센서를 높이 230cm에 설치하였기 때문에 측정 거리 수치를 0~70cm 로 설정

    lcd.setCursor(0, 0);
    lcd.print("                     ");
    lcd.setCursor(0, 1);
    lcd.print("you can come in!");       // 0~70cm 사이 일 때 "you can come in!" 문구를 출력하여 방에 들어올 수 있음을 나타냄

    mysv.write(-40);                     // 0~70cm 사이일 때 서보모터 각도 -40도로 설정

    noTone(13);                          // 0~70cm 사이일 때 부저 Off

  } 
    if (distance > 110)                  // 측정 거리 110cm 이상이어도 방에 들어올 수 있다.
    {
    digitalWrite(red, LOW);                 
    digitalWrite(green, LOW); 
    digitalWrite(blue, HIGH);            // 110cm 이상일 때 RGB 파랑 LED 점등

    lcd.setCursor(0, 0);
    lcd.print("      Long      ");       // 초음파 센서에 아무 감지를 못하면 항상 110cm 이상의 수치이므로 "long in the room!" 문구를 상시 출력한다.
    lcd.setCursor(0, 1);
    lcd.print("  in the room!  ");

    mysv.write(-40);                     // 110cm 이상일 때 서보모터 각도 40도로 설정

    noTone(13);                          // 110cm 이상일 때 부저 Off
  }
  delay(100);
}