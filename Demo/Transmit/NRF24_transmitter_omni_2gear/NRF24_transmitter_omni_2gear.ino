#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <GPSXClass.h>

/*
 * green -> 52
 * purple ->50
 * blue ->51
 * SPI for Mega: https://www.arduino.cc/en/Reference/SPI
 */

 
RF24 radio(9,8);

const byte address[6] = "7";
uint8_t but_mem = 50;


bool CROSS_PRESSED = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPayloadSize(1);
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  //radio.setRetries(15, 15); 
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  PSX.mode(PSX_PAD1, MODE_ANALOG, MODE_LOCK);
  PSX.updateState(PSX_PAD1);
}

void joystick_read()
{
  PSX.updateState(PSX_PAD1);  
  Serial.println(but_mem);
// Serial .print("X: ");
 // Serial.print(ANALOG_LEFT_X(PSX_PAD1));
 // Serial.print("  Y:  ");
//  Serial.println(ANALOG_LEFT_Y(PSX_PAD1));


 if (PRESSED_CROSS(PSX_PAD1)==1) 
 { 
     CROSS_PRESSED = 1;  
   }

 if (RELEASED_CROSS(PSX_PAD1)==1) 
 { 
     CROSS_PRESSED = 0;  
   }

  if (CROSS_PRESSED == 1  ) {
      but_mem = 99 ;//SHOOT;
    }


else if (ANALOG_RIGHT_X(PSX_PAD1)< 101 ||  ANALOG_RIGHT_X(PSX_PAD1)> 149)

{
  
  if (ANALOG_RIGHT_X(PSX_PAD1)<20) {
     but_mem = 103; //TURN CCV FAST
   }


  if (ANALOG_RIGHT_X(PSX_PAD1)>19 && ANALOG_RIGHT_X(PSX_PAD1)<100) {
     but_mem = 101; //TURN CCV SLOW
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>150 && ANALOG_RIGHT_X(PSX_PAD1)<236) {
     but_mem = 111;  //TURN CV SLOW
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>235 && ANALOG_RIGHT_X(PSX_PAD1)<256) {
     but_mem = 113;   //TURN CV FAST
   }
  
  }






else
{


    if (ANALOG_LEFT_Y(PSX_PAD1)>94 && ANALOG_LEFT_Y(PSX_PAD1)<141) {
     but_mem = 50; //BOŞ
   }

if (ANALOG_LEFT_Y(PSX_PAD1)<15 ) {
     but_mem = 13;    //YUKARI HIZLI
   }

else   if (ANALOG_LEFT_Y(PSX_PAD1)>14 && ANALOG_LEFT_Y(PSX_PAD1)<95) {
     but_mem = 11;    //YUKARI YAVAŞ
   }    


  if (ANALOG_LEFT_Y(PSX_PAD1)>240 && ANALOG_LEFT_Y(PSX_PAD1)<256) {
     but_mem = 53;  //AŞAĞI HIZLI
   }

else   if (ANALOG_LEFT_Y(PSX_PAD1)>140 && ANALOG_LEFT_Y(PSX_PAD1)<241 ) {
     but_mem = 51;  //AŞAĞI YAVAŞ
   }
   


 else if (ANALOG_LEFT_X(PSX_PAD1)<30 ) {
     but_mem = 72;  //SOL 
   }




   else   if (ANALOG_LEFT_X(PSX_PAD1)>226 && ANALOG_LEFT_X(PSX_PAD1)<256 ) {
     but_mem = 32;  //SAĞ 
   }

   }
//}
}



void loop() {
  joystick_read();
  radio.write(&but_mem, sizeof(but_mem));
  delay(1);
  
}
