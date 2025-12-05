#include <Servo.h>
Servo monServo;

void setup() {
  monServo.attach(11);
  monServo.write(85);
}

void loop() {

}
