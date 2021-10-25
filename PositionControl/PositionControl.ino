#include <Encoder.h>

#define ENA 5
#define IN1 7
#define IN2 8

Encoder motor(2,3);
long pos=0;

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
}

void loop() {
//set zero angle
while 

}
