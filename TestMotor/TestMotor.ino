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
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW); 
  analogWrite(ENA,100); //1 byte value 0 - 255 dec  0x00 - 0xFF HEX
}
