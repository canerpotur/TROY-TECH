/*
Simple transmitter, just sends 12-byte packet continously
nRF24L01 library: https://github.com/gcopeland/RF24

nRF24L01 connections 
 1 - GND
 2 - VCC 3.3V !!! Ideally 3.0v, definitely not 5V
 3 - CE to Arduino pin 9
 4 - CSN to Arduino pin 10
 5 - SCK to Arduino pin 13
 6 - MOSI to Arduino pin 11
 7 - MISO to Arduino pin 12
 8 - UNUSED
 
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut =  0xE8E8F0F0E1LL;

// The sizeof this struct should not exceed 32 bytes
struct PacketData {
  long lon;
  long lat;
  int32_t altitude;
};

PacketData data;

RF24 radio(9, 10);

void setup() {

  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  
}

void loop() {
    radio.write(&data, sizeof(PacketData));
}


