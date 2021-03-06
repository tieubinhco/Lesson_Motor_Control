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
int interval=10;  //ms

float currentSpeed=0;
float previousSpeed=0;
float vFilt=0;
float vpreFilt=0;
float v=0;
float desiredSpeed=50;
float error=0;
int pwmValue=100; //0 - 255 dec 0x00 - 0xFF hex
int direct=1;  //1 clockwise  //0 counter-clockwise
float Kp=1;  //controlsignal = Kp*error


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
  v=read_speed();
  vFilt=0.854*vFilt+0.0728*v+0.0728*vpreFilt;
  vpreFilt=v;
  
  currentSpeed=vFilt;
  
  error= desiredSpeed-currentSpeed;
  pwmValue=Kp*error;
  direct=1;

  if (pwmValue<0) 
  {
    pwmValue=abs(pwmValue);
    direct=0;
  }

  if (pwmValue>255) pwmValue=255;
    
  analogWrite(ENA,pwmValue);
  digitalWrite(IN1,direct);
  digitalWrite(IN2,!direct);
//  Serial.print("Current speed=\t");
  Serial.print(int(currentSpeed));
//  Serial.print("\tDesired speed=\t");
Serial.print(" ");
  Serial.println(int(desiredSpeed));
}

float read_speed(void)
{
    //read angular speed of the motor
    //return angular speed in rpm
    currentEncoder = motor.read();
    currentMillis = millis();
    long deltaT=(currentMillis - previousMillis);
    if (deltaT>=interval)
    {
        float rot_speed = (float)((60000/deltaT)*(currentEncoder - previousEncoder)/oneRev);
        previousEncoder = currentEncoder;
        previousMillis = currentMillis;
        previousSpeed=rot_speed;
        return rot_speed;
    }
    else 
    {
      return previousSpeed;
    }

}
