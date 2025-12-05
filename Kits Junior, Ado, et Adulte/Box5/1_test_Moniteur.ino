#include <IRremote.h>
long val;
int IRpin = A5;
int pinLed = 6;
IRrecv irrecv(IRpin);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Démarrer la réception
  pinMode(pinLed, OUTPUT);
}

void loop() {
  // Décodage de la touche appuyée
  if (irrecv.decode(&results) == 1)
  {
    val = results.value;
    Serial.println(val, DEC);
    // Emet par la liaison série ‘results.value’
    // le DEC force l’affi chage de la valeur en décimal
    irrecv.resume();
    // Redémarre la réception du signal
  }
  // Vous taperez ici le code de l’étape 7
}
