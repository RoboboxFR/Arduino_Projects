//Variable pour les Moteurs
int pin1MoteurG = 12; 
int pin2MoteurG = 8; 
int pinPMoteurG = 11;
int pin1MoteurD = 2; 
int pin2MoteurD = 4;
int pinPMoteurD = 5;
int moteur[2] = {0,0};
int VITESSE_SUIVI_GAUCHE = 50;
int VITESSE_SUIVI_DROITE = 50;

// Variables pour Suivi de Ligne
int pinLineD = A0;
int pinLineC = A1;
int pinLineG = A2;

// Variable pour le Bouton
int pinBouton = 3;

void setup() {
  pinMode(pin1MoteurG,OUTPUT);
  pinMode(pin2MoteurG,OUTPUT);
  pinMode(pinPMoteurG,OUTPUT);
  pinMode(pin1MoteurD,OUTPUT);
  pinMode(pin2MoteurD,OUTPUT);
  pinMode(pinPMoteurD,OUTPUT);

  pinMode(pinLineD,INPUT);
  pinMode(pinLineC,INPUT);
  pinMode(pinLineG,INPUT);
  pinMode(pinBouton,INPUT);

// Attendre jusqu’à ce que le bouton
// soit appuyé.
  while(!(digitalRead(pinBouton))) {}

  delay(1000);
}

void loop() {
   suivre_ligne();
   avance(moteur[0],moteur[1]);
}

void suivre_ligne(){
 boolean lineG = digitalRead(pinLineG);
 boolean lineC = digitalRead(pinLineC);
 boolean lineD = digitalRead(pinLineD);
 // Seul le capteur central voit la ligne
 if (!lineG && lineC && !lineD) {
  // Avancer tout droit
  moteur[0]=VITESSE_SUIVI_GAUCHE;
  moteur[1]=VITESSE_SUIVI_DROITE;
 }
 // Le capteur droit voit la ligne
 if (!lineG && lineC && lineD) {
  // Tourner à droite lentement
  moteur[0]=VITESSE_SUIVI_GAUCHE;
  moteur[1]=0;
 }
 // Le capteur gauche voit la ligne
 if (lineG && lineC && !lineD) {
  // Tourner à gauche lentement
  moteur[0]=0; 
  moteur[1]=VITESSE_SUIVI_DROITE; 
 }
 // Seul le capteur droit voit la ligne
 if (!lineG && !lineC && lineD) {
  // Tourner à droite rapidement
  moteur[0]=VITESSE_SUIVI_GAUCHE;
  moteur[1]=-VITESSE_SUIVI_DROITE;
 }
 // Seul le capteur gauche voit la ligne
 if (lineG && !lineC && !lineD) {
  // Tourner à gauche rapidement
  moteur[0]=-VITESSE_SUIVI_GAUCHE;
  moteur[1]=VITESSE_SUIVI_DROITE;
 }
}

void avance(int motG, int motD ){
    dirMoteur(1,1,motG); 
    dirMoteur(2,1,motD);
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

    if (((sens==1) && (pourcentage>0)) || ((sens==-1) && (pourcentage<0))){
    etat1=1;
    etat2=0;
  }
  else if (((sens==-1) && (pourcentage>0)) || ((sens==1) && (pourcentage<0))){
    etat1=0;
    etat2=1;
  }
  else {
    etat1=0;
    etat2=0;
  }
  puissance=map(abs(pourcentage),0,100,0,255);
  digitalWrite(pin1,etat1);
  digitalWrite(pin2,etat2);
  analogWrite(pinP,puissance);
}
