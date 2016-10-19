// Merci à ThierryM pour cette innovation !


#include <Servo.h>

Servo monServo1; //Crée l'objet Servo pour le moteur inférieur
Servo monServo2; //Crée l'objet Servo pour le moteur suppérieur
int posiMoteurD1 = 135; // Positionnement de départ du moteur 1
int posiMoteurA1 = 135; // Positionnement d'arrivée du moteur 1
int posiMoteurD2 = 135; // Positionnement de départ du moteur 2
int posiMoteurA2 = 135; // Positionnement d'arrivée du moteur 2
int NoMoteur = 1; // No du moteur actif

int PinCapteur = 2; //pin d'entrée du capteur de mouvement
int PinBouton1 = 6; //pin d'entrée du bouton 1
int PinBouton2 = 7; //pin d'entrée du bouton 2
int pinSpeaker = 3; //pin de sortie du buzzer

int pirState = LOW; // on initialise le capteur à LOW
int valCapteur = 0;

int valBouton1 = 0;
int valBouton2 = 0;

int i;
int BasculeMoteur = 0; // permet de savoir si on a changé de moteur

void setup() {
pinMode(PinCapteur, INPUT); //définit que c'est une entrée
pinMode(PinBouton1, INPUT); //définit que c'est une entrée
pinMode(PinBouton2, INPUT); //définit que c'est une entrée
pinMode(pinSpeaker, OUTPUT); //définit que c'est une sortie
monServo1.attach(8); // le moteur inférieur est associé à la broche 8
monServo2.attach(9); // le moteur supérieur est associé à la broche 9
monServo1.write(posiMoteurD1); // initialisation de la position du moteur 1
monServo2.write(posiMoteurD2); // initialisation de la position du moteur 1
}

void loop() {
valCapteur = digitalRead(PinCapteur);
valBouton1 = digitalRead(PinBouton1);
valBouton2 = digitalRead(PinBouton2);

// Change de No de moteur à chaque détection de mouvement
if ((valCapteur == HIGH) && (BasculeMoteur == 0)) {
joueSon(150,160);
BasculeMoteur = 1;
if (NoMoteur == 1) {
NoMoteur = 2;
}
else {
NoMoteur = 1; 
}
}


// si le bouton 1 est sollicité, on positionne le moteur de -15 degrés, si c'est le bouton 2, +15 degrés
if (valBouton1 == HIGH) {
BasculeMoteur = 0;
if (NoMoteur == 1) {
posiMoteurA1 = posiMoteurD1 - 15;
}
else {
posiMoteurA2 = posiMoteurD2 - 15; 
}
}
else {
if (valBouton2 == HIGH) {
BasculeMoteur = 0;
if (NoMoteur == 1) {
posiMoteurA1 = posiMoteurD1 + 15;
}
else {
posiMoteurA2 = posiMoteurD2 + 15; 
}
}
else {
delay(1000); 
}
}

if (posiMoteurD1 < posiMoteurA1) {
for(i=posiMoteurD1; i <= posiMoteurA1; i+=1) // boucle croissante de posiMoteurD1 à posiMoteurA1
{
monServo1.write(i);
delay(15);
}
posiMoteurD1 = posiMoteurA1;
}
if (posiMoteurD1 > posiMoteurA1) {
for(i=posiMoteurD1; i >= posiMoteurA1; i-=1) // boucle décroissante de posiMoteurD1 à posiMoteurA1
{
monServo1.write(i);
delay(15);
}
posiMoteurD1 = posiMoteurA1;
}

if (posiMoteurD2 < posiMoteurA2) {
for(i=posiMoteurD2; i <= posiMoteurA2; i+=1) // boucle croissante de posiMoteurD2 à posiMoteurA2
{
monServo2.write(i);
delay(15);
}
posiMoteurD2 = posiMoteurA2;
}
if (posiMoteurD2 > posiMoteurA2) {
for(i=posiMoteurD2; i >= posiMoteurA2; i-=1) // boucle décroissante de posiMoteurD2 à posiMoteurA2
{
monServo2.write(i);
delay(15);
}
posiMoteurD2 = posiMoteurA2;
}

}

// Fonction pour jouer un son avec comme paramètres : la durée et la fréquence
void joueSon (long duree, int frequence) {
duree *=1000;
int period = (1.0 / frequence)* 1000000;
long temps_passe = 0;

while (temps_passe < duree) {
digitalWrite(pinSpeaker, HIGH);
delayMicroseconds(period/2);
digitalWrite(pinSpeaker, LOW);
delayMicroseconds(period/2);
temps_passe += (period);
}
}
