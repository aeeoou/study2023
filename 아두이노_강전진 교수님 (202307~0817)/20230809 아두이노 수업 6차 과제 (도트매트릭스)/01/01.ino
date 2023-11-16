#include <LedControl.h>                    // LedControl 헥사 파일 선언
#include "pitches.h"                       // pitches 파일 선언

LedControl Dote = LedControl(7,6,5,1);     // 모듈핀 위치 설정 (DIN, CLK, CS, 몇번째 모듈) 

#define TRIG 9   // TRIG 9번 핀
#define ECHO 8   // ECHO 8번 핀
#define NOTE 25  // 음표 개수 매크로 정의. 산토끼 재생
// #define NOTE 49  // 음표 개수 매크로 정의. 곰 세마리 재생

byte digits[4][8] =                        // 네모 1~4의 비트맵을 정의
{
  {                                        // 네모1
    B00000000,                            
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000
  },

  {                                        // 네모2
    B11111111,
    B11111111,
    B11111111,
    B11100111,
    B11100111,
    B11111111,
    B11111111,
    B11111111  
  },

  {                                        // 네모3
    B11111111,
    B11111111,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11111111,
    B11111111 
  },

  {                                        // 네모4
    B11111111,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B10000001,
    B11111111
  }
};

int melody[] =
{                                             // 산토끼 음표 25
  NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_E4,
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_C4,
  NOTE_E4, NOTE_G4, NOTE_C5, NOTE_G4, NOTE_C5,
  NOTE_G4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_G4,
  NOTE_D4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4
};

int noteDurations[] =
{                                             // 산토끼 
  4, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4,
  8, 8, 8, 8, 8, 8, 4, 4, 8, 8, 8, 8, 4
};

/* int melody[] =
{                                                  // 곰 세마리 음표 49
  NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,
  NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
  NOTE_G5,NOTE_G5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,
  NOTE_C5,NOTE_C5,NOTE_C5,
  NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
  NOTE_G5,NOTE_G5,NOTE_G5,
  NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
  NOTE_G5,NOTE_G5,NOTE_G5,
  NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,
  NOTE_G5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_G5,
  NOTE_C6,NOTE_G5,NOTE_C6,NOTE_G5,
  NOTE_E5,NOTE_D5,NOTE_C5
};

int noteDurations[]=                            
{                                                  // 곰 세마리                                    
  4,8,8,4,4,
  4,8,8,4,4,
  8,8,4,8,8,4,
  4,4,2,
  4,4,4,4,
  4,4,2,
  4,4,4,4,
  4,4,2,
  4,4,4,4,
  8,8,8,8,2,
  4,4,4,4,
  4,4,2
};
*/

void setup()
{
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);     // 초음파센서 TRIG
  pinMode(ECHO, INPUT);      // 초음파센서 ECHO

  pinMode(13, OUTPUT);       // 수동부저 3번핀 연결

  Dote.shutdown(0, false);   // 도트매트릭스 절전모드로 설정
  Dote.setIntensity(0, 7);   // 도트매트릭스 밝기모드 설정
  Dote.clearDisplay(0);      // 도트매트릭스 LED 초기화 설정
}

void loop()
{
  long duration, distance;   

  digitalWrite(3, LOW);      // 초기 상태에서 부저를 끈다.

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn (ECHO, HIGH);

  distance = (duration * 17) / 1000;
  // distance = duration * 17 / 1000;

  Serial.println(duration);
  Serial.print("\nDIstance : ");
  Serial.print(distance);
  Serial.print(" CM");
  
  delay(50);

  Dote.clearDisplay(0);              // 이전 표시 지우기

   int noteDuration;                 // 음표의 재생 시간을 나타내는 변수
   int pauseBetweenNotes;            // 음표 간의 일시적인 정지 시간을 나타내는 변수

  if (distance <= 10)                // 거리가 10cm 미만일 때
  { 
    for (int blinkCount = 0; blinkCount < 5; blinkCount++) {
      displayNemo(1);
      delay(50);
      Dote.clearDisplay(0);
      delay(50);
    }

    for (int thisNote = 0; thisNote < NOTE; thisNote++) {        // 노래 재생
     noteDuration = 1000 / noteDurations[thisNote];
      tone(13, melody[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
    }

  } else if (distance >= 10 && distance < 20) {          // 거리가 10~20cm 사이일 때
    displayNemo(2);                                      // 2번 네모 표시
    digitalWrite(3, LOW);
    delay(0);                                            // 부저 울리는 시간 조절
    tone(13, melody[1], 500);                            // 2번 네모일 때 부저 울림

  } else if (distance >= 20 && distance < 30) {          // 거리가 20~30cm 사이일 때
    displayNemo(3);                                      // 3번 네모 표시
    digitalWrite(3, LOW);
    delay(0);  
    tone(13, melody[2], 500);                            // 3번 네모일 때 부저 울림

  } else {                                               // 거리가 30cm 이상일 때
    displayNemo(4);                                      // 4번 네모 표시
    digitalWrite(3, LOW);
    delay(0);  
    tone(13, melody[3], 500);                            // 4번 네모일 때 부저 울림
  }
  delay(50);
}

void displayNemo (int nemo) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Dote.setRow(0, j, digits[nemo - 1][j]);
    }
    delay(100);
  }
}


