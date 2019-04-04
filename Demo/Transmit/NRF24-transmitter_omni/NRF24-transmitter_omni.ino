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


bool R1_PRESSED = 0;
bool R2_PRESSED = 0;
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

   if (PRESSED_R1(PSX_PAD1)==1) {
     R1_PRESSED = 1;  
   }

if (RELEASED_R1(PSX_PAD1)==1) { 
     R1_PRESSED = 0;  
   }

   if (PRESSED_R2(PSX_PAD1)==1) {
     R2_PRESSED = 1;  
   }

if (RELEASED_R2(PSX_PAD1)==1) { 
     R2_PRESSED = 0;  
   }

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
  
  if (ANALOG_RIGHT_X(PSX_PAD1)<10) {
     but_mem = 103; //TURN CCV FAST
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>9 && ANALOG_RIGHT_X(PSX_PAD1)<50) {
     but_mem = 102;  //TURN CCV NORMAL
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>49 && ANALOG_RIGHT_X(PSX_PAD1)<100) {
     but_mem = 101; //TURN CCV SLOW
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>150 && ANALOG_RIGHT_X(PSX_PAD1)<200) {
     but_mem = 111;  //TURN CV SLOW
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>199 && ANALOG_RIGHT_X(PSX_PAD1)<246) {
     but_mem = 112;   //TURN CV NORMAL
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>245 && ANALOG_RIGHT_X(PSX_PAD1)<256) {
     but_mem = 113;   //TURN CV FAST
   }
  
  }







/*

else
{
if(    (   ANALOG_LEFT_Y(PSX_PAD1)<30  &&   ANALOG_LEFT_X(PSX_PAD1)>4    &&   ANALOG_LEFT_X(PSX_PAD1)<65   )
    || (   ANALOG_LEFT_Y(PSX_PAD1)<30 &&     ANALOG_LEFT_X(PSX_PAD1)>190    &&   ANALOG_LEFT_X(PSX_PAD1)<251   ) 
    || (   ANALOG_LEFT_Y(PSX_PAD1)>225 &&   ANALOG_LEFT_X(PSX_PAD1)>4    &&   ANALOG_LEFT_X(PSX_PAD1)<65    )
    || (   ANALOG_LEFT_Y(PSX_PAD1)>225 &&   ANALOG_LEFT_X(PSX_PAD1)>190   &&   ANALOG_LEFT_X(PSX_PAD1)<251  ))
{


  
  if (ANALOG_LEFT_Y(PSX_PAD1)<30  &&   ANALOG_LEFT_X(PSX_PAD1)>4    &&   ANALOG_LEFT_X(PSX_PAD1)<65    && R2_PRESSED == 1  ) {
      but_mem = 83;//SOL YUKARI CAPRAZ HIZLI;
    }

 else if (ANALOG_LEFT_Y(PSX_PAD1)<30  &&   ANALOG_LEFT_X(PSX_PAD1)>4    &&   ANALOG_LEFT_X(PSX_PAD1)<65  && R1_PRESSED == 1     ) {
      but_mem = 81;//SOL YUKARI CAPRAZ YAVAŞ;
    }

  else    if (ANALOG_LEFT_Y(PSX_PAD1)<30  &&   ANALOG_LEFT_X(PSX_PAD1)>4    &&   ANALOG_LEFT_X(PSX_PAD1)<65      ) {
      but_mem = 82;//SOL YUKARI CAPRAZ NORMAL;
    }

*/


  if (ANALOG_LEFT_Y(PSX_PAD1)<30 &&     ANALOG_LEFT_X(PSX_PAD1)>190    &&   ANALOG_LEFT_X(PSX_PAD1)<251   && R2_PRESSED == 1  ) {
      but_mem = 23;//SAĞ YUKARI CAPRAZ HIZLI;
    }

 else if (ANALOG_LEFT_Y(PSX_PAD1)<30 &&     ANALOG_LEFT_X(PSX_PAD1)>190    &&   ANALOG_LEFT_X(PSX_PAD1)<251   && R1_PRESSED == 1    ) {
      but_mem = 21;//SAĞ YUKARI CAPRAZ YAVAŞ;
    }

 else if (ANALOG_LEFT_Y(PSX_PAD1)<30 &&     ANALOG_LEFT_X(PSX_PAD1)>190    &&   ANALOG_LEFT_X(PSX_PAD1)<251     ) {
      but_mem = 22;//SAĞ YUKARI CAPRAZ NORMAL;
    }




      if (   ANALOG_LEFT_Y(PSX_PAD1)>225 &&   ANALOG_LEFT_X(PSX_PAD1)>4    &&   ANALOG_LEFT_X(PSX_PAD1)<65   && R2_PRESSED == 1   ) {
      but_mem = 63;//SOL AŞAĞI CAPRAZ HIZLI;
    }
   else   if (   ANALOG_LEFT_Y(PSX_PAD1)>225 &&   ANALOG_LEFT_X(PSX_PAD1)>4    &&   ANALOG_LEFT_X(PSX_PAD1)<65   && R1_PRESSED == 1   ) {
      but_mem = 61;//SOL AŞAĞI CAPRAZ YAVAŞ;
    }
    else      if (   ANALOG_LEFT_Y(PSX_PAD1)>225 &&   ANALOG_LEFT_X(PSX_PAD1)>4    &&   ANALOG_LEFT_X(PSX_PAD1)<65      ) {
      but_mem = 62;//SOL AŞAĞI CAPRAZ NORMAL;
    }

    

      if (   ANALOG_LEFT_Y(PSX_PAD1)>225 &&   ANALOG_LEFT_X(PSX_PAD1)>190   &&   ANALOG_LEFT_X(PSX_PAD1)<251   && R2_PRESSED == 1  ) 
      but_mem = 43;//SAĞ AŞAĞI CAPRAZ HIZLI;

   else if (   ANALOG_LEFT_Y(PSX_PAD1)>225 &&   ANALOG_LEFT_X(PSX_PAD1)>190   &&   ANALOG_LEFT_X(PSX_PAD1)<251  && R1_PRESSED == 1   ) 
      but_mem = 41;//SAĞ AŞAĞI CAPRAZ YAVAŞ;

  else  if (   ANALOG_LEFT_Y(PSX_PAD1)>225 &&   ANALOG_LEFT_X(PSX_PAD1)>190   &&   ANALOG_LEFT_X(PSX_PAD1)<251    ) 
      but_mem = 42;//SAĞ AŞAĞI CAPRAZ NORMAL;
      
    
   }
