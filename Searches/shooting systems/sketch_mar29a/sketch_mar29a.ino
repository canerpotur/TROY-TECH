const int in1 = 7;     // Motor sürücümüze bağladığımız pinleri tanımlıyoruz
const int in2 = 6;  
const int in3 = 5;     

void setup() 
 
{
pinMode(in1, OUTPUT);  //Tüm pinlerden güç çıkışı olacağı için OUTPUT olarak ayarladık.
pinMode(in2, OUTPUT); 
pinMode(in3, OUTPUT);  

}
 
void loop() 
 
{
digitalWrite(in3, HIGH);
digitalWrite(in2, HIGH);
digitalWrite(in1,  LOW);  

}
