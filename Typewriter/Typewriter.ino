/*#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_sv_SE.h>
 */

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
    void setPins(int DataBits_pin[], int strobe_pin, int busy_pin)
    {
      Strobe = strobe_pin;
      Busy = busy_pin;
      memcpy(DataBit , DataBits_pin , 8*sizeof(int) );

      pinMode(Strobe,OUTPUT);
      pinMode(Busy,INPUT);
      for(byte i=0 ; i<8 ; i++)
        pinMode(DataBit[i], OUTPUT);
    }
    void Print(byte msg)
    {
      Wait_if_Busy(); // waits until the busy pin goes low
      
      for(byte i=0 ; i<8 ; i++){
        digitalWrite(DataBit[0],bitRead(msg,0));
        //Serial.println(bitRead(msg,0));
      }
      Pulse_strobe(); 
    }
  
};
Printer dotmatrix;
void setup() {
  // Minimum pins needed to run this with parallel port
  int dpin[8] = {9,8,7,6, 5,4,3,2}; //D0 to D7
  int busy = 11 , strobe = 12 ;
  
  //keyboard pins (usb/ps2)
  const int Data = 10; // D+
  const int Clock = 13; // D-
  
  dotmatrix.setPins(dpin, strobe, busy); 
  //initialise keyboard...?(idk)
  //Serial.begin(9600);
  
}

void loop() {
  // read input from keyboard
  // convert scan code to ascii(byte)
  // write the ascii to the printer -> dotmatrix.Print(ascii)

}
