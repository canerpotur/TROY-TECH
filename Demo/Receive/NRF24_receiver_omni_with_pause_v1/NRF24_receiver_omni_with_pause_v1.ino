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
////first l298n////
const int in1 = 8;   
const int in2 = 9;     
const int in3 = 10;
const int in4 = 11;
const int enA = 5;  //Enable pins for pwms
const int enB = 6;


////second l298n////
const int in5 =  12;
const int in6 =  13;
const int enC = 3;

///shooting/////////
const int shooting_pin = 30;


 const int ShootPin1 = 31;     // Motor sürücümüze bağladığımız pinleri tanımlıyoruz
  const int ShootPin2 = 32;  
  const int ShootPin3 = 33; 

//prev_text for understanding changes
int prev_text = 0;



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

pinMode(in5, OUTPUT); 
pinMode(in6, OUTPUT);  
pinMode(enC, OUTPUT);


pinMode(shooting_pin, OUTPUT);


pinMode(ShootPin1, OUTPUT);  //Tüm pinlerden güç çıkışı olacağı için OUTPUT olarak ayarladık.
  pinMode(ShootPin2, OUTPUT); 
  pinMode(ShootPin3, OUTPUT);  

digitalWrite(ShootPin1,  LOW);  
 digitalWrite(ShootPin3, HIGH);



digitalWrite(shooting_pin,  LOW); 
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

void motor1_ileri(int Speed){  /////////motor1 saat yönünde döner
    analogWrite(enA,  Speed);   
    digitalWrite(in2, LOW);
    digitalWrite(in1,  HIGH);  
  }


void motor2_ileri(int Speed){  /////////motor2 saat yönünde döner
    analogWrite(enB,  Speed);   
    digitalWrite(in4, LOW);
    digitalWrite(in3,  HIGH); 
    }

void motor3_ileri(int Speed){  /////////motor3 saat yönünde döner
    analogWrite(enC,  Speed);   
    digitalWrite(in6, LOW);
    digitalWrite(in5,  HIGH); 
    }
       
void motor1_geri(int Speed){  /////////motor1 saatin tersi yönünde döner
    analogWrite(enA,  Speed);    
    digitalWrite(in2, HIGH);
    digitalWrite(in1,  LOW); 
   }


void motor2_geri(int Speed){  /////////motor2 saatin tersi yönünde döner
    analogWrite(enB,  Speed);  
    digitalWrite(in4, HIGH);
    digitalWrite(in3,  LOW);
   }

void motor3_geri(int Speed){  /////////motor3 saatin tersi yönünde döner
    analogWrite(enC,  Speed);  
    digitalWrite(in6, HIGH);
    digitalWrite(in5,  LOW);
   }   

void dur(){
      analogWrite(enA,  0); 
      analogWrite(enB,  0); 
      analogWrite(enC,  0); 
  }

///////////Motions of HELEN-V///////
void MoveLeft()
{
  motor1_ileri(44);
  motor2_ileri(44);
  motor3_geri(255);
}


void MoveRight()
{
  motor1_geri(44);
  motor2_geri(44);
  motor3_ileri(255);
}

void MoveForward(int Speed2)
{
  motor1_geri(Speed2);
  motor2_ileri(Speed2);
}


void MoveBackward(int Speed2)
{
  motor1_ileri(Speed2);
  motor2_geri(Speed2);
}


void MoveForwardRight(int Speed2)
{
  motor1_geri(Speed2);
  motor3_ileri(Speed2);
}

void MoveBackwardRight(int Speed2)
{
  motor2_geri(Speed2);
  motor3_ileri(Speed2);
}


void MoveForwardLeft(int Speed2)
{
  motor2_ileri(Speed2);
  motor3_geri(Speed2);
}

void MoveBackwardLeft(int Speed2)
{
  motor1_ileri(Speed2);
  motor3_geri(Speed2);
}




void TurnCV(int Speed2)
{
  motor1_geri(Speed2);
  motor2_geri(Speed2);
  motor3_geri(Speed2);
}


void TurnCCV(int Speed2)
{
  motor1_ileri(Speed2);
  motor2_ileri(Speed2);
  motor3_ileri(Speed2);
}

void Shoot()
{/*
 digitalWrite(shooting_pin, HIGH);
  delay(120); 
  digitalWrite(shooting_pin, LOW);

*/
 digitalWrite(ShootPin2, HIGH);
  delay(75); 
  digitalWrite(ShootPin2, LOW);

}

void loop() {
  prev_text=text;
  if (radio.available()) {
      radio.read(&text, sizeof(text));   
  }      
      if(text !=50 && prev_text!= 50)
      {
        if(prev_text != text)
        {
          dur();
          dur();
          delay(10);
        }
      } 
     
        Serial.println(text, DEC);         

          if(text==50)
            dur();


      if(text==11)
         MoveForward(45);
        
     if(text==12)
         MoveForward(155);
     
           if(text==13)
         MoveForward(255);




        
      if(text==21)
         MoveForwardRight(45);
        
     if(text==22)
         MoveForwardRight(155);
     
           if(text==23)
         MoveForwardRight(255);



          if(text==31 || text==32 || text==33 )
          MoveRight();


      if(text==41)
         MoveBackwardRight(45);
        
     if(text==42)
         MoveBackwardRight(155);
     
           if(text==43)
         MoveBackwardRight(255);


    if(text==51)
         MoveBackward(45);
        
     if(text==52)
         MoveBackward(155);
     
           if(text==53)
         MoveBackward(255);

/*
      if(text==61)
         MoveBackwardLeft(30);
        
     if(text==62)
         MoveBackwardLeft(155);
     
           if(text==63)
         MoveBackwardLeft(255);

   */

         

if(text==71 || text==72 || text==73 )
          MoveLeft();

/*
      if(text==81)
         MoveForwardLeft(30);
        
     if(text==82)
         MoveForwardLeft(155);
     
           if(text==83)
         MoveForwardLeft(255);
         */



if(text==101)
         TurnCCV(40);
        
     if(text==102)
         TurnCCV(155);
     
           if(text==103)
         TurnCCV(255);



if(text==111)
         TurnCV(40);
        
     if(text==112)
         TurnCV(155);
     
           if(text==113)
         TurnCV(255);


          
        if(text==99)
         {
          Shoot();
          }
     
  


  
}
