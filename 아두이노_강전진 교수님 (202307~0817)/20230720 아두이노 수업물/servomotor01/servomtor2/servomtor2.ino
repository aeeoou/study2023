#include <Servo.h> // Servo모터를 사용하기 위한 라이브러리 입력
Servo mysv; // Servo 크래스를 사용한다.

void setup() {
  mysv. attach(8); // 8번 핀으로 초기화합니다.
}
// 아날로그 A0번의 값(0~1023)을 읽어 0~90도로 매핑해서 작동한다

void loop() {
  mysv.write(0);
  delay(1000);

  mysv.write(90);
  delay(1000);

  mysv.write(180);
  delay(1000);

  mysv.write(0);
  delay(1000);
}
