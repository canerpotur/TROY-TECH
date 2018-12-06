#include <SoftwareSerial.h>

SoftwareSerial mySerial(8, 9); // RX, TX

void setup()
{
  Serial.begin(9600);  // make sure serial monitor is set to this rate
  mySerial.begin(9600); // change this to the rate set in rf magic.
}


void loop()
{
  if(mySerial.available())
  {
     Serial.print(char(mySerial.read()));     
  }
  
}
