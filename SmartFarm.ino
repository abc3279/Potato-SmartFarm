//3개월 후 재배
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <SoftwareSerial.h>

//라이브러리 관련 핀
#define DHTPIN 8 //dht11 8번 핀
#define DHTTYPE DHT11

//라이브러리 관련
DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial bt(2, 3); // 블루투스 통신을 위한 핀설정(핀2-TXD, 핀3-RXD)
LiquidCrystal_I2C lcd(0x27,16,2);

//아날로그 핀 변수
int soil = A0;  //토양수분센서를 A0번 핀으로 선언
int water = A1;
int cds = A2;

//디지털 핀 변수
int water_pump = 4;
int heat = 5;
int fan = 6;
int pmoi = 7;
int led = 9;

//값을 저장하는 변수들
int soil_value = 0;
int water_value = 0;
float tmp_value = 0;
float moi_value = 0;

//참 거짓을 저장하는 변수들
bool warning = 0;
bool is500 = 0;

void setup() 
{
  pinMode(heat, OUTPUT);
  pinMode(water_pump, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(pmoi, OUTPUT);
  pinMode(led, OUTPUT);
  
  bt.begin(9600);   
  dht.begin();

  lcd.init();
  lcd.backlight();
}

void loop() 
{
  soil_value = analogRead(soil);  
  moi_value = dht.readHumidity();
  tmp_value = dht.readTemperature();
  water_value = analogRead(water);
 
    //bluetooth 출력
    bt.print("soil-moi: ");
    bt.println(soil_value);
    bt.print("Tmp : ");
    bt.print(tmp_value);
    bt.println(" C");
    bt.print("moi : ");
    bt.print(moi_value);
    bt.println("%");
    bt.print("water : ");
    bt.println(water_value);
    bt.print("cds : ");
    bt.println(analogRead(cds));
 
    if(tmp_value < 20) 
    {
      digitalWrite(heat, LOW);
      digitalWrite(fan, HIGH);
    }
    else
    {
      digitalWrite(heat, HIGH);
      digitalWrite(fan, LOW);
    }
    
    if(moi_value < 50)
    {
      digitalWrite(pmoi, HIGH);
    }
    else
    {
      digitalWrite(pmoi, LOW);
    }
    
    if(soil_value >= 630) {
      digitalWrite(water_pump, LOW); // 가동
    }
    else
    {
      digitalWrite(water_pump, HIGH); // 중지
    }

    if(analogRead(cds) < 30)
    {
        digitalWrite(led, HIGH);
    }
 
    else
    {
      digitalWrite(led, LOW);
    }   

  delay(1000);
}
