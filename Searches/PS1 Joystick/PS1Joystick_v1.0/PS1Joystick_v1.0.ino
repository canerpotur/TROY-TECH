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


void setup()
{
  Serial.begin(19200);
  PSX.mode(PSX_PAD1, MODE_ANALOG, MODE_LOCK);
  
   // Poll current state once.
  PSX.updateState(PSX_PAD1);
}
int xxx;
void loop()
{
  PSX.updateState(PSX_PAD1);

 
  Serial.print(ANALOG_LEFT_X(PSX_PAD1));
  Serial.print("  ");
  Serial.print(ANALOG_LEFT_Y(PSX_PAD1));
  Serial.print("  ");
  Serial.print(ANALOG_RIGHT_X(PSX_PAD1));
  Serial.print("  ");
  Serial.println(ANALOG_RIGHT_Y(PSX_PAD1)); 



  if (PRESSED_CIRCLE(PSX_PAD1)) {
    Serial.println("Pressed circle");
   }

  if (RELEASED_CIRCLE(PSX_PAD1)) {
    Serial.println("Released circle");
  }    

  if (PRESSED_SQUARE(PSX_PAD1)) {
    Serial.println("Pressed square");
    PSX.mode(PSX_PAD1, MODE_DIGITAL, MODE_UNLOCK);
  }

  if (RELEASED_SQUARE(PSX_PAD1)) {
    Serial.println("Released square");
  }

  if (PRESSED_CROSS(PSX_PAD1)) {
    Serial.println("Pressed cross");
    PSX.mode(PSX_PAD1, MODE_ANALOG, MODE_UNLOCK);
  }

  if (RELEASED_CROSS(PSX_PAD1)) {
    Serial.println("Released cross");
  }

  if (IS_DOWN_TRIANGLE(PSX_PAD1)) {
  }

  if (PRESSED_TRIANGLE(PSX_PAD1)) {
    Serial.println("Pressed triangle");
  }

  if (RELEASED_TRIANGLE(PSX_PAD1)) {
    Serial.println("Released triangle");
  }
}
