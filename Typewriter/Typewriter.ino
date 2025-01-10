#include <PS2Keyboard.h>

class Printer{
  private:
      //serial port pins
    int Strobe;
    int DataBit[8] ;
    int Busy;
      
    void Wait_if_Busy(){ 
      while(digitalRead(Busy) == HIGH); //is this polling ?
        return;
      }
    void Pulse_strobe(){
      digitalWrite(Strobe, LOW);
      delayMicroseconds(2); // The strobe works best with 2microSecond pulse (for my printer)
      digitalWrite(Strobe, HIGH);
      return;
      }
  public:
    void begin(int DataBits_pin[], int strobe_pin, int busy_pin)
    {
      Strobe = strobe_pin;
      Busy = busy_pin;
      memcpy(DataBit , DataBits_pin , 8*sizeof(int) );

      pinMode(Strobe,OUTPUT);
      pinMode(Busy,INPUT);
      for(byte i=0 ; i<8 ; i++)
        pinMode(DataBit[i], OUTPUT);

      digitalWrite(strobe,HIGH);
    }
    void printByte(byte msg)
    {
      //Wait_if_Busy(); // waits until the busy pin goes low
      
      for(byte i=0 ; i<8 ; i++){
        digitalWrite(DataBit[i],bitRead(msg,i));
        //Serial.println(bitRead(msg,0));
      }
      Pulse_strobe(); 
    }
  
};

PS2Keyboard keyboard;
Printer dotmatrix;

void setup() {
  // Minimum pins needed to run this with parallel port
  int dpin[8] = {9,8,7,6, 5,4,3,2}; //D0 to D7
  int busy = 11 , strobe = 12 ;
  //keyboard pins (usb/ps2)
  const int Data = 10; // D+
  const int Clock = 13; // D-

  keyboard.begin(Data,Clock);
  dotmatrix.begin(dpin, strobe, busy);
  //Serial.begin(9600);
  
}

void loop() {
  if(keyboard.available()) {
    byte c = keyboard.read();
    dotmatrix.printByte(c);
    //Serial.println(c);
  }
}
