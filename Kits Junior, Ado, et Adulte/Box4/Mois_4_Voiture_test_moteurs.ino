int pin1MoteurG = 12; 
int pin2MoteurG = 8; 
int pinPMoteurG = 11;
int pin1MoteurD = 2; 
int pin2MoteurD = 4;
int pinPMoteurD = 5;

void setup() {
  // Configuration des sorties commandes moteurs
  pinMode(pin1MoteurG,OUTPUT);
  pinMode(pin2MoteurG,OUTPUT);
  pinMode(pinPMoteurG,OUTPUT);
  pinMode(pin1MoteurD,OUTPUT);
  pinMode(pin2MoteurD,OUTPUT);
  pinMode(pinPMoteurD,OUTPUT);
}

void loop() {
  avance();
}


void dirMoteur(int moteur,int sens,int pourcentage){
  int pin1,etat1,pin2,etat2,pinP,puissance; //variable de la fonction

  if (moteur==1){
    pin1=pin1MoteurG;
    pin2=pin2MoteurG;
    pinP=pinPMoteurG;
  }
  else {
    pin1=pin1MoteurD;
    pin2=pin2MoteurD;
    pinP=pinPMoteurD;
  }
  if (sens==1){
    etat1=1;
    etat2=0;
  }
  else if (sens==-1){
    etat1=0;
    etat2=1;
  }
  else {
    etat1=0;
    etat2=0;
  }
  puissance=map(pourcentage,0,100,0,255);
  digitalWrite(pin1,etat1);
  digitalWrite(pin2,etat2);
  analogWrite(pinP,puissance);
}

void avance(){
    dirMoteur(1,1,100); 
    dirMoteur(2,1,100); 
}
