#include <IRremote.h>

long val;
int IRpin = A5;
int pinLed = 6;

IRrecv irrecv(IRpin);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Démarrer la réception
  pinMode(pinLed,OUTPUT);
}

void loop() 
{
  if (irrecv.decode(&results)==1) 
    {
      val = results.value;
      Serial.println(val,DEC); // Emet vers la liaison série 'results.value'
      irrecv.resume();     // Attente de la prochaine valeur
    };


  if (val == 16738455){ // Code pour touche 0
    digitalWrite(pinLed, HIGH);
    delay(1000);
    digitalWrite(pinLed, LOW);
    val = 0;
  };
}
