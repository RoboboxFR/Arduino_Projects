// Merci à Isabelle pour le code !

// Variables Globales
const int ledPin = 5;      // pin sortie Led
const int inputPin = 2;      // pin entree capteur de mouvement
const int pinSpeaker = 6;    // pin sortie buzzer
int pirState = LOW;
int val = 0;
int cpt = 0;



void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  pinMode(inputPin,INPUT);
  pinMode(pinSpeaker,OUTPUT);
  pinMode(13,OUTPUT);  // led de la board Uno
}

void joueSon (long duree, int frequence) {   // on indique la duree en ms
  duree *=1000;
  int period = (1.0 / frequence)* 1000000;
  long temps_passe = 0;

  while (temps_passe < duree) {
    digitalWrite(pinSpeaker,HIGH);
    delayMicroseconds(period/2);
    digitalWrite(pinSpeaker,LOW);
    delayMicroseconds(period/2);
    temps_passe += (period);
  }
}

// partie consacree aux sons
int noire=0;
int blanche=1;
int croche=2;
int ronde=3;

void joueNote(const char* note, int tempo) {
  
  int c=200;  // duree d'une croche
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


void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(inputPin);

  if (val==HIGH) {      // si capteur mouvement recoit un signal alors la LED s'allume et l'alarme sonne
     cpt += 1;
     if (cpt == 1) {             // on allume la LED 13 de la board 1 fois
       digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
       delay(500);               // wait for half a second
       digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
       delay(500);               // wait for half a second 
     }
     else if (cpt == 2) {        // on allume la LED 13 de la board 2 fois
      for (int i=1; i < 3; i++){
        digitalWrite(13, HIGH);  
        delay(500);             
        digitalWrite(13, LOW);  
        delay(500); 
      }
     }
     else if (cpt == 3) {        // on lance Happy Birthday
      digitalWrite(ledPin,HIGH);
      joueHappyBirthday();
      delay(150);
      cpt = 0;
     }
     delay(2000);
  }

  else {                // si capteur mouvement ne recoit pas de signal alors on eteint la LED et on ne joue pas de son
    digitalWrite(ledPin,LOW);
    joueSon(0,0);
    delay(150);
  }
}
