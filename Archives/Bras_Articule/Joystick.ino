#include <Servo.h>

// constantes (ports analogiques)
const int VRx = 0;
const int VRy = 1;
const int SW  = 2;

// Variables de lecture
int calX, calY, calSW, rawX, rawY,angleX, angleY, posMoteur = 0;
Servo serv1,
      serv2;

void setup() {
  // Calibration de la valeur (0, 0) du joystick
  calX = analogRead(VRx);
  calY = analogRead(VRy);
  calSW = analogRead(SW);
  
  // Branchements des servos sur pin de sortie
  serv1.attach(2); // servo 1 sur pin 2
  serv2.attach(4); // servo 2 sur pin 4
}

void loop() {
  // Mesure des valeurs en X et Y
  rawX = analogRead(VRx)- calX;
  rawY = analogRead(VRy)- calY;

  // Activation des bras articulés, axe X pour serv1, axe Y pour serv2
  
  // convertir analog en degrés pour moteur
  angleX = map(rawX, -506, 510, 0, 100);
  angleY = map(rawY, -506, 510, 0, 150);
  
  // appliquer angle pour mouvement
  serv1.write(angleX);
  serv2.write(angleY);

  delay(100);
}
