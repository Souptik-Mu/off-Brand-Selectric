#include <PS2Keyboard.h>
#include <string.h>
#include <stdio.h>

#define KBD_CLK_PIN 3
#define KBD_DATA_PIN 2
/*
#define d0 4
#define d1 5
#define d2 6
#define d3 7
#define d4 8
#define d5 9
#define d6 10
#define d7 11
*/
#define d7 4
#define d6 5
#define d5 6
#define d4 7
#define d3 8
#define d2 9
#define d1 10
#define d0 11

#define strobe 12
#define autofd 13

PS2Keyboard keyboard;

int caracter = 0;

int D[8] = {d1,d2,d3,d4,d5,d6,d7};
bool A[8] = {0,1,1,0, 0,0,0,0};
void imprime(byte msg)
{
// decode character into 8 bits
  byte t = msg;
  for(int i=7 ;i>=0;i--)
  {
    bool a = t%2;
    Serial.print(a);Serial.print(" ");
    digitalWrite(D[i],a);
    t=t/2;
  }
  /*digitalWrite(d0,bitRead(msg,0));Serial.print(bitRead(msg,0));
  digitalWrite(d1,bitRead(msg,1));Serial.print(bitRead(msg,1));
  digitalWrite(d2,bitRead(msg,2));Serial.print(bitRead(msg,2));
  digitalWrite(d3,bitRead(msg,3));Serial.print(bitRead(msg,3));
  digitalWrite(d4,bitRead(msg,4));Serial.print(bitRead(msg,4));
  digitalWrite(d5,bitRead(msg,5));Serial.print(bitRead(msg,5));
  digitalWrite(d6,bitRead(msg,6));Serial.print(bitRead(msg,6));
  digitalWrite(d7,bitRead(msg,7));Serial.print(bitRead(msg,7));
  */Serial.print("\n");


      digitalWrite(strobe,LOW);
      delayMicroseconds(2);
      digitalWrite(strobe,HIGH);
}


void setup() {
keyboard.begin(KBD_DATA_PIN,KBD_CLK_PIN);
pinMode(d0, OUTPUT);
pinMode(d1, OUTPUT);
pinMode(d2, OUTPUT);
pinMode(d3, OUTPUT);
pinMode(d4, OUTPUT);
pinMode(d5, OUTPUT);
pinMode(d6, OUTPUT);
pinMode(d7, OUTPUT);
pinMode(strobe, OUTPUT);
digitalWrite(strobe,HIGH);
Serial.begin(9600);
delay(1000);
  //imprime(97);
}



void loop() {
  if(keyboard.available()) {
    byte c = keyboard.read();
    imprime(c);
    Serial.println(c);
  }
  //for(int i=80 ; i<150 ; i++)
  //imprime(97);
}
