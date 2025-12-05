// Merci à Yohan pour la création de ce code simplifié !

// initiaisation des différentes pattes de l'arduino

int ledPin = 5;       // la patte 5 de l'arduino s'appelle désormais ledPin               
int inputPin = 2;     // la patte 2 de l'arduino s'appelle désormais inputPin              
int pinSpeaker = 6;   // la patte 6 de l'arduino s'appelle désormais pinSpeaker                 
int val = 0;          // "val" est une variable       

            
void setup() // cette partie du code n'est lue qu'une fois
{
  // déclaration des pattes en entrées ou en sorties
  pinMode(ledPin, OUTPUT);     
  pinMode(inputPin, INPUT);    
  pinMode(pinSpeaker, OUTPUT);
}


void loop() // boucle principale,cette partie du code est lue en boucle
  {
  val = digitalRead(inputPin); // la valeur qui est en entrée est stocké dans la variable "val"
                                // val peut prendre deux valeurs HIGH ou LOW

  
  if (val == HIGH) // cas 1 : val = HIGH, quelqu'un est passé devant le capteur
    {
    digitalWrite(ledPin, HIGH);  // allume la del
    tone(pinSpeaker, 160, 300); // envoi un signal sur le speaker fréquence = 160 hz, durée 300ms 
    delay(150);                 // attendre 150ms
    } 
  
  else          // cas 2 : val = LOW, personne n'est passé devant le capteur
  {
      digitalWrite(ledPin, LOW); // eteind la del
      delay(300);                // attendre 300ms
  }
}
