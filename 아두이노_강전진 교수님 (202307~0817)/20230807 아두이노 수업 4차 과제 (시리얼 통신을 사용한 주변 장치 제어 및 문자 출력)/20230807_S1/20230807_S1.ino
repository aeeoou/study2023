#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

char receivedString[100];   // 시리얼로 받은 문자열을 저장할 버퍼

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();

  Serial.begin(9600);
}

void loop()
{
  Serial.readBytes(receivedString, 100);   // 문자열의 최대길이
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_unifont_t_korean1);
  u8g2.setFontDirection(0);
  u8g2.firstPage();
  do
  {
  u8g2.setCursor(0, 15);
  u8g2.print(receivedString);   // 받은 문자열 출력
  // u8g2.sendBuffer();   // 디스플레이에 업데이트 된 화면 보이기
    }
    while ( u8g2.nextPage() );
}
