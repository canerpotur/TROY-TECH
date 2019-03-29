/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

// digital pin 2 has a pushbutton attached to it. Give it a name:
  int kaan;
  const int in1 = 7;     // Motor sürücümüze bağladığımız pinleri tanımlıyoruz
  const int in2 = 6;  
  const int in3 = 5;  

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(in1, OUTPUT);  //Tüm pinlerden güç çıkışı olacağı için OUTPUT olarak ayarladık.
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT);  
  
}

// the loop routine runs over and over again forever:
void loop() {
    digitalWrite(in1,  LOW);  
    digitalWrite(in3, HIGH);
  kaan = Serial.read();
  if(kaan != -1)
  {
  
  digitalWrite(in2, HIGH);
  Serial.println(kaan);
  delay(120); 
  digitalWrite(in2, LOW);
  }
  delay(10);        
 /* 
  */
}
