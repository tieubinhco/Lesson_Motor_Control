#include <Encoder.h>

#define ENA 5
#define IN1 7
#define IN2 8

Encoder motor(2,3);
long currentPos=0;

float desiredAngle=90;
float currentAngle=0; 
float err=0;
int pwmValue=0;  //0-255
int direct=0;
float Kp=50;

void setup() {
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  Serial.begin(9600);
  Serial.println("Rotate to the desired angle using proportional controller");
  Serial.println("Press r to set current position to 0 degree");
  while(true)
  {
    char startingChar=Serial.read(); 
    delay(500);
    Serial.print(".");
    if (startingChar=='r')
    {
        Serial.println();
        break;
    }
  }
  motor.write(0);
  Serial.println("Current position is set to 0 degree");
  Serial.println("Press s to start");
  while(true)
  {
    char startingChar=Serial.read(); 
    delay(500);
    Serial.print(".");
    if (startingChar=='s')
    {
        Serial.println();
        break;
    }
  }
  Serial.println("Program started");
}

float convert_to_degree(long currentPulse)
{
  float revolution = float(float(currentPulse)/float(194));
  float degree= revolution * 360;
  return degree;
}

void loop() {

currentPos=motor.read();
currentAngle=convert_to_degree(currentPos);
Serial.print("Degree= \t");
Serial.println(int(currentAngle));

err=desiredAngle-currentAngle;
pwmValue=Kp*err;
direct=0;

if (pwmValue<0)
{
  pwmValue=abs(pwmValue);
  direct=1;
}

if (pwmValue<30) pwmValue=30;
else if(pwmValue>255) pwmValue=255;

digitalWrite(IN1,direct);
digitalWrite(IN2,!direct);
analogWrite(ENA,pwmValue);

}
