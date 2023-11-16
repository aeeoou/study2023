#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 9   // 초음파 센서 Trig 핀을 9번 핀에 연결
#define ECHO_PIN 8   // 초음파 센서 Echo 핀을 8번 핀에 연결

LiquidCrystal_I2C lcd (0x27, 16, 2);   // I2C 주소와 LCD 크기 설정 (주소는 0x27일 수도 있음)

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lcd.begin(16, 2);   // LCD 초기화
  lcd.print("Distance:");   // 첫 번째 줄에 표시할 초기 텍스트 출력
  lcd.backlight();
}


void loop() {
  long duration, distance_cm;

  // 초음파 센서로 거리 측정
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);

  // 거리(cm) 계산
  distance_cm = duration * 0.034 / 2;

  // LCD에 거리 값 출력
  lcd.setCursor(9, 0);   // 첫 번째 줄의 9번째 열에 커서 위치 설정
  lcd.print("      ");   // 이전에 출력된 값 지우기
  lcd.setCursor(9, 0);   // 커서 위치 다시 설정
  lcd.print(distance_cm);   // 측정된 거리 값 출력
  lcd.print("cm");

  delay(500);   // 0.5초 간격으로 거리 측정과 LCD 출력 반복
}