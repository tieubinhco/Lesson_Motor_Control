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
int interval=10;  //ms sample Time
int direct=1;
float angularSpeed=0;

float previousSpeed=0;
long deltaT=0;

float vFilt=0;
float vpreFilt=0;

void setup() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
  Serial.begin(9600);
  Serial.println("Reading speed of the motor");
  Serial.println("-----------------------------------------");
}

void loop() {

  
  int pwm=255; //Input
  
  angularSpeed=read_speed(); //Output
  
  direct=1*(pwm>0);
  Serial.print(pwm);
  Serial.print("\t");
  Serial.print(angularSpeed);
  Serial.print("\t");
  Serial.println(millis());
  analogWrite(ENA,abs(pwm));
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
