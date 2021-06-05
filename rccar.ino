int xPin = A1;
int yPin = A2;
int buttonPin = 4;

int  xPosition = 0;
int  yPosition = 0;


#include <SoftwareSerial.h>

SoftwareSerial mySerial(3,2); //블루투스 객체 선언(TX,RX)

void setup() {

// initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  mySerial.begin(9600); //소프트웨어 시리얼 통신 설정
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP); 
  
  // For versions prior to Arduino 1.0.1
  // pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);

  // Start serial at 9600 baud
}

 void loop() {
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  int buttonState = digitalRead(buttonPin);
  
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(buttonState);

  // Print out the value you read:
  Serial.println(voltage);
  
if(xPosition==526 || xPosition==527 || xPosition==528) 
{

if ( yPosition > 1000 ) 
{
    mySerial.println("2");  //후진
    Serial.print("2");
}
  
else if (yPosition < 20 ) 
{                                     
    mySerial.println("1");  //전진
    Serial.print("1");
}
}
else if (xPosition > 1000 ) 
{
    mySerial.println("3"); //우회전
    Serial.print("3");
}

else if ( xPosition < 20 ) 
{
    mySerial.println("4");  //좌회전
    Serial.print("4");
}

 if(voltage > 2 )
 {
    mySerial.println("5");  //가속
    Serial.print("5");
 }

delay(500);
}

