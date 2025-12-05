int pin1MoteurG = 12; 
int pin2MoteurG = 8; 
int pinPMoteurG = 11;
int pin1MoteurD = 2; 
int pin2MoteurD = 4;
int pinPMoteurD = 5;
int pinAna_a = A0;
int pinAna_b = A1;
int pinAna_c = A2;

int a,b,c,x,y;
float angle;

void setup() {
  // Configuration des pins moteurs
  pinMode(pin1MoteurG,OUTPUT);
  pinMode(pin2MoteurG,OUTPUT);
  pinMode(pinPMoteurG,OUTPUT);
  pinMode(pin1MoteurD,OUTPUT);
  pinMode(pin2MoteurD,OUTPUT);
  pinMode(pinPMoteurD,OUTPUT);
  // Configuration des pins analogiques
  pinMode(pinAna_a,INPUT);
  pinMode(pinAna_b,INPUT);
  pinMode(pinAna_c,INPUT);
}

void loop() {
  a = analogRead(pinAna_a);
  b = analogRead(pinAna_b);
  c = analogRead(pinAna_c);
  
  y = a + cos(-2*PI/3)*b + cos(2*PI/3)*c;
  x = 0 + sin(-2*PI/3)*b + sin(2*PI/3)*c;
  angle = atan2(x,y)* (180 / PI);

  if (angle>10) {
    tourneDroite();
  }
  else if (angle<-10) {
    tourneGauche();
  }
  else {
    avance();
  }
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
  analogWrite(pinP,puissance);
  digitalWrite(pin1,etat1);
  digitalWrite(pin2,etat2);
}

void avance(){
    dirMoteur(1,1,50); 
    dirMoteur(2,1,50); 
}

void tourneDroite(){
    dirMoteur(1,1,50);
    dirMoteur(2,-1,50);
}

void tourneGauche(){
    dirMoteur(1,-1,50); 
    dirMoteur(2,1,50);
}
