#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <GPSXClass.h>


RF24 radio(9,8);

const byte address[6] = "7";
uint8_t but_mem = 50;
bool mutex_lock = 0;
bool mutex_lock_x = 0;
bool mutex_lock_right = 0;
bool mutex_lock_left = 0;
int flag_op;  //op:  1=X, 2=R1, 3=L1


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

  if(mutex_lock_x == 1 || mutex_lock_left == 1 || mutex_lock_right == 1)
      mutex_lock = 1;
 if(mutex_lock == 1)
     {

      if(mutex_lock_x == 1)
        but_mem = 99; //X
      else if(mutex_lock_right == 1)
        but_mem = 61; //R1
      else if(mutex_lock_left == 1)
        but_mem = 62; //L1  
      }
  
  if(mutex_lock == 0){
  
  
  if (ANALOG_LEFT_Y(PSX_PAD1)<10) {
     but_mem = 23;
   }

  if (ANALOG_LEFT_Y(PSX_PAD1)>9 && ANALOG_LEFT_Y(PSX_PAD1)<50) {
     but_mem = 22;
   }

  if (ANALOG_LEFT_Y(PSX_PAD1)>49 && ANALOG_LEFT_Y(PSX_PAD1)<95) {
     but_mem = 21;
   }

  if (ANALOG_LEFT_Y(PSX_PAD1)>94 && ANALOG_LEFT_Y(PSX_PAD1)<141) {
     but_mem = 50;
   }

  if (ANALOG_LEFT_Y(PSX_PAD1)>140 && ANALOG_LEFT_Y(PSX_PAD1)<190) {
     but_mem = 11;
   }

  if (ANALOG_LEFT_Y(PSX_PAD1)>189 && ANALOG_LEFT_Y(PSX_PAD1)<246) {
     but_mem = 12;
   }

  if (ANALOG_LEFT_Y(PSX_PAD1)>245 && ANALOG_LEFT_Y(PSX_PAD1)<256) {
     but_mem = 13;
   }
/******* right analog ******/
//if( but_mem != 50)
//{
if (ANALOG_RIGHT_X(PSX_PAD1)<10) {
     but_mem = 43;
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>9 && ANALOG_RIGHT_X(PSX_PAD1)<50) {
     but_mem = 42;
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>49 && ANALOG_RIGHT_X(PSX_PAD1)<100) {
     but_mem = 41;
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>150 && ANALOG_RIGHT_X(PSX_PAD1)<200) {
     but_mem = 31;
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>199 && ANALOG_RIGHT_X(PSX_PAD1)<246) {
     but_mem = 32;
   }

  if (ANALOG_RIGHT_X(PSX_PAD1)>245 && ANALOG_RIGHT_X(PSX_PAD1)<256) {
     but_mem = 33;
   }
  }


 if (PRESSED_R1(PSX_PAD1)==1) {//Move right
     mutex_lock = 1;
     mutex_lock_right=1;
     flag_op = 2;

   }
    if (RELEASED_R1(PSX_PAD1)==1) {//Move right
     mutex_lock = 0;   
     mutex_lock_right=0;
   }
   
 
  if (PRESSED_L1(PSX_PAD1)==1) {//Move Left
    mutex_lock = 1;
    mutex_lock_left=1;
    flag_op = 3;
    
   }
  if (RELEASED_L1(PSX_PAD1)==1) {//Move Left
    mutex_lock = 0;
    mutex_lock_left=0;
   }

   if (PRESSED_CROSS(PSX_PAD1)==1) { //shoot
     mutex_lock = 1;
     mutex_lock_x=1;
     flag_op = 1;
  
   }
    if (RELEASED_CROSS(PSX_PAD1)==1) { //shoot
     mutex_lock = 0;
     mutex_lock_x=0;
   }
   
  Serial.println(but_mem);

}


void loop() {
  joystick_read();
  radio.write(&but_mem, sizeof(but_mem));
  delay(1);
  
}
