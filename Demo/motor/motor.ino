
const int in1 = 8;    
const int in2 = 9;     
const int enA = 5; 

void setup() 
 
{
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT);  
pinMode(enA, OUTPUT);

}
 
void loop() 
{

analogWrite(enA,  255);   //1. motor 255 ile tam hızda dönüyor...  
digitalWrite(in2, LOW);
digitalWrite(in1,  HIGH);  
 

}
 
