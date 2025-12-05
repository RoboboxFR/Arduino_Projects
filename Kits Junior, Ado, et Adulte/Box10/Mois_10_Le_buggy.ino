
#include <Voiture_Robobox.h>
#include <Servo.h>
Servo monServo;

Voiture Ma_Voiture(4, 3, 5, 7, 8, 6);

// On défini le pin pour l’émetteur
#define trigger 10

// Puis un pin pour le récepteur
#define echo 9

int distance = 0; // initialise la distance mesurée
int distMin = 50; // définit la distance minimale pour avancer
int ToutDroit = 85;
int AGauche = 55;
int ADroite = 115;
int TempsStop = 50;
int TempsRecule = 1000;
int TempsTourne = 1000;
int choix;
int vitesse = 50;
unsigned long tempo ;


void setup()
{
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  pinMode(echo, INPUT);

  monServo.attach(11);
  
  tempo = millis();
}

void loop() {
  if (millis() > tempo) {
    choix_direction(2);
  }
  Ma_Voiture.avance(vitesse);

  distance = lireDistance();
  if (distance<distMin) {
     // Si obstacle - STOP
    Ma_Voiture.recule(vitesse);
    delay(TempsStop);
    Ma_Voiture.stop();

    // Regarde si obstacle à droite ou à gauche
    choix = random(2); // Choix aléatoire (résultat 0 ou 1)
    choix_direction(choix);

    distance = lireDistance();
    if (distance<distMin) {
      // Si obstacle - on regarde de l'autre côté
      choix_direction(1-choix);

      distance = lireDistance();
      if (distance<distMin) {
        // Si obstacle - on regule
        Ma_Voiture.recule(vitesse);
        delay(TempsRecule);
        // on se remets tout droit
        choix_direction(2);
      }
    }
    Ma_Voiture.avance(vitesse);
    tempo = millis() + TempsTourne;
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

void choix_direction(int dir) {
      switch (dir) {
      case 0: 
        monServo.write(AGauche);
        break;
      case 1:
        monServo.write(ADroite);
        break;
      case 2: 
        monServo.write(ToutDroit);
        break;
    }
    delay(250);
}
