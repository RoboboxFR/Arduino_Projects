
#include <IRremote.h>

long val;
int IRpin = 11;
int pinLed = 4;

IRrecv irrecv(IRpin);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(pinLed,OUTPUT);
}

void loop() 
{
  if (irrecv.decode(&results)) 
    {
      val = results.value;
      Serial.println(val); // Print the Serial 'results.value'
      irrecv.resume();   // Receive the next value
    };


  if (val == -1386715550){ // replace with value 'val' // remplacer par la valeur 'val'
    digitalWrite(4, HIGH);
    delay(1000);
    digitalWrite(4, LOW);
    val = 0;
  };
  
}
