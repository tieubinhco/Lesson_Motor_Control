#include <Encoder.h>
#define IN1 7
#define IN2 8
#define ENA 5
#define RR A0


Encoder motor(2,3); //2 interrupt pins
const int oneRev=194;
long currentPos=0;
char calibButton=0;

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(RR,INPUT);
  Serial.begin(9600);
  Serial.println("Hello, this is a LAB");
  Serial.println("-----------------------------------------");
  Serial.println("Press r to set this position as 0 degree");
  while (true)
  {
      calibButton=Serial.read();
      if (calibButton=='r')
      {
          motor.write(0);
          break;
      }
  }
  Serial.println("-----------------------------------------");
  Serial.println("Current position is set to 0 degree");
  Serial.println("-----------------------------------------");
  Serial.println("Program starts");
  Serial.println("-----------------------------------------");
}

float desiredAngle=90;
float currentAngle=0;
float error=0;
int pwmValue=100; //0 - 255 dec 0x00 - 0xFF hex
int direct=1;  //1 clockwise  //0 counter-clockwise
float Kp=1;  //controlsignal = Kp*error

int potentioMeter=0;


void loop() {
  //read value from potentiometer
potentioMeter=analogRead(RR);
//convert to degree setpoint
desiredAngle=map(potentioMeter,0,1023,0,360);

currentPos=motor.read();
currentAngle=convert_to_degree(currentPos);
//wrap angle
currentAngle=int(currentAngle)%360;
Serial.print("Degree= \t");
Serial.print(int(currentAngle));
Serial.print("\t Setpoint= \t");
Serial.println(desiredAngle);
error=desiredAngle-currentAngle; 
pwmValue=Kp*error; 
direct=1;

if (pwmValue<0)
{
  pwmValue=abs(pwmValue); //pwmValue is always positive 0-255
  direct=0;
}

// 30<=pwmValue <=255
if (pwmValue>255) pwmValue=255;
// no lower bound

digitalWrite(IN1, direct); 
digitalWrite(IN2, !direct); 
analogWrite(ENA,pwmValue);
}

float convert_to_degree(long currentPulse)
{
 // 1 rev = 194 pulses = 360 degrees
 float revolution = float(currentPulse)/float(oneRev);
 float degree = revolution*360;
 return degree;
}
