/*본 스케치는 https://infoinno.tistory.com/70 블로그와 쳇 gpt 를 참조하여 필요 코드를 발췌하여 작성하였습니다.
수정일 2024.05.16
작성자 신정헌*/
#include <Wire.h>// I2C 통신
#include <LiquidCrystal_I2C.h>
#include <DHT.h>//온습도

#define pinDHT 9//온습도 센서 핀
#define DHTTYPE DHT11//온습도센서 부품타입

DHT dht(pinDHT, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);//lcd 부품
int count = 0;
int numStars = 0;
bool increasing = true; // 별이 나타나는 상태를 나타내는 플래그
float celsiusToFahrenheit(float celsius) {
  return floor (celsius * 9.0 / 5.0 + 32.0);
}

void setup() {
  Serial.begin(9600);
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
  //DHT
  
  int h = dht.readHumidity();
  int t = dht.readTemperature();
   // 섭씨를 화씨로 변환
  float t_fahrenheit = celsiusToFahrenheit(t);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t_fahrenheit);
  Serial.print(" C    ");
  Serial.print(count);

  lcd.setCursor(0, 0);
  lcd.print("T ");
  lcd.print((int)t_fahrenheit);
  lcd.print(" f");
  lcd.setCursor(0, 1);
  lcd.print("H ");
  lcd.print(h);
  lcd.print(" %");
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