#define RR A0


void setup() {
  pinMode(RR,INPUT);
  Serial.begin(9600);
  Serial.println("Reading value Vout");
  Serial.println("-----------------------------------------");
}


void loop() {
int readVolts= analogRead(RR);
float voltage= readVolts * (5.0 / 1023.0);
Serial.println(voltage);
delay(100);
}
