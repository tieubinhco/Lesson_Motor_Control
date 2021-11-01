#define RR A0


void setup() {
  pinMode(RR,INPUT);
  Serial.begin(9600);
  Serial.println("Reading value Vout");
  Serial.println("-----------------------------------------");
}


void loop() {
int readVolts= analogRead(RR);
Serial.println(readVolts);
delay(100);
}
