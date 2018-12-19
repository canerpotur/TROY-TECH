/*
Simple receiver to display how many packets per second are being received
nRF24L01 library: https://github.com/gcopeland/RF24
I2C OLED screen library: https://github.com/olikraus/u8glib

nRF24L01 connections 
 1 - GND
 2 - VCC 3.3V !!! Ideally 3.0v, definitely not 5V
 3 - CE to Arduino pin 9
 4 - CSN to Arduino pin 10
 5 - SCK to Arduino pin 13
 6 - MOSI to Arduino pin 11
 7 - MISO to Arduino pin 12
 8 - UNUSED
 
OLED connections
 GND - GND
 VCC - VCC
 SDA - Arduino pin A4
 SCL - Arduino pin A5
 
*/

#include <SPI.h>
#include "U8glib.h"
#include <nRF24L01.h>
#include <RF24.h>

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_NO_ACK|U8G_I2C_OPT_FAST);	// Fast I2C / TWI

const uint64_t pipeIn =  0xE8E8F0F0E1LL;

RF24 radio(9, 10);

// The sizeof this struct should not exceed 32 bytes
struct PacketData {
  unsigned long hours;
  unsigned long minutes;
  unsigned long seconds;
};

PacketData data;

/**************************************************/

int packetCounts[10];
int packetCountIndex = 0;
int packetCountTotal = 0;

#define AVG_SECONDS 10

int avgs[AVG_SECONDS];
int avgIndex = 0;
unsigned long avgTotal = 0;

void setup()
{
  Serial.begin(115200);
  // Set up radio module
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(false);
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

  u8g.setColorIndex(1);
  u8g.setFont(u8g_font_fur11);

  memset(&data, 0, sizeof(PacketData));  
  memset( packetCounts, 0, sizeof(packetCounts) );
  memset( avgs, 0, sizeof(avgs) );
}

unsigned long packetsRead = 0;
unsigned long lastScreenUpdate = 0;
unsigned long lastAvgUpdate = 0;
unsigned long lastRecvTime = 0;
unsigned long drops = 0;

/**************************************************/

void recvData()
{  
  while ( radio.available() ) {        
    radio.read(&data, sizeof(PacketData));
    packetsRead++;
    lastRecvTime = millis();
  }
}

/**************************************************/

char ppsBuf[16];
char avgBuf[16];
char hmsBuf[16];

void draw() {
  u8g.drawStr( 2, 24, ppsBuf);
  u8g.drawStr( 2, 40, avgBuf);
  u8g.drawStr( 2, 56, hmsBuf);
}

void updateScreen()
{  
  unsigned long now = millis();
  if ( now - lastScreenUpdate < 100 )
    return;
    
  // moving average over 1 second
  packetCountTotal -= packetCounts[packetCountIndex];
  packetCounts[packetCountIndex] = packetsRead;
  packetCountTotal += packetsRead;

  packetCountIndex = (packetCountIndex + 1) % 10;
  packetsRead = 0;
  
  sprintf(ppsBuf, "PPS: %d", packetCountTotal);
  sprintf(avgBuf, "AVG: %ld", avgTotal / AVG_SECONDS);
  sprintf(hmsBuf, "%02ld:%02ld:%02ld", data.hours, data.minutes, data.seconds);

  u8g.firstPage();
  do {
    draw();
  } 
  while( u8g.nextPage() );
  
  lastScreenUpdate = millis();

  if ( now - lastAvgUpdate >= 1000 ) {    
    // moving average of 1 second moving average
    avgTotal -= avgs[avgIndex];
    avgs[avgIndex] = packetCountTotal;
    avgTotal += packetCountTotal;
  
    avgIndex = (avgIndex + 1) % AVG_SECONDS;
    lastAvgUpdate = millis();
  }
}

/**************************************************/

void loop()
{
  recvData();
  updateScreen();
}







