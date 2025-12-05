#include <Servo.h>

// CrÃ©ation dâ€™une variable de type 'Servoâ€™, appelÃ©e 'monServo1â€™
Servo monServo1;

// CrÃ©ation dâ€™une variable de type 'Servoâ€™, appelÃ©e 'monServo2â€™
Servo monServo2;

// DÃ©finition d'une variable pour positionner nos moteurs 
int angleMoteur;




void setup() 
{
  // Nous informons au programme qu'un servo est branchÃ© sur le pin D5 et un autre sur le pin D6
  monServo1.attach(5);
  monServo2.attach(6);
}

void loop() 
{
 
 // A chaque passage, on ajoute 1 Ã  angleMoteur jusqu'a ce que la variable atteigne 90 
  for(angleMoteur=0;angleMoteur<=90;angleMoteur=angleMoteur+1)
  {
  // On affecte la valeur d'angleMoteur Ã  monServo1
   monServo1.write(angleMoteur);

  // On affecte la valeur 180-angleMoteur Ã  monServo2
    monServo2.write(180-angleMoteur);

  // On attend 15 ms
     delay(15);
  }

  // A chaque passage, on retranche 1 Ã  angleMoteur jusqu'Ã  ce que la variable atteigne 0
   for(angleMoteur=90;angleMoteur>0;angleMoteur=angleMoteur-1)
   {
    monServo1.write(angleMoteur);
    monServo2.write(180-angleMoteur);
    delay(15);
  }
 }
