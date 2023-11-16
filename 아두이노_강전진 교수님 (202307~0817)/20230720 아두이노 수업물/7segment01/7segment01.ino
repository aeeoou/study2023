#include <Servo.h>
Servo mysv; // Servo 크래스를 사용한다.

void setup() {
  mysv. attach(8); // 8번 핀으로 초기화합니다.
}
// 아날로그 A0번의 값(0~1023)을 읽어 0~90도로 매핑해서 작동한다

void loop() {
  mysv.write(map(analogRead(A0), 0, 1023, 0 ,180));
  delay(100);
}
