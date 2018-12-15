#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,2);
uint8_t text;
const byte address[6] = "00001";
const int in1 = 3;    
const int in2 = 4;     
const int enA = 5; 

const int in3 = 8;    
const int in4 = 9;
const int enB = 10;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0,address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT);  
pinMode(enA, OUTPUT);

pinMode(in3, OUTPUT); 
pinMode(in4, OUTPUT);  
pinMode(enB, OUTPUT);

}

1b0001.0000



void sol_ileri(){
    analogWrite(enA,  255);   
    digitalWrite(in2, LOW);
    digitalWrite(in1,  HIGH);  


    analogWrite(enB,  255);   
    digitalWrite(in3, LOW);
    digitalWrite(in4,  HIGH); 
  }


void sag_ileri(){
    analogWrite(enB,  200);   
    digitalWrite(in3, LOW);
    digitalWrite(in4,  HIGH); 
    }


void sol_geri(){
    analogWrite(enA,  200);    
    digitalWrite(in2, HIGH);
    digitalWrite(in1,  LOW); 
   }


void sag_geri(){
    analogWrite(enB,  200);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4,  LOW);
   }

void dur(){
      analogWrite(enA,  0); 
      analogWrite(enB,  0); 
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
      
        if(text==0b10001)
         {
        sag_ileri();
        sol_ileri();
          }
        
        if(text==0b10100)
         {
        sag_geri();
        sol_geri();
        }
        
        
        if(text==0b10010)
         {
        sag_geri();
        sol_ileri();
        }
  
        if(text==0b11000)
         {
        sag_ileri();
        sol_geri();
        }
        
        
        if(text==0b10000)
        {
        dur();
        }

  }

  
}
