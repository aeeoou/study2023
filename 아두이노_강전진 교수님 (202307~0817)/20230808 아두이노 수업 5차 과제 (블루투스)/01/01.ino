#include <SoftwareSerial.h>
#include <Wire.h>               // I2C 통신을 사용하기 위한 라이브러리
#include <Adafruit_GFX.h>       // Adafruit의 그래픽 관련 라이브러리
#include <Adafruit_SSD1306.h>   // SSD1306 제어용 라이브러리
#include <Servo.h>              // 서버모터를 사용하기 위한 라이브러리

#define SCREEN_WIDTH 128        // OLED 디스플레이의 가로 픽셀수
#define SCREEN_HEIGHT 64        // OLED 디스플레이의 세로 픽셀수
#define OLED_RESET 4            // 리셋핀이 있는 OLDE의 리셋핀에 연결할 아두이노의 핀 번호, 리셋핀이 없는 모듈은 임의의 숫자를 넣음

int ledPin1 = 13;               // 빨강색 LED 연결 13번핀
// char order [100];            // 문자열을 저장하기 위한 배열이나 해당 코드에서는 제거해도 무방하다함.
bool led_state = false;         // 빨강색 LED의 상태를 나타내는 불리언 변수. 이 변수는 LED의 on/off 상태를 저장함.

SoftwareSerial BTSerial(2,3);   // 소프트웨어 시리얼 통신을 위한 객체를 생성하는 코드
                                // "SoftwareSerial" 를 사용하여 블루투스 모듈과 아두이노 사이의 시리얼 통신을 설정한다.
                                // "BTSerial" 은 블루투스 모듈과의 통신에 사용되며, BTSerial을 통해 데이터를 보내고 받을 수 있다.

Adafruit_SSD1306 display (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);    // 디스플레이 객체 생성

Servo mysv;                                                                   // Servo 크래스를 사용합니다.

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Serial.begin(9600);
  BTSerial.begin(9600);

  mysv.attach(8);                                     // 서보모터 8번핀에 연결

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);          // 0x3C 주소로 디스플레이 장치 초기화
  display.clearDisplay();                             // 버퍼를 비움
}

void loop()
{
  if (BTSerial.available())             // 블루투스 시리얼 버퍼에 데이터가 있는지 확인
  {
    char command = BTSerial.read();     // 블루투스로부터 한 문자를 읽어서 "command" 변수에 저장.
    //Serial.write(command);
    //Serial.write(BTSerial.read());

    if (command == '0')                 // 블루투스로부터 '0' 이라는 명령을 받았을 때 빨강색 LED를 키거나 끄는 역할을 한다.
    {
      led_state = !led_state;           //
      digitalWrite(13, led_state);      //
    }
    // if(BTSerial.read() == 'l')       //

    else if (command >= '0' && command <= '9')  // "command" 변수가 0~9 사이의 문자인지 확인하고, 해당 문자를 숫자로 변환하여 서보모터의 각도를 제어하는 코드
    {
      int angle = (command - '0') * 20;         // 문자를 숫자로 변환하고 20을 곱하여 각도 값을 계산 (ex: 문자 '1'을 숫자 '1'로 변환 후 20을 곱하여 20도의 각도로 나타냄)
      angle = constrain (angle, 0, 360);        // 계산된 각도 값을 0~360 사이의 각도로 제한한다.
      mysv.write(angle);                        // 계산된 각도 값을 서보모터에 전달하여 모터를 움직인다.
      delay(100);                               // 0.1초 동안의 딜레이를 준다.
    }
  }
  
  if (Serial.available())                       // 시리얼 통신을 통해 받은 데이터를 블루투스 시리얼로 전송하는 부분
  {                                             
    char serialData = Serial.read();            // 시리얼 버퍼에서 데이터를 읽어와 블루투스 시리얼을 통해 전송
    BTSerial.write (serialData);
    /* BTSerial.write (Serial.read());
  }
  
  if (Serial.available()) {
    BTSerial.write(Serial.read()); */
  }

  int analogValue = analogRead(A0);
  int mappedValue = map(analogValue, 0, 1023, 0, 90);

  display.clearDisplay();
  display.setTextSize(1);               // 텍스트 크기를 설정
  display.setTextColor(SSD1306_WHITE);  // 텍스트 색상을 설정
  display.setCursor(0, 0);              // 다음 줄의 시작 위치를 설정 (0,0) 위치부터 텍스트 시작
  display.print("Servo Angle:");        // "Servo Angle" 텍스트를 디스플레이에 출력
  display.setCursor(0, 10);             // 다음 줄의 시작 위치를 설정 (0,10) 위치부터 텍스트 시작
  display.print(mappedValue);           // "mappedValue" 변수에 저장된 서보모터의 각도 값을 출력

  display.setCursor(0, 20);             // 또 다음 줄의 시작 위치를 설정 (0,20) 위치부터 텍스트 시작
  display.print("Servo: ");             // OLED 화면에 "Servo" 텍스트를 출력
  display.print(mysv.read());           // "mysv.read()" 함수를 호출하여 현재 서보모터의 각도 값을 OLED에 출력

  display.display();                    // 디스플레이 버퍼의 내용을 실제 디스플레이에 업데이트

  delay(100);                           // 0.1초 동안 딜레이를 주어 디스플레이가 업데이트되는 동안 일시적으로 대기
  /*
    {
      if(led_state == 0)
      {
      digitalWrite(13, HIGH);
      led_state = 1;
    }
    else
    {
      digitalWrite(13, LOW);
      led_state = 0;
    }

  }
}
  if (Serial.available())
{
  BTSerial.write(Serial.read());
}

mysv.write(map(analogRead(A0), 0, 1023, 0, 90));
delay(100);
*/
}