// 230729 2차 과제 FND, 스위치, RC서보 동시 작동시키기
#include <Servo.h>
#include "Arduino.h"


const int buttonPin = 10; // 스위치 연결 번호
const int ledPin = 13; // LED 연결 번호
const int servoPin = 11; // 서보모터 연결 번호

Servo servoMotor; // 서보모터 설정

const int pins[8] = {2, 3, 4, 5, 6, 7, 8, 9}; // FND 번호 점등을 위해 사용할 8개의 포트
const int numberCode[16][8] = {
  {0,0,0,0,0,0,1,0}, // 0
  {1,0,0,1,1,1,1,0}, // 1
  {0,0,1,0,0,1,0,0}, // 2
  {0,0,0,0,1,1,0,0}, // 3
  {1,0,0,1,1,0,0,0}, // 4
  {0,1,0,0,1,0,0,0}, // 5
  {0,1,0,0,0,0,0,0}, // 6
  {0,0,0,1,1,0,1,0}, // 7
  {0,0,0,0,0,0,0,0}, // 8
  {0,0,0,0,1,0,0,0}, // 9
  {0,0,0,1,0,0,0,0}, // A
  {1,1,0,0,0,0,0,0}, // B
  {0,1,1,0,0,0,1,0}, // C
  {1,0,0,0,0,1,0,0}, // D
  {0,1,1,0,0,0,0,0}, // E
  {0,1,1,1,0,0,0,0}}; // F

//const int servo[16] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150};



int buttonPushCounter = 0;
int buttonState = 0;
int lastButtonState = 0;

void showNumber(int number)
{
  boolean value; 

  for(int bitPosition = 0; bitPosition<8;bitPosition++)
  {
    if(number<0||number>16)
      value = 0;
    else
      value = numberCode[number][bitPosition];
    digitalWrite(pins[bitPosition],value);
  }
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  for (int i = 0; i < 8; i++)
    pinMode(pins[i], OUTPUT);
  pinMode(buttonPin, INPUT);

  servoMotor.attach(servoPin);
  servoMotor.write(90); // 서보모터 초기 각도 설정
  delay(100); // 서보모터 딜레이 시간
 // showNumber(buttonPushCounter);
}

void loop(){

  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);

      //servoMotor.write(servo[buttonPushCounter]);

    } else {
      Serial.println("off");
    }
    delay(50);
  }

  
  lastButtonState = buttonState;

  if (buttonPushCounter == 16) {
    buttonPushCounter = 0;
  }

  showNumber(buttonPushCounter);


// 버튼이 눌릴 때마다 LED 교대로 켜고 끄기
if (buttonPushCounter % 2 == 0) {
  digitalWrite(ledPin, HIGH);
} else {
  digitalWrite(ledPin, LOW);
}

  

  int angle = map(buttonPushCounter, 0, 15, 0, 180); // 서보모터 각도 매핑
  servoMotor.write(angle);
  delay(100);
}


// void showNumber(int number) {

//   boolean value;
//   for (int bitPosition = 0; bitPosition < 8; bitPosition++) {
//     if (number < 0 || number > 16)
//       value = 0;
//     else
//       value = bitRead(numberCode[number], bitPosition);
//     digitalWrite(pins[bitPosition], value);
//   }
// }