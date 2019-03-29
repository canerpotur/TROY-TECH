#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*
 * green -> 52
 * purple ->50
 * blue ->51
 * SPI for Mega: https://www.arduino.cc/en/Reference/SPI
 */

RF24 radio(48,49);
uint8_t text;
const byte address[6] = "7";
const int in1 = 3;    
const int in2 = 4;     
const int enA = 5; 

const int in3 = 8;    
const int in4 = 9;
const int enB = 6;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.setPayloadSize(1);
  radio.begin();
  
  radio.openReadingPipe(1,address);
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

/***** timer ***///
  TCCR1A = 0;
  TCCR1B = 0;    // tüm TCCR1B yazmacını sıfırlar
 
  // timer1 için overflow interruptını açar
  TIMSK1 |= (1 << TOIE1); //Kullandığınız işlemcide bu timer yoksa farklı bir timer ilede aynı ayarları set edebilirsiniz
 
  // CS11 bitini atadık vede timer şuanda clock hızında çalışacaktır.
  TCCR1B |= (1 << CS12); //  böleni 8 olarak ayarladık. Yani 16/8 = 2 MHZ
  TIMSK1 |= (1 << TOIE1); // Overflow kesmesini açarız

}

ISR(TIMER1_OVF_vect)
{
 
  text=50;
 
}

void ileri(int x){
    if(x==23)    //Low speed
    {         
      digitalWrite(in2, LOW);
      digitalWrite(in1,  HIGH);   
      digitalWrite(in3, LOW);
      digitalWrite(in4,  HIGH);       
      analogWrite(enA,  255);
      analogWrite(enB,  255);      
      }
      if(x==22) //Average speed
      {      
      digitalWrite(in2, LOW);
      digitalWrite(in1,  HIGH);  
      digitalWrite(in3, LOW);
      digitalWrite(in4,  HIGH); 
       analogWrite(enA,  55);  
       analogWrite(enB,  55);        
      } 
      if(x==21)   //Low speed
      {         
      digitalWrite(in2, LOW);
      digitalWrite(in1,  HIGH);   
      digitalWrite(in3, LOW);
      digitalWrite(in4,  HIGH); 
      analogWrite(enA,  25);
      analogWrite(enB,  25); 
      }   
  }

void geri(int x){
    if(x==11)     //Low speed
    {
      analogWrite(enA,  25);    
      digitalWrite(in2, HIGH);
      digitalWrite(in1,  LOW);  
      analogWrite(enB,  25);  
      digitalWrite(in3, HIGH);
      digitalWrite(in4,  LOW);
      }
    if(x==12)   //Average speed
    {
      analogWrite(enA,  55);    
      digitalWrite(in2, HIGH);
      digitalWrite(in1,  LOW);  
      analogWrite(enB,  55);  
      digitalWrite(in3, HIGH);
      digitalWrite(in4,  LOW);
      }
    if(x==13) //High speed
    {
      analogWrite(enA,  255);    
      digitalWrite(in2, HIGH);
      digitalWrite(in1,  LOW);  
      analogWrite(enB,  255);  
      digitalWrite(in3, HIGH);
      digitalWrite(in4,  LOW);
      }
   }

void sol(int x){
    if(x==43) //High speed
    {
    analogWrite(enB,  255);   
    digitalWrite(in3, LOW);
    digitalWrite(in4,  HIGH);
    analogWrite(enA,  255);   
    digitalWrite(in2, HIGH);
    digitalWrite(in1,  LOW);      
      }
      if(x==42)  //Average speed
      {
    analogWrite(enB,  55); 
    digitalWrite(in3, LOW);
    digitalWrite(in4,  HIGH);
    analogWrite(enA,  55);   
    digitalWrite(in2, HIGH);
    digitalWrite(in1,  LOW);      
      } 
      if(x==41)  //Low speed
      {
    analogWrite(enB,  25); 
    digitalWrite(in3, LOW);
    digitalWrite(in4,  HIGH);
    analogWrite(enA,  25);   
    digitalWrite(in2, HIGH);
    digitalWrite(in1,  LOW);      
      }       
}

 void sag(int x){
    if(x==33)  //High speed
    {
    analogWrite(enA,  255);  
    digitalWrite(in2, LOW);
    digitalWrite(in1,  HIGH); 
    analogWrite(enB,  255);  
    digitalWrite(in3, HIGH);
    digitalWrite(in4,  LOW);
      }
      if(x==32)  //Average speed
      {
    analogWrite(enA,  55);  
    digitalWrite(in2, LOW);
    digitalWrite(in1,  HIGH);  
      analogWrite(enB,  55); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4,  LOW);      
      } 
      if(x==31)  //Low speed
      {
    analogWrite(enA,  25); 
    digitalWrite(in2, LOW);
    digitalWrite(in1,  HIGH);  

      analogWrite(enB,  25); 
    digitalWrite(in3, HIGH);
    digitalWrite(in4,  LOW);
      }   
  }


void sol_ileri(){
    analogWrite(enA,  200);   
    digitalWrite(in2, LOW);
    digitalWrite(in1,  HIGH);  
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
  }      
        Serial.println(text, DEC); 
        

          if(text==50)
          {
            dur();
          }  
  
        if(text==21 || text==22 || text==23 )
         {
          ileri(text);
          }

           if(text==11 || text==12 || text==13 )
         {
          geri(text);
          }

          if(text==43 || text==42 || text==41 )
         {
          sol(text);
          }

          if(text==33 || text==32 || text==31 )
         {
          sag(text);
          }
     
  


  
}
