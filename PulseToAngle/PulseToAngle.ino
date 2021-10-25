#include <Encoder.h>

#define ENA 5
#define IN1 7
#define IN2 8

Encoder motor(2, 3);
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(9600);
  Serial.println("Read pulses of the Encoder and convert to degree");
}

long previousPos=-999;

float convert_to_degree(long currentPulse)
{
  float revolution = float(float(currentPulse)/float(194));
  float degree= revolution * 360;
  return degree;
}

void loop() {
  long newPos=0;
  newPos = motor.read();
  if (newPos!=previousPos) {
    Serial.print("Encoder pulses = ");
    Serial.print(newPos);
    Serial.print("\t");
    Serial.print("Degree = ");
    Serial.print(int(convert_to_degree(newPos)));
    Serial.println();
    previousPos = newPos;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset value and set current position to 0 degree");
    motor.write(0);
  }
}
