//sender

#include <SoftwareSerial.h>

SoftwareSerial mySerial(4, 5); // RX, TX

int value=123;
int value1=0;
int value2=44;

void setup()
{
  mySerial.begin(1200); // change this to the rate set in rf magic.
}

void loop()
{
    
    mySerial.println(value);
    delay(250);

    mySerial.println(value2);
    delay(250);

    mySerial.println(value1);
    delay(250);

}
