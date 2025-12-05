#include <Voiture_Robobox.h>
#include <Servo.h>
#include "SD.h"
#include "SPI.h"

#define SD_ChipSelectPin 10
#define trigger A0
#define echo A1

Servo monServo;
Voiture Ma_Voiture(4, 2, 5, 7, 8, 6);

String Fichier_P = "parcours.txt";
String Fichier_D = "donnees.csv";
File monFichier_P;
File monFichier_D;

int distance = 0;
int distMin = 50;
int ToutDroit = 85;
int AGauche = 40;
int ADroite = 130;
int TempsStop = 500;
int TempsRecule = 500; 
int TempsAvance = 500;
int TempsTourne = 800; //Temps à régler de manière à ce que le robot réalise 1/4 de tour
int vitesse = 100; // Adapter la vitesse en fonction des besoins (min = 0, max = 100)
boolean detection = true;
boolean boucle = false;
int pos = 0;

void setup()
{
  Serial.begin(9600);
  Serial.print("Initialisation carte SD...");
  
  /* Initialisation du port SPI */
  pinMode(10, OUTPUT);
  
  if(!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("Echec Carte SD");
    return;
  }

  monServo.attach(3);

  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW);
  pinMode(echo, INPUT);
}

void loop() {
  monFichier_P = SD.open(Fichier_P);
  if (monFichier_P) {
    Serial.print(Fichier_P);
    Serial.println(" : ");
    
    monFichier_P.seek(pos);
    // Lecture du fichier jusqu'à la fin
    while (monFichier_P.available()>0) {
      Deplacement(monFichier_P.read());
      monFichier_D = SD.open(Fichier_D, FILE_WRITE);
      if (monFichier_D) {
        Serial.print("Ecriture...");
        monFichier_D.print(millis());
        monFichier_D.print(";");
        monFichier_D.println(lireDistance());
        monFichier_D.close();
        Serial.println("fait.");
      } else {
        Serial.print("erreur d'ouverture de ");
        Serial.println(Fichier_D);
      }
    }
    // fermeture du fichier :
    monFichier_P.close();
  } else {
    // en cas de problème, écriture d'une erreur
    Serial.print("erreur d'ouverture de ");
    Serial.println(Fichier_P);
  }


  while(!boucle){}
  //arrêt du programme si pas de Z
}


int lireDistance(){
  long lecture_echo;
  long cm;
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  lecture_echo = pulseIn(echo, HIGH);
  cm = lecture_echo /58;
  return cm;
}

void Deplacement(char choix){
  if (choix=='/') {detection = false;}
  if (choix=='Z') {boucle = true;}
  if (choix=='A') {detection = true;}
  if (detection & (choix!='B')) {
    distance = lireDistance();
    if (distance<distMin) {choix = 'S';}
  }
  switch (choix) {
    case 'L': 
      monServo.write(AGauche);
      Ma_Voiture.avance(vitesse);
      Serial.println(" Gauche ");
      delay(TempsTourne);
      break;
    case 'R':
      monServo.write(ADroite);
      Ma_Voiture.avance(vitesse);
      Serial.println(" Droite ");
      delay(TempsTourne);
      break;
    case 'F': 
      monServo.write(ToutDroit);
      Ma_Voiture.avance(vitesse);
      Serial.println(" Avance ");
      delay(TempsAvance);
      break;
    case 'B': 
      monServo.write(ToutDroit);
      Ma_Voiture.recule(vitesse);
      Serial.println(" Recule ");
      delay(TempsRecule);
      break;
    case 'G': 
      monServo.write(AGauche);
      Ma_Voiture.recule(vitesse);
      Serial.println(" Gauche ");
      delay(TempsTourne);
      break;
    case 'D':
      monServo.write(ADroite);
      Ma_Voiture.recule(vitesse);
      Serial.println(" Droite ");
      delay(TempsTourne);
      break;
    default :
      Ma_Voiture.stop();
      Serial.println(" Stop ");
      delay(TempsStop);
  }
}
