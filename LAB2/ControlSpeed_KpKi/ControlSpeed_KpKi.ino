#include <Encoder.h>
#include <math.h>
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
long deltaT=0;

float currentSpeed=0;
float previousSpeed=0;

float desiredSpeed=500;
float error=0;
int pwmValue=100; //0 - 255 dec 0x00 - 0xFF hex
int direct=1;  //1 clockwise  //0 counter-clockwise
float Kp=0.202;  //controlsignal = Kp*error
float Ki=0.9;
float Kd=0.1;  
float errorIntegral=0;
float errorPrevious=0;
float errorDerivative=0;

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(RR,INPUT);
  Serial.begin(9600);
}

float v=0;
float v_1=0;
float v_2=0;
float v_3=0;
float v_4=0;

float vpreFilt=0;
float vFilt=0;


void loop() {
//  desiredSpeed=500*(sin(0.7*currentMillis/1e3)>0)+200;
//desiredSpeed=4*((28*(int(currentMillis/1e3)%10)+2)*(currentMillis/1e3<15)-(28*(int(currentMillis/1e3)%10)+2)*(currentMillis/1e3>=15));
  desiredSpeed=500; //RPM

  //Moving average Filter
  v_4=v_3;
  v_3=v_2;
  v_2=v_1;
  v_1=v;
  v=read_speed();
  vFilt=(v+v_1+v_2+v_3+v_4)/5;




  currentSpeed=vFilt;

  //Calculate error
  error= desiredSpeed-currentSpeed;
  
  // Integrate the error
  errorIntegral=errorIntegral+ error*deltaT/1.0e3;

  // Take derivate of the error
  errorDerivative=(error-errorPrevious)/(deltaT/1.0e3);

  errorPrevious=error;
  
  
  //Controller 
  pwmValue=Kp*error + Ki*errorIntegral + Kd*errorDerivative;
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
  Serial.print(currentSpeed);
//  Serial.print("\tDesired speed=\t");
  Serial.print(" ");
  Serial.print(desiredSpeed);
    Serial.print(" ");
  Serial.println(pwmValue);
}

float read_speed(void)
{
    //read angular speed of the motor
    //return angular speed in rpm
    currentEncoder = motor.read();
    currentMillis = millis();
    deltaT=(currentMillis - previousMillis);
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
