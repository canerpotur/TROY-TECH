//UNO_Receive data

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  char Data = '2';
  if (Serial.available() > 0) {
    Data = Serial.read();
    Serial.print(Data);
    Serial.flush();
    
   // Serial.println();
  }
  switch ( Data ) {
    case  '0':
      digitalWrite(13, LOW);// blink0();
      break;

    case  '1':
      digitalWrite(13, HIGH);//blink1();
      break;
    default :
      break;
  }
}
