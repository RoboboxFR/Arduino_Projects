
#include <Voiture_Robobox.h>
#include <Servo.h>
Servo monServo;
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX

Voiture Ma_Voiture(4, A2, 5, 7, 8, 6);

// On défini le pin pour l’émetteur
#define trigger A0

// Puis un pin pour le récepteur
#define echo A1

int distance = 0; // initialise la distance mesurée
int distMin = 20; // définit la distance minimale pour avancer
int ToutDroit = 85;
int AGauche = 55;
int ADroite = 115;
int TempsStop = 50;
int TempsRecule = 1000;
int TempsTourne = 1000;
int choix;
int vitesse = 50;
unsigned long tempo ;

char c = ' ';
boolean NL = true;
 


void setup()
{
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  pinMode(echo, INPUT);

  monServo.attach(9);
  
  tempo = millis();

  Serial.begin(9600);
      
  // baud rate du HC-0x : 9600 par défaut
  BTSerial.begin(9600);  
  Serial.println("Arduino avec HC-0x");
}

void loop() {

    // Lecture du module BT et affichage des données sur le moniteur série de l'Ordinateur
  if (BTSerial.available())
  {
    c = BTSerial.read();
    Serial.write(c);
    if (c!='B') {
      distance = lireDistance();
      BTSerial.print("Mesure capteur : ");
      BTSerial.println(distance);
      if (distance<distMin) {
        c = 'S';
      }
    }
  
    switch (c) {
      case 'L': 
        monServo.write(AGauche);
        Ma_Voiture.avance(vitesse);
        BTSerial.println("Je vais à Gauche");
        delay(500);
        break;
      case 'R':
        monServo.write(ADroite);
        Ma_Voiture.avance(vitesse);
        BTSerial.println("Je vais à Droite");
        delay(500);
        break;
      case 'F': 
        monServo.write(ToutDroit);
        Ma_Voiture.avance(vitesse);
        BTSerial.println("J'avance");
        delay(500);
        break;
      case 'B': 
        monServo.write(ToutDroit);
        Ma_Voiture.recule(vitesse);
        BTSerial.println("Je recule");
        delay(500);
        break;
      default :
        Ma_Voiture.stop();
        BTSerial.println("STOP");
        delay(500);
    }
//    Ma_Voiture.stop();
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
