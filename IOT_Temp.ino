/*본 스케치는 https://infoinno.tistory.com/70 블로그와 쳇 gpt 를 참조하여 필요 코드를 발췌하여 작성하였습니다.
수정일 2024.05.16
작성자 신정헌*/
#include <Wire.h>// I2C 통신
#include <LiquidCrystal_I2C.h>
#include <DHT.h>//온습도

#define pinDHT 9//온습도 센서 핀
#define DHTTYPE DHT11//온습도센서 부품타입
#define DCFAN  6
#define DCFAN_2 5

DHT dht(pinDHT, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);//lcd 부품
int numStars = 0;
bool increasing = true; // 별이 나타나는 상태를 나타내는 플래그


void setup() {
  pinMode(DCFAN,OUTPUT);
  pinMode(DCFAN_2,OUTPUT);
  //처음 동작 시 나오는 메시지
  Serial.begin(9600);//아두이노 보드타입 시리얼
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(6, 0);
  lcd.print("HELLO");
  lcd.setCursor(0, 1);
  lcd.print("Thermohygrometer");
  delay(2000);
  lcd.clear();
}

void loop() {
  //DHT결과값 불러오기
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  
//시리얼모닝터
  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" C    ");
  Serial.println("");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.println("");
  Serial.print("WORKING.......");
  Serial.println("");

  int fanSpeed = map(t, 18, 24, 0, 255); // 온도 20도에서 30도 사이를 팬 속도 0~255로 매핑
  fanSpeed = constrain(fanSpeed, 0, 255); // 팬 속도 제한
  analogWrite(DCFAN, fanSpeed); // 팬 속도 설정

  int fanSpeed2 = map(h, 24, 70, 0, 255); // 습도 24%에서 70% 사이를 팬 속도 0~255로 매핑
  fanSpeed2 = constrain(fanSpeed, 0, 255); // 팬 속도 제한
  analogWrite(DCFAN_2, fanSpeed); // 팬 속도 설정


  lcd.setCursor(0, 0);
  lcd.print("T ");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("H ");
  lcd.print(h);
  lcd.print("%");
  lcd.setCursor(9,0);
  lcd.print("Working");
  lcd.setCursor(11, 1);
   // 별 개수 증가 또는 감소
  if (increasing) {
    numStars++;
    lcd.setCursor(10, 1);
    for (int i = 0; i < numStars; i++) {
      lcd.print("*");
    }
    if (numStars == 5) {
      increasing = false;
    }
  } else {
    numStars--;
    lcd.setCursor(10 - numStars + 4, 1);
    lcd.print(" ");
    if (numStars == 0) {
      increasing = true;
    }
    
  }

  delay(1000);
  }