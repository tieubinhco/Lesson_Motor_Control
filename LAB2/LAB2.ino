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
int interval=10;  //ms  // sample time 
int direct=1;
float angularSpeed=0;
float previousSpeed=0;
long deltaT=0;

float vFilt=0;
float vpreFilt=0;
float v=0;

float desiredSpeed=30;
float currentSpeed=0;

//proportional controller Kp
float error=0;
float Kp=0.35;

//integral controller Ki
float Ki=0;
float errorIntegral=0;

int pwmValue = 0;

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  Serial.begin(9600);
  Serial.println("Reading speed of the motor");
  Serial.println("-----------------------------------------");
}

void loop() {
  //Read speed
  //FILTER 
  v=read_speed();
  vFilt=0.854*vFilt+0.0728*v+0.0728*vpreFilt;
  vpreFilt=v;
  currentSpeed=vFilt;

  //Controller
  error=desiredSpeed-currentSpeed;
  errorIntegral= errorIntegral + error*deltaT/1.0e3; 
  pwmValue= Kp*error  + Ki*errorIntegral;   // 0<= pwmValue <=255
  direct=1;

  if (pwmValue <0)
  {
    direct=0;
    pwmValue = abs(pwmValue);
  }

  if (pwmValue > 255) pwmValue=255;
  
  
  Serial.print(int(desiredSpeed));   //plot setpoint (reference) 
  Serial.print(" ");
  Serial.print(int(currentSpeed));   //plot current speed (output)
  Serial.println();

  analogWrite(ENA,pwmValue);
  digitalWrite(IN1,direct);
  digitalWrite(IN2,!direct);
}


float read_speed(void)
{
    //read angular speed of the motor
    //return angular speed in rpm
    currentEncoder = motor.read();
    currentMillis = millis();
    
    deltaT=(currentMillis - previousMillis);
    long deltaEncoder=currentEncoder-previousEncoder;
       
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
