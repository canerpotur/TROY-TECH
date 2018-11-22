//uno_send data

boolean flo = 0;
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, flo);
  Serial.println(flo);
  Serial.flush();
  delay(2000);
  flo = !flo;

}
