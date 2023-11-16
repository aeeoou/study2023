// pitches.h 라이브러리를 포함합니다.
#include "pitches.h"

// 도레미파솔라시도의 음표를 정의합니다.
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6,
  NOTE_C6, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5
};

// 음표의 길이를 정의합니다. 4 = 4분음표, 8 = 8분음표 등
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4
};

// 시작시 점등할 LED의 핀 번호
const int startLedPin = 5;
// 재생 완료시 점등할 LED의 핀 번호
const int endLedPin = 3;

void setup() {
  // 핀을 출력으로 설정합니다.
  pinMode(startLedPin, OUTPUT);
  pinMode(endLedPin, OUTPUT);

  // 시작 LED를 꺼진 상태로 초기화합니다.
  digitalWrite(startLedPin, HIGH);
  // 종료 LED를 꺼진 상태로 초기화합니다.
  digitalWrite(endLedPin, LOW);

  // 멜로디를 연주합니다.
  for (int thisNote = 0; thisNote < 16; thisNote++) {
    // 음표의 연주 시간을 계산합니다.
    int noteDuration = 1500 / noteDurations[thisNote];
    // 음표를 발생시킵니다.
    tone(8, melody[thisNote], noteDuration);

    // 음과 음 사이의 쉬는 시간을 설정합니다.
    int pauseBetweenNotes = noteDuration * 1.30;
    // 쉬는 시간 동안 대기합니다.
    delay(pauseBetweenNotes);
    // 음표 연주를 중지합니다.
    noTone(8);
  }

  // 재생이 완료되면 LED 2개를 점등합니다.
  digitalWrite(startLedPin, OUTPUT);
  digitalWrite(endLedPin, HIGH);
}

void loop() {
  // 멜로디를 반복해서 연주하지 않습니다.
}