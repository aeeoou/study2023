// 필요한 라이브러리를 포함시킨다.
#include <Servo.h>

// 핀 번호를 정한다.
const int ledPin = 9; // LED를 연결한 핀 번호 (PWM 핀)
const int servoPin = 10; // 서보모터를 연결한 핀 번호
const int joyXPin = A0; // 조이스틱 X축 핀 번호
const int joyYPin = A1; // 조이스틱 Y축 핀 번호
const int joyButtonPin = 2; // 조이스틱 버튼을 연결한 핀 번호

// 서보 객체 생성
Servo servoMotor;

void setup() {
  // 핀 모드 설정
  pinMode(ledPin, OUTPUT);
  // 서보모터 연결 설정
  servoMotor.attach(servoPin);
  // 조이스틱 버튼을 입력 모드로 설정
  pinMode(joyButtonPin, INPUT_PULLUP);

  // 시리얼 통신 시작
  Serial.begin(9600);
}

void loop() {
  // 조이스틱 값 읽기 (X축과 Y축)
  int joyXValue = analogRead(joyXPin);
  int joyYValue = analogRead(joyYPin);

  // X축 값을 서보모터에 적용하여 각도로 변환 (0~180도로 제한)
  int servoAngle = map(joyXValue, 0, 1023, 0, 180);
  servoMotor.write(servoAngle);

  // Y축 값을 LED 밝기 (PWM)로 변환하여 적용 (0~255로 제한)
  int ledBrightness = map(joyYValue, 0, 1023, 0, 255);
  analogWrite(ledPin, ledBrightness);

  // 조이스틱 버튼 상태 확인
  bool buttonState = digitalRead(joyButtonPin);

  // 조이스틱 버튼이 눌렸을 때 LED를 켬
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // 시리얼 모니터에 값을 출력하여 확인
  Serial.print("Joystick X Value: ");
  Serial.print(joyXValue);
  Serial.print(", Servo Angle: ");
  Serial.print(servoAngle);
  Serial.print(", Joystick Y Value: ");
  Serial.print(joyYValue);
  Serial.print(", LED Brightness: ");
  Serial.print(ledBrightness);
  Serial.print(", Joystick Button: ");
  Serial.println(buttonState);
  
  // 일시적인 딜레이 추가
  delay(100);
}