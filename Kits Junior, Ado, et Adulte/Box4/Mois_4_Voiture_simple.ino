int pin1MoteurG = 12; 
int pin2MoteurG = 8; 
int pinPMoteurG = 11;
int pin1MoteurD = 2; 
int pin2MoteurD = 4;
int pinPMoteurD = 5;
int TRIG_PIN = 10;
int ECHO_PIN = 9;
int DIST_MAX = 200;
int i = 90;
int distActuelle = 0;

void setup() {
  // Configuration des sorties commandes moteurs
  pinMode(pin1MoteurG,OUTPUT);
  pinMode(pin2MoteurG,OUTPUT);
  pinMode(pinPMoteurG,OUTPUT);
  pinMode(pin1MoteurD,OUTPUT);
  pinMode(pin2MoteurD,OUTPUT);
  pinMode(pinPMoteurD,OUTPUT);

  // Configuration des pin Capteur US
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  
    distActuelle = lireDistance();
    if (distActuelle > 20){
      avance();
    }
    if (distActuelle < 20){
      recule();
      tourneDroite();
    }
//    delay(300);
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

void recule(){
    dirMoteur(1,0,100); 
    dirMoteur(2,0,100);
    delay(500); 
    dirMoteur(1,-1,100); 
    dirMoteur(2,-1,100);
    delay(500);  
}

void tourneDroite(){
    dirMoteur(1,1,100); 
    dirMoteur(2,-1,50); 
    delay(250); 
}

// Envoi la distance mesurée par le capteur de distance
int lireDistance() {
  long lecture_echo;
  long cm;
  // On active l’emetteur
  digitalWrite(TRIG_PIN, HIGH);
  // Pendant 10 microsecondes
  delayMicroseconds(10);
  // On désactive l’emetteur
  digitalWrite(TRIG_PIN, LOW);
  // On lit la valeur reçue
  lecture_echo = pulseIn(ECHO_PIN, HIGH);
  // Conversion de cette valeur en centimètres
  cm = lecture_echo/58;
  return cm;
}
