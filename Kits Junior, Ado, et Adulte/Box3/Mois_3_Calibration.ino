#include <Servo.h>

Servo servo1, servo2;

void setup()
{
  servo1.attach(5);
  servo2.attach(6);
}

void loop(){
  servo1.write(90);
  servo2.write(90);
}


