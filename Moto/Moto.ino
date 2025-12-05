#include <IRremote.h>
#include <Servo.h> 

int moteur1 = 10;
int vitMoteur =0;
int IRpin = 5;
long val;
int servoAngle;
IRrecv irrecv(IRpin);
decode_results results;
Servo servo1;

void setup() {
  pinMode(moteur1,OUTPUT);
  irrecv.enableIRIn(); 
  servo1.attach(3);  }

void loop() {
  if (irrecv.decode(&results)) 
    {
      val = results.value;
      action(val);
      irrecv.resume();
    };  }


void action(long token){   
  if(token == 16601263){ tourneDroite();} // changer ce numéro par le vote
  else if(token == 16584943){ tourneGauche();} // changer ce numéro par le vote
  else if(token == 16621663){ accelere();  } // changer ce numéro par le vote
  else if(token == 16617583){ arret(); } } // changer ce numéro par le vote

void tourneDroite(){
  servoAngle = min(180,servoAngle +15);
  servo1.write(servoAngle);  }

void tourneGauche(){
  servoAngle = max(0,servoAngle -15);
  servo1.write(servoAngle);   }

void accelere(){
  analogWrite(moteur1,1);   }

void arret(){
  analogWrite(moteur1,0);   }

