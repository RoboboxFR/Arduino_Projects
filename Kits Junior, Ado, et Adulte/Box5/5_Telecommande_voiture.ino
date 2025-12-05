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
int cm;

#include <IRremote.h>

long val;
int IRpin = A5;
int pinLed = 6;

IRrecv irrecv(IRpin);
decode_results results;

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
  
  Serial.begin(9600); // On peut se passer de cette ligne si on n’utilise plus le moniteur série
  irrecv.enableIRIn(); // Start the receiver
  pinMode(pinLed,OUTPUT);
}

void loop() {
  
  if (irrecv.decode(&results)==1) 
    {
      val = results.value;
      Serial.println(val, DEC);
      irrecv.resume();
    }

  if (val == 16718055){ // Code pour touche 2
    avance();
  }
  
  if (lectureDistance() < 20){
      stopRobot();
  }    
  
  if (val == 16730805){ // Code pour touche 8
    recule();
    delay(1000);
    stopRobot();
  }
}

void dirMoteur(int moteur,int sens,int pourcentage){
  int pin1,etat1,pin2,etat2,pinP,puissance;

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
    dirMoteur(1,1,100); 
    dirMoteur(2,1,100); 
}

void recule(){
    dirMoteur(1,-1,100); 
    dirMoteur(2,-1,100);
}

void tourneDroite(){
    dirMoteur(1,1,100); 
    dirMoteur(2,-1,50);
}

void stopRobot(){
    dirMoteur(1,0,0); 
    dirMoteur(2,0,0);
}

int lectureDistance() {
  long lecture_echo;
  long cm;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  lecture_echo = pulseIn(ECHO_PIN, HIGH);
  cm = lecture_echo/58;
  return cm;
}
