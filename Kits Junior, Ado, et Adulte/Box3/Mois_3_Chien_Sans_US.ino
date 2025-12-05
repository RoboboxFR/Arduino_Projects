// Ajoute la bibliothèque servo-moteurs
#include <Servo.h> 

// Création de deux objets servos
Servo servoAvant, servoArriere;

// On défini le pin pour l’émetteur
#define trigger 2

// Puis un pin pour le récepteur
#define echo 4

// Création du tableau d’angles
char avant[] = {60,120,120,120,120,60,60,60};
// initialise la distance mesurée
int distance = 0;
// définit la distance minimale pour avancer
int distMin = 20;

void setup(){
  // lie un moteur au pin D5
  servoAvant.attach(5);
  // lie un moteur au pin D6
  servoArriere.attach(6);
  // le pin émetteur comme est une sortie
  pinMode(trigger, OUTPUT);
  // on empêche l’émission d’un signal
  digitalWrite(trigger, LOW);
  // le pin récepteur est une entrée
  pinMode(echo, INPUT);
}

void loop(){
//  distance = lireDistance();
//  if(distance > distMin){
    avance();
//  }
  
}

void avance(){
  for(int n=0;n<4;n++){
    servoAvant.write(avant[2*n]);
    servoArriere.write(avant[(2*n)+1]);
    delay(350);
  }
}

int lireDistance(){
  long lecture_echo;
  long cm;
  // On active l’emetteur
  digitalWrite(trigger, HIGH);
  // Pendant 10 microsecondes
  delayMicroseconds(10);
  // On éteint l’emetteur
  digitalWrite(trigger, LOW);
  // On lit la valeur reçue
  lecture_echo = pulseIn(echo, HIGH);
  // Conversion de cette valeur en centimètres
  cm = lecture_echo /58;
  return cm;
}