else{
    if (ANALOG_LEFT_Y(PSX_PAD1)>94 && ANALOG_LEFT_Y(PSX_PAD1)<141) {
     but_mem = 50; //BOŞ
   }

if (ANALOG_LEFT_Y(PSX_PAD1)<10 && R2_PRESSED == 1) {
     but_mem = 13;    //YUKARI HIZLI
   }

else if (ANALOG_LEFT_Y(PSX_PAD1)<10 && R1_PRESSED == 1) {
     but_mem = 11;    //YUKARI YAVAŞ
   }    
   
else  if (ANALOG_LEFT_Y(PSX_PAD1)<10) {
     but_mem = 12;    //YUKARI NORMAL 
   }



  if (ANALOG_LEFT_Y(PSX_PAD1)>245 && ANALOG_LEFT_Y(PSX_PAD1)<256 && R2_PRESSED == 1) {
     but_mem = 53;  //AŞAĞI HIZLI
   }

else   if (ANALOG_LEFT_Y(PSX_PAD1)>245 && ANALOG_LEFT_Y(PSX_PAD1)<256 && R1_PRESSED == 1) {
     but_mem = 51;  //AŞAĞI YAVAŞ
   }
   
 else  if (ANALOG_LEFT_Y(PSX_PAD1)>245 && ANALOG_LEFT_Y(PSX_PAD1)<256) {
     but_mem = 52;  //AŞAĞI NORMAL
   }


if (ANALOG_LEFT_X(PSX_PAD1)<10 && R2_PRESSED == 1) {
     but_mem = 73;  //SOL HIZLI
   }


 else if (ANALOG_LEFT_X(PSX_PAD1)<10 && R1_PRESSED == 1) {
     but_mem = 71;  //SOL YAVAŞ
   }

 else if (ANALOG_LEFT_X(PSX_PAD1)<10) {
     but_mem = 72;  //SOL NORMAL
   }


  if (ANALOG_LEFT_X(PSX_PAD1)>245 && ANALOG_LEFT_X(PSX_PAD1)<256 && R2_PRESSED == 1) {
     but_mem = 33;  //SAĞ HIZLI
   }

   else   if (ANALOG_LEFT_X(PSX_PAD1)>245 && ANALOG_LEFT_X(PSX_PAD1)<256 && R1_PRESSED == 1) {
     but_mem = 31;  //SAĞ YAVAŞ
   }
   

  else if (ANALOG_LEFT_X(PSX_PAD1)>245 && ANALOG_LEFT_X(PSX_PAD1)<256) {
     but_mem = 32;  //SAĞ NORMAL
   }
}
}
}


void loop() {
  joystick_read();
  radio.write(&but_mem, sizeof(but_mem));
  delay(1);
  
}
