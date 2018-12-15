
const int in1 = 3;    
const int in2 = 4;     
const int enA = 5; 

const int in3 = 8;    
const int in4 = 9;
const int enB = 10;

void setup() 
 
{
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT);  
pinMode(enA, OUTPUT);

pinMode(in3, OUTPUT); 
pinMode(in4, OUTPUT);  
pinMode(enB, OUTPUT);

}
 
void loop() 
{

analogWrite(enA,  200);   //1. motor 255 ile tam hızda dönüyor...  
digitalWrite(in2, LOW);
digitalWrite(in1,  HIGH);  

analogWrite(enB,  200);   //1. motor 255 ile tam hızda dönüyor...  
digitalWrite(in3, LOW);
digitalWrite(in4,  HIGH);  
 

}
 
