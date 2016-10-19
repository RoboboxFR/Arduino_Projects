//Merci à LouisD pour cette réponse :)

int ledPin = 5; // pin de la led jambe longue = 5 sur carte Arduino UNO 
int inputPin = 2; // pin du capteur de mouvement central orange = 2 sur carte Arduino UNO 
int pinSpeaker = 6; // pin du buzzer jambe longue = 6 sur carte Arduino UNO 
int pirState = LOW; // Etat initial du capteur de mouvement - pas de mouvement
int val = 0; // variable globale initialisée à 0 
int detect = 3; // Nombre de détection d'intrusion avant lampe s'allume
int max_detect =0; // Variable globale initialisée à 0


// Fonction toujours présente sur carte Arduino - indication des paramètres
void setup() { 
pinMode(ledPin, OUTPUT); // info sort de la carte vers la Led
pinMode(inputPin, INPUT); // info parvient du capteur de mouvement vers la carte
pinMode(pinSpeaker, OUTPUT); // info sort de la carte vers le buzzer
Serial.begin(9600);
}


// Fonction indiquant à la carte de jouer un son pendant une certaine durée et à une certaine fréquence
void joueSon (long duree, int frequence) {
duree *= 1000; // Nous multiplions la durée par 1000 pour compter en millisecondes
int period = (1.0 / frequence) * 1000000; // Nous ajustons la fréquence de l’envoi de sons pour correspondre à une fréquence audio
long temps_passe = 0; // Nous initialisons la variable ‘temps passé’ à 0
while (temps_passe < duree) {
digitalWrite(pinSpeaker,HIGH); // mise en route du buzzer
delayMicroseconds(period / 2); // attente de quelques millisecondes
digitalWrite(pinSpeaker, LOW); // arret du buzzer
delayMicroseconds(period /2); // attente de quelques millisecondes
temps_passe += period; // increment de temps passé
}
}

// la led d'allume pendant 1 seconde si mon_max est atteint 
void led_allume (int mon_max) {
max_detect ++; // increment

if (max_detect == mon_max) { 
digitalWrite(ledPin, HIGH); // éteind la LED
delay(500); // attendre 1000 millisecondes
digitalWrite(ledPin, LOW); // éteind la LED
max_detect = 0; // réinitialise variable globale
delay(300);
} 
}


// vérifie si un mouvement est détecté - allume la led et joue son - sinon éteint led et pas de son
void loop() { 
val = digitalRead(inputPin); // variable globale associée à la valeur du capteur mouvement HIGH ou LOW 

if (val == HIGH) { // si un mouvement est détecté
// boucle 3 fois pour faire 3 sons différents
for (int i=0; i < 3; i++){ 
joueSon(600, random(100,10000)); // joue son pendant 0.6 seconde à un nombre de hertz aléatoire 
delay (300);
}
led_allume (detect);
joueSon(0,0); 
}
delay(300); 
}

// pas évident de comprendre les "delays" utiles
// ni la gestion de longueur des son ou de leur multiplication en saccade... 
