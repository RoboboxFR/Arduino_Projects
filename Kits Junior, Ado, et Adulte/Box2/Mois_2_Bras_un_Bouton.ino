// Import de la bibliothèque Servo.h
#include <Servo.h>
// Création d’une variable de type ‘Servo’, appelée ‘monServo1’
Servo monServo1;
// Création d’une variable de type ‘Servo’, appelée ‘monServo2’
Servo monServo2;
// Création d’une variable de type int qui va stocker le pin sur lequel le bouton est branché
int bouton=2;
// Définition d’une variable pour positionner nos moteurs
int angleMoteur;

void setup()
{
  // Nous informons la carte Arduino sur quel pin est branché chaque moteur (D5)
  monServo1.attach(5);
  // Nous informons la carte Arduino sur quel pin est branché le bouton poussoir (D2)
  pinMode(bouton, INPUT);
}

void loop()
{
  // Si le bouton est appuyé, on lance la boucle
  if (digitalRead(bouton) == HIGH) {
    for(angleMoteur=0;angleMoteur<=90;angleMoteur=angleMoteur+1) {
      monServo1.write(angleMoteur);
      delay(15);
    }
    for(angleMoteur=90;angleMoteur>=0;angleMoteur=angleMoteur-1) {
      monServo1.write(angleMoteur);
      delay(15);
    }
  }
}
