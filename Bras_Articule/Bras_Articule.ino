

#include <Servo.h> 
 
Servo monServo1;       // Créé un objet 'Servo' et l'appelle 'monServo1'
Servo monServo2;       // Créé un objet 'Servo' et l'appelle 'monServo2'
int posiMoteur = 0;    // Défini une variable pour positionner nos moteurs

void setup() 
{ 
  monServo1.attach(2);  // Relie le servo monServo1 au pin 2
  monServo2.attach(4);
} 
void loop() 
{ 
  for(posiMoteur = 0; posiMoteur <= 90; posiMoteur += 1) // Va faire 90 boucles en 
  {     // incrémentant posiMoteur
    monServo1.write(posiMoteur);              
    monServo2.write(posiMoteur);			// demande au moteur d’aller dans la 
    delay(15); 		// position définie par posiMoteur
} 
  for(posiMoteur = 90; posiMoteur>=0; posiMoteur-=1)  //répète l’opération précédente
{  // en sens inverse
    monServo1.write(posiMoteur);  
    monServo2.write(posiMoteur);
    delay(15);                       // Attends 15 millisecondes pour donner le temps au moteur de 
  } 			                        // changer de position
} 
