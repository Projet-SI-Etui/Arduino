// connect motor controller pins to Arduino digital pins
// motor one
int enA = 4;
int in1 = 3;
int in2 = 2;
void setup()
{
  //Initialize Serial Monitor
  Serial.begin(9600);
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  analogWrite(enA, 255); 
}

void loop()
{  
  //le moteur tourne
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(2000);
  //stop le moteur
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(1000);
  //le moteur tourne dans le sens inverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);
  //stop le moteur
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(1000);
}
