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

void setup() {
  // put your setup code here, to run once:
 
pinMode(in1, OUTPUT); 
pinMode(in2, OUTPUT);  
pinMode(enA, OUTPUT);

pinMode(in3, OUTPUT); 
pinMode(in4, OUTPUT);  
pinMode(enB, OUTPUT);

pinMode(in5, OUTPUT); 
pinMode(in6, OUTPUT);  
pinMode(enC, OUTPUT);
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
  motor1_ileri(200);
  motor2_ileri(200);
  motor3_geri(100);
}


void MoveRight()
{
  motor1_geri(200);
  motor2_geri(200);
  motor3_ileri(100);
}

void MoveForward()
{
  motor1_ileri(200);
  motor2_ileri(200);
}


void MoveBackward()
{
  motor1_geri(200);
  motor2_geri(200);
}

void TurnCV()
{
  motor1_ileri(200);
  motor2_ileri(200);
  motor3_ileri(200);
}


void TurnCCV()
{
  motor1_geri(200);
  motor2_geri(200);
  motor3_geri(200);
}


void loop() {



  
 
  }

  
