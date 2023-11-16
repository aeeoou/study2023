#include <LedControl.h>                      // LedControl 헥사파일을 선언

LedControl Dote = LedControl(7, 6, 5, 1);    // 모듈핀 위치 설정 ( DIN , CLK , CS , 몇번째 모듈)

const int buttonPin = 2; // 스위치 연결 번호

int buttonPushCounter = 0;   // 버튼이 눌린 횟수를 저장하는 변수 (이 변수는 버튼이 눌릴 때마다 증가되며 초기 값은 0으로 설정)
int buttonState = 0;         // 현재 버튼의 상태를 나타내는 변수 (버튼이 눌렸을 때 값이 변경되며 주로 디지털 입력 핀의 값을 읽어서 버튼 상태를 판단하는데 사용)
int lastButtonState = 0;     // 이전 버튼의 상태를 저장하는 변수 (버튼의 상태 변화를 감지하기 위해 현재 버튼 상태와 이전 버튼 상태를 비교하는데 사용)

byte digits[10][8] =                       // 0~9까지의 숫자를 byte 타입 2차원 배열로 구성
{                                          // 10개의 숫자(digits) , 8 byte의 신호
  {                                        // 숫자 0 
    B00111000,                             // 총 64개의 LED에 원하는 모양의 신호를 준다
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B01000100,
    B00111000
  },

  {                                         // 숫자 1
    B00010000,
    B00110000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00010000,
    B00111000 
  },

  {                                         // 숫자 2
    B00111000,
    B01000100,
    B00000100,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01111100
  },

  {                                          // 숫자 3
    B00111000,
    B01000100,
    B00000100,
    B00011000,
    B00000100,
    B00000100,
    B01000100,
    B00111000 
  },

  {                                          // 숫자 4
    B00000100,
    B00001100,
    B00010100,
    B00100100,
    B01000100,
    B01111100,
    B00000100,
    B00000100
  },

  {                                                     // 숫자 5
    B01111100,
    B01000000,
    B01000000,
    B01111000,
    B00000100,
    B00000100,
    B01000100,
    B00111000
  },

  {                                                      // 숫자 6
    B00111000,
    B01000100,
    B01000000,
    B01111000,
    B01000100,
    B01000100,
    B01000100,
    B00111000
  },

  {                                                       // 숫자 7
    B01111100,
    B00000100,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B00100000,
    B00100000
  },

  {                                                        // 숫자 8
    B00111000,
    B01000100,
    B01000100,
    B00111000,
    B01000100,
    B01000100,
    B01000100,
    B00111000 
  },

  {                                                         // 숫자 9
    B00111000,
    B01000100,
    B01000100,
    B01000100,
    B00111100,
    B00000100,
    B01000100,
    B00111000
  }
};

void setup() 
{
  Dote.shutdown(0, false);                 // 절전모드로 (첫번째 모듈, 절전모드를 하지 않는다) 설정 
  Dote.setIntensity(0, 7);                 // 밝기를 조절 (첫번째 모듈, 1~15까지 원하는 밝기) 설정
  Dote.clearDisplay(0);                    // LED를 초기화 설정 (첫번째 모듈)

  pinMode(buttonPin, INPUT_PULLUP);   // 버튼 피늘 입력 모드로 설정
  Serial.begin(9600);          // 시리얼 통신 초기화
}

void loop() 
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    buttonPushCounter++;
    // Serial.println("on");
    Serial.print("number of button pushes: ");
    Serial.println(buttonPushCounter);

      // updataDisplay();   // 디스플레이 갱신 함수 호출
    
    } // else {
      // Serial.println("off");
    }
    delay(50);
  }

  // lastButtonState = buttonState;

  // if (buttonPushCounter == 16) {
  //  buttonPushCounter = 0;
  
void updateDisplay() {
  if (buttonPushCounter >= 0 && buttonPushCounter < 10) {
    for (int a = 0; a < 8; a++) {   // j는 변수 (아무 단어로 명칭해도 됨)
      Dote.setRow(0, a, digits[buttonPushCounter][a]);
    }
  }
}
  /* int i, j;                                                  // for문에 사용할 변수 설정
  for (i = 0; i < 10; i++)                           // i는 0~9까지 10개의 숫자를 하나씩 표시 한다
  {
    for (j = 0; j <8; j++)                            // j는 미리 제작한 비트맵의 y축 8비트 신호를 하나씩 보낸다
    {
      Dote.setRow(0, j, digits[i][j]);           // setRow는 x축 LED를 한번에 제어하며,
    }                                                         // (첫번째 모듈 , y축 신호, 2차원배열값 [숫자] [8비트신호])
  delay (500);                                         // 0.5초의 딜레이
  }
  */

