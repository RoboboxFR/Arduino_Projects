int ledPin=5;     // définition du PIN de sortie de la led
int inputPin=2;   // définition du PIN d'entrée du capteur de mouvement
int pinSpeaker=6; // définition du PIN de sortie du buzzer
int pirState=LOW;
int val=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);     // le pin de la led est une sortie
  pinMode(inputPin,INPUT);    // le pin du capteur de mouvement est une entrée
  pinMode(pinSpeaker,OUTPUT); // le pin du buzzer est une sortie
}

// fonction pour produire un son avec le buzzer
void joueSon(long duree, int frequence) {
  duree *= 1000;
  int period = (1.0/frequence)*1000000;
  long temps_passe=0;

  while (temps_passe < duree) {
    digitalWrite(pinSpeaker,HIGH);
    delayMicroseconds(period/2);
    digitalWrite(pinSpeaker,LOW);
    delayMicroseconds(period/2);
    temps_passe+=period;
  }
}

int noire=0;
int blanche=1;
int croche=2;
int ronde=3;

void joueNote(const char* note, int tempo) {
  
  //int c=375;
  int c=200;
  int temps=300;
  if (tempo==noire) {temps=2*c; }
  else if (tempo==blanche) {temps=4*c; }
  else if (tempo==croche) {temps=c; }
  else if (tempo==ronde) {temps=8*c; }

  int inter=100;
  if (note == "Do") { joueSon(temps, 523); delay(inter);}
  else if (note == "Re") { joueSon(temps, 587); delay(inter);}
  else if (note == "Mi") { joueSon(temps, 659); delay(inter);}
  else if (note == "Fa") { joueSon(temps, 698.5); delay(inter);}
  else if (note == "Sol") { joueSon(temps, 784); delay(inter);}
  else if (note == "La") { joueSon(temps, 880); delay(inter);}
  else if (note == "Si") { joueSon(temps, 988); delay(inter);}
  else if (note == "Sib") { joueSon(temps, 932); delay(inter);}
}

void joueHappyBirthday() {
  joueNote("Do",croche);
  joueNote("Do",croche);
  joueNote("Re",noire);
  joueNote("Do",noire);
  joueNote("Fa",noire);
  joueNote("Mi",blanche);
  joueNote("Do",croche);
  joueNote("Do",croche);
  joueNote("Re",noire);
  joueNote("Do",noire);
  joueNote("Sol",noire);
  joueNote("Fa",ronde);
}

int compteur=0;
void loop() {
  // put your main code here, to run repeatedly:
  val=digitalRead(inputPin);
  if (val==HIGH) { // si le capteur recoit une valeur positive, l'alarme attend
    compteur=compteur+1;
    if (compteur<3) {
      delay(1000);
    }
    else {
     digitalWrite(ledPin,HIGH);
     joueHappyBirthday();
     delay(150);
     compteur=0;
    }
  }
  else {
    digitalWrite(ledPin,LOW); // si le capteur ne recoit pas de signal, rien ne se passe
    joueSon(0,0);
    delay(300);
  }
}
