const int ledPins[] = {6, 9, 3, 5, 10}; // LED가 연결된 디지털 핀 번호 배열
const int numLEDs = 5; // LED 개수
const int delayTime = 1000; // LED 켜지거나 꺼지는 간격 (밀리초)

void setup() {
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT); // 모든 LED 핀을 출력으로 설정
  }
}

void loop() {
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], HIGH); // i번째 LED 켜기
    delay(delayTime); // delayTime 시간만큼 대기
    digitalWrite(ledPins[i], LOW); // i번째 LED 끄기
  }
}