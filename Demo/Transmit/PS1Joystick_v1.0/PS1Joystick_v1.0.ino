/*
This example demonstrates all features of the library.

- The controller starts up in ANALOG mode, and is locked
  (user cannot switch modes using the ANALOG button)
  
- SQUARE and CROSS buttons toggle between ANALOG and DIGITAL modes.
  also, at this point the lock is released.

Pin layouts are hardcoded in GPSX.c.
For function details, refer to documents attached to this library.
*/

#include <GPSXClass.h>

uint8_t but_mem = 0;
void setup()
{
  Serial.begin(9600);
  PSX.mode(PSX_PAD1, MODE_DIGITAL, MODE_LOCK);
  
  // Poll current state once.
  PSX.updateState(PSX_PAD1);
}




void loop()
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
