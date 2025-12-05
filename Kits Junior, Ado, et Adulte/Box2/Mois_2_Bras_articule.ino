// Utilisation de la bibliothèque Servo.h
#include <Servo.h>

// Création d’une variable de type 'Servo’, appelée 'monServo1’
Servo monServo1;

// Création d’une variable de type 'Servo’, appelée 'monServo2’
Servo monServo2;

// Définition d’une variable pour positionner nos moteurs
int angleMoteur = 0;

void setup()
{
  monServo1.attach(5);
  monServo2.attach(6);
}

void loop()
{
  for(angleMoteur = 0; angleMoteur <= 190; angleMoteur += 1)
  {
  monServo1.write(angleMoteur);
  monServo2.write(180-angleMoteur);
  delay(10);
  }
  for(angleMoteur = 180; angleMoteur>=0; angleMoteur-=1)
  {
    monServo1.write(angleMoteur);
    monServo2.write(180-angleMoteur);
    delay(10);
 }
}
