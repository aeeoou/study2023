#if 0 

#elif 0
const byte ledPin = 13;   // LED를 연결한 핀 번호
const byte interruptPin = 2;   // 인터럽트 핀 번호
volatile byte state = LOW;   // LED의 상태를 저장하는 변수 (HIGH 또는 LOW)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT);   // 인터럽트 핀을 입력
  attachInterrupt(0, blink, CHANGE);   // 인터럽트 핀에 인터럽트 핸들러 함수 등록
}

void loop() {
  digitalWrite(ledPin, state);   // LED 상태 업데이트
}

void blink() {
  state = !state;   // LED 상태 반전
}

#elif 1
#include <TimerOne.h>   // 외부 라이브러리 사용을 위해 TimerOne.h 파일을 iclude

int count = 0;   // 타이머 인터럽트 핸들러를 수행할 때마다 1씩 증가할 변수인 count를 0으로 초기화
void setup() {
  pinMode(13, OUTPUT);   // LED가 연결된 13번을 OUTPUT 설정
  Serial.begin(9600);   // 시리얼을 9600bps 로 초기화
  Timer1.initialize(10000);   // Timer1 을 initialize 함수를 통해 10000us 즉, 10ms 단위로 인터럽트 주기 지정
  Timer1.attachInterrupt(timerISR);   // Timer1을 attachInterrupt 함수를 통해 timerlsr 이라는 인터럽트 핸들러 등록
}
void loop() {
}
void timerlsr()
{
  digitalWrite(13, digitalRead(13)^1);
  count++;
  if(count%100==0)
  {
    Serial.println(count);
  }
}

#endif