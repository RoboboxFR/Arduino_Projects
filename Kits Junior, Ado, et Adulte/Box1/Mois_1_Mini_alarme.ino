// Défi nition du ‘pin D12’ relié à la LED
int ledPin = 12;

// Défi nition du ‘pin A5’ relié au capteur de mouvement
int inputPin = A5;

// Défi nition du ‘pin D4’ relié au buzzer
int pinSpeaker = 4;

// Déclaration et initialisation de la variable val
int val = 0;

void setup() {
  // Configuration du pin LED en tant que sortie
  pinMode(ledPin, OUTPUT);
  
  // Configuration du pin capteur en tant qu’entrée
  pinMode(inputPin, INPUT);

  // Configuration du pin buzzer en tant que sortie
  pinMode(pinSpeaker, OUTPUT); 
}

void loop(){
  // Y a-t-il du mouvement ?
  val = digitalRead(inputPin);
  if (val == HIGH) {
    // Si oui …
    // On allume la LED
    digitalWrite(ledPin, HIGH);

    // On fait sonner le buzzer
    tone(pinSpeaker,160, 300);

    // On attend 0,15s
    delay(150);

    // On éteint le buzzer
    noTone(pinSpeaker);

    // On éteint la LED
    digitalWrite(ledPin, LOW);

    // On attend 0,15s
    delay(150);
  }
}
