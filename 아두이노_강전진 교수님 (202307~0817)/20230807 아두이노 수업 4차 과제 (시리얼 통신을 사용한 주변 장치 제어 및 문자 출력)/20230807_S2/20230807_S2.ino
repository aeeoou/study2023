#include <Arduino.h>
#include <Servo.h>

Servo servoMotor;

const int gasSensorPin = A1;   // 가스 센서 모듈을 연결한 아날로그 핀 번호

void setup() {
  Serial.begin(9600);
  servoMotor.attach(9);   // 서보 모터를 9번 핀에 연결
  servoMotor.write(90);   // 서보 모터의 초기 각도를 90도로 설정
}

void loop(){
  if (Serial.available() > 0) {
    char inputChar = Serial.read();

    if (inputChar >= '1' && inputChar <= '5') {   // 1부터 5 사이의 숫자가 입력되었을 때
      int angle = (inputChar - '0') * 30;   // 입력된 숫자에 해당하는 각도 계산 (1-30, 2-60, 3...)
      servoMotor.write(angle);   // 서보 모터를 계산한 각도로 회전
    } else if (inputChar == 'a') {   // 문자 'a' 가 입력되었을 때 가스 센서 값을 읽어서 시리얼로 출력
    int gasValue = analogRead(gasSensorPin);
    Serial.print("Gas Sensor Value: ");
    Serial.println(gasValue);
    }
  }
}