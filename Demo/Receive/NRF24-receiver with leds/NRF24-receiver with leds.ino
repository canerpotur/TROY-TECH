#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);
 uint8_t text;
const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
   radio.setPayloadSize(2);
  radio.openReadingPipe(0,address);
  
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop() {
  if (radio.available()) {
radio.read(&text, sizeof(text));
 if(text!=0b10000)   
 {
    
       Serial.print(text, BIN);
       Serial.println("....."); 
 }
else
Serial.println("Wait for command..");


if(bitRead(text,0)) 
digitalWrite(2,HIGH);
else 
digitalWrite(2,LOW);

if(bitRead(text,1)) 
digitalWrite(3,HIGH);
else 
digitalWrite(3,LOW);

if(bitRead(text,2)) 
digitalWrite(4,HIGH);
else 
digitalWrite(4,LOW);

if(bitRead(text,3)) 
digitalWrite(5,HIGH);
else 
digitalWrite(5,LOW);


  }

/*else
{
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  
  
  
  
  }

*/
  
}
