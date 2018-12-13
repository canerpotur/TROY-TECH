#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <GPSXClass.h>


RF24 radio(2,8);

const byte address[6] = "00001";
uint8_t but_mem = 0b10000;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setRetries(15, 15); 
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  PSX.mode(PSX_PAD1, MODE_DIGITAL, MODE_LOCK);
  PSX.updateState(PSX_PAD1);
}

void joystick_read()
{
  PSX.updateState(PSX_PAD1);  
  if (PRESSED_TRIANGLE(PSX_PAD1)) {
    but_mem |= 0b10001;
   }
  if (RELEASED_TRIANGLE(PSX_PAD1)) {
    but_mem &= 0b11110;
  }    
  if (PRESSED_SQUARE(PSX_PAD1)) {
    but_mem |= 0b11000; 
  }
  if (RELEASED_SQUARE(PSX_PAD1)) {
    but_mem &= 0b10111;
  }
  if (PRESSED_CROSS(PSX_PAD1)) {
    but_mem |= 0b10100;
  }
  if (RELEASED_CROSS(PSX_PAD1)) {
    but_mem &= 0b11011;
  }
  if (PRESSED_CIRCLE(PSX_PAD1)) {
    but_mem |= 0b10010;
  }
  if (RELEASED_CIRCLE(PSX_PAD1)) {
    but_mem &= 0b11101;
  }
  Serial.println(but_mem, BIN);

}


void loop() {
  joystick_read();
  radio.write(&but_mem, sizeof(but_mem));
  delay(1);
  
}
