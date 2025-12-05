// Merci à AnthonyC pour cette réponse !
int ledPin=5; //pin sortie led
int inputPin=2; //pin entrée capteur
int pinSpeaker=6; //pin sortie buzzer
int pirState=LOW;
int val=0;
int compteur=0;



void setup() {
pinMode(ledPin,OUTPUT); // definit que la sortie de la led
pinMode(inputPin,INPUT); //definit que le pin du capteur est une entrée
pinMode(pinSpeaker,OUTPUT); //definit que la pin buzzeer en une sortie

}
void joueSon (long duree,int frequence) { //debut de la fonction
duree*=1000;
int period=(1.0/frequence)*1000000;
long temps_passe=0;

while (temps_passe digitalWrite(pinSpeaker,HIGH);
delayMicroseconds(period/2);
digitalWrite(pinSpeaker,LOW);
delayMicroseconds(period/2);
temps_passe+=(period);
}
}


void loop() {
val=digitalRead(inputPin);



if (val==HIGH){
digitalWrite(ledPin,HIGH);
delay(2812); //2812 est la valeur qu'il faut au capteur pour passer de la valeur HIGH au LOW potentiometre P1 au minimum 
compteur++;
}

if(compteur==3){
digitalWrite(ledPin,HIGH);
joueSon(1500,300);
delay(2812);
compteur=0;
}




else {
joueSon(0,0);
digitalWrite(ledPin,LOW);
delay(150);
}
}
