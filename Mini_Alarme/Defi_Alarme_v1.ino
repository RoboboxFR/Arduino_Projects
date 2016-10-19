// Merci à Anthony pour le code!


int ledPin=5;  //pin sortie led
int inputPin=2;   //pin entrée capteur
int pinSpeaker=6;   //pin sortie buzzer
int pirState=LOW;
int val=0;



void setup() {
pinMode(ledPin,OUTPUT);  // definit que la sortie de la led
pinMode(inputPin,INPUT);   //definit que le pin du capteur est une entrée
pinMode(pinSpeaker,OUTPUT);   //definit que la pin buzzeer en une sortie
}


void joueSon (long duree,int frequence) { //debut de la fonction
  duree*=1000;
  int period=(1.0/frequence)*1000000;
  long temps_passe=0;

  while (temps_passe<duree){  //debut de la boucle 'while'
    digitalWrite(pinSpeaker,HIGH);
    delayMicroseconds(period/2);
    digitalWrite(pinSpeaker,LOW);
    delayMicroseconds(period/2);
    temps_passe+=(period);
  }
}

void loop() {
  val=digitalRead(inputPin);
  int compteur = 0;
  
  if(val==HIGH){
    digitalWrite(ledPin,HIGH);
     delay(150);
     compteur++;
     }
  if(compteur==3){
    digitalWrite(ledPin,HIGH);
    joueSon(300,150);
    compteur = compteur-3;
    delay(150);
  }
   
 else{
     digitalWrite(ledPin,LOW);
     joueSon(0,0);
     delay(150);
  }
}
