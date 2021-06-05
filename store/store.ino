#include <SoftwareSerial.h>         //블루투스
#include <SPI.h>                      //rfid
#include <MFRC522.h>                 //rfid


SoftwareSerial BTSerial(2,3);         //블루투스 data input output 핀 설장

#define OFF   HIGH                      
#define ON    LOW
#define RST_PIN     9
#define SS_PIN      10

MFRC522 mfrc(SS_PIN, RST_PIN);          //rfid 디지털 핀 9, 10 사용

int card = 5;                            //포토인트럽터 핀 5번
int cash = 4;                            //스위치 핀 4번
               

void setup() {
  Serial.begin(9600);                   //시리얼통신b
  BTSerial.begin(9600);                  //블루투스 통신
  SPI.begin();                          //rfid
  
  pinMode(card, INPUT);
  pinMode(cash, INPUT);
}

void loop() {
  int fre = 0;
  int val = digitalRead(card);
  if (val == OFF)                     //포토인터럽트 카드 감지 시 fre+1 
  {
    fre = fre + 1; 
    Serial.println(fre);              //fre 변수 전송
    BTSerial.write(fre);
  }
  delay(200);
  
  int ant = 2;
  int val1 = digitalRead(cash);       //스위치 눌리면 ant+1
  if (val1 == OFF)
  {
    ant = ant + 1;
    Serial.println(ant);              //ant 변수 전송
    BTSerial.write(ant);

  }
  delay(200);

  if ( ! mfrc.PICC_IsNewCardPresent() || ! mfrc.PICC_ReadCardSerial() )         //rfid 에 감지 안되거나 id 가 다를 때
  {
    delay(500);
    return;
  }

  int drk = 4;
  if ( mfrc.uid.uidByte[0] == 78 && mfrc.uid.uidByte[1] == 120 && mfrc.uid.uidByte[2] == 83 && mfrc.uid.uidByte[3] ==  211 )          //rfid tag의 id 맞으면 drk +1
  {
    drk = drk + 1;
    
    Serial.println(drk);           //drk 전송
    BTSerial.write(drk);
    delay(200);
  }

  int snk = 6;    
  if ( mfrc.uid.uidByte[0] == 3 && mfrc.uid.uidByte[1] == 64 && mfrc.uid.uidByte[2] == 196 && mfrc.uid.uidByte[3] == 43 )             //rfid tag id 맞으면 snk+1
  {
    snk = snk + 1;
    Serial.println(snk);          //snk 전송
    BTSerial.write(snk);
    delay(200);
  }

  int ndl = 8;
  if ( mfrc.uid.uidByte[0] == 239 && mfrc.uid.uidByte[1] == 53 && mfrc.uid.uidByte[2] == 92 && mfrc.uid.uidByte[3] == 100 )         //rfid tag id 맞으면 ndl+1
  {
    ndl = ndl + 1;
    Serial.println(ndl);          //ndl 전송
    BTSerial.write(ndl);
    delay(200);
  }
}
