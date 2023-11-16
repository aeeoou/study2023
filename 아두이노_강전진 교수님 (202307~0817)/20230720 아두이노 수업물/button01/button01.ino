const int buttonPin = 2; // 버튼이 연결된 핀 번호
const int ledPin = 13;   // LED가 연결된 핀 번호

int buttonState = 0;     // 버튼 상태를 저장하는 변수 (0: 미눌림, 1: 눌림)

void setup() {
  pinMode(buttonPin, INPUT); // 버튼 핀을 입력으로 설정
  pinMode(ledPin, OUTPUT);   // LED 핀을 출력으로 설정
}

void loop() {
  buttonState = digitalRead(buttonPin); // 버튼 상태를 읽어서 변수에 저장

  if (buttonState == HIGH) { // 버튼이 눌렸을 때
    digitalWrite(ledPin, HIGH); // LED를 켜기
  } else { // 버튼이 눌리지 않았을 때
    digitalWrite(ledPin, LOW); // LED를 끄기
  }
}

