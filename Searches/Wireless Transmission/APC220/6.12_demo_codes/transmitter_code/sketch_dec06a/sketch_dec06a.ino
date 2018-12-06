//sender

#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX

uint8_t value;
void setup()
{
  Serial.begin(9600); // make sure serial monitor is set to this rate
  mySerial.begin(9600); // change this to the rate set in rf magic.
}

void loop()
{
    value=0xA3;
    delay(300);
    mySerial.println(value);


    value=0xB7;
    mySerial.println(value);
    delay(300);
  

}
