#define IN1 7
#define IN2 8
#define ENA 5


void setup() {
  // put your setup code here, to run once:
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH); 
  analogWrite(ENA,255);

}
