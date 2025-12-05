// Voici le code du Robot Chien
// N'hésitez pas à le copier-coller

#include <NewPing.h> // ajoute la bibliothèque du capteur ultrason
#include <Servo.h> // ajoute la bibliothèque servo-moteurs

Servo servoAvant,servoArriere; // créé deux objets servos
NewPing sonar(2, 4, 200); // créé un objet sonar

char avant[] = {60,100,100,100,100,60,60,60}; // créé un array ‘avant[]’
int distance = 0; // initialise la distance mesurée
int distMin = 20; // définit la distance minimale pour avancer

void setup()
{
  servoAvant.attach(6); // lie un moteur au pin 6
  servoArriere.attach(8); // lie un moteur au pin 8
  Serial.begin(9600);
  
}


void loop()
{
  distance = 0;

  while(distance == 0){
      distance = quelleDistance();
      Serial.print(distance);
  }

if(distance > distMin){  //Tant que la distance mesurée est inférieure à 20cm nous avançons
    
    avance();
  
  }
} 


void avance()
{
  for(int n=0;n<4;n++)
  {
  servoAvant.write(avant[2*n]);          // envoie au moteur une valeur pair de la liste avant[]
  servoArriere.write(avant[(2*n)+1]); // envoie au moteur une valeur impair de la liste
  delay(350);
  }
}

int quelleDistance()
{ 
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS/US_ROUNDTRIP_CM;

  return cm;
}
