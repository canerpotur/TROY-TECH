#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);

const byte address[6] = "00001";
uint8_t text;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
   radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
}

void loop() {
  text = 0xA3;
  radio.write(&text, sizeof(text));
  delay(300);
  

  text = 0xB7;
  radio.write(&text, sizeof(text));
  delay(300);
}
