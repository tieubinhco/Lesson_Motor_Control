#include <Encoder.h>
#define IN1 7
#define IN2 8
#define ENA 5
#define RR A0

Encoder motor(2,3); //2 interrupt pins
const int oneRev=194;
long currentEncoder=0;
long previousEncoder=0;
long currentMillis=0;
long previousMillis=0;
int interval=500;  //ms
int direct=1;
float angularSpeed=0;

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(RR,INPUT);
  Serial.begin(9600);
  Serial.println("Reading speed of the motor");
  Serial.println("-----------------------------------------");
}

void loop() {
  int readVolts= analogRead(RR);
  int PWM=map(readVolts,0,1023,0,255);
  analogWrite(ENA,PWM);
  digitalWrite(IN1,direct);
  digitalWrite(IN2,!direct);
  angularSpeed=read_speed();
  Serial.print("Angular speed=  \t");
  Serial.println(angularSpeed);
  delay(100);
}

float read_speed(void)
{
    //read angular speed of the motor
    //return angular speed in rpm
    currentEncoder = motor.read();
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        float rot_speed = (float)((60000/interval)*(currentEncoder - previousEncoder)/oneRev);
        previousEncoder = currentEncoder;
        return rot_speed;
    }
}
