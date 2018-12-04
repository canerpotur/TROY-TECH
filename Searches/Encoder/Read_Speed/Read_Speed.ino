const byte pin_a = 2;   //for encoder pulse A
const byte pin_b = 3;   //for encoder pulse B
int encoder = 0;
int m_direction = 0;
double pv_speed = 0;
int timer1_counter; //for timer

void setup() {
  pinMode(pin_a,INPUT_PULLUP);
  pinMode(pin_b,INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(pin_a), detect_a, RISING);
  // start serial port at 9600 bps:
  Serial.begin(9600);
  //--------------------------timer setup
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 171430;   // preload timer   
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
  //--------------------------timer setup
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
void loop() {
    Serial.print("speed (rpm) is : ");
    Serial.print(pv_speed);         //Print speed value to Computer
    Serial.print("  --  ");
    Serial.print("Direction = ");
    Serial.println(m_direction);
    delay(10);
}

void detect_a() {
  encoder+=1;
  m_direction = digitalRead(pin_b);
}
ISR(TIMER1_OVF_vect)        // interrupt service routine - tick every 0.1sec
{
  TCNT1 = timer1_counter;   // set timer
  pv_speed = 60*(encoder/200.0)/0.01;
  encoder=0;
}
