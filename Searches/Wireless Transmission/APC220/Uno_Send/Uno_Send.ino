//uno_send data

uint8_t value;
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {


  value = 0xA3;
  Serial.print(value);
  Serial.flush();
  delay(500);

  value = 0xB7;
  Serial.print(value);
  Serial.flush();
  delay(500);

}
