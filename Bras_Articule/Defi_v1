// Merci à AnthonyC pour ce code :)

int BP1=6; //bouton poussoir 1
int BP2=7; //bouton poussoir 2
int bras=0;
int avbras=0;


#include<Servo.h>
Servo monservo1;
Servo monservo2;
int posiMoteur = 0;





void setup() {
monservo1.attach(2);// definit les servo et leur sortie
monservo2.attach(4);
pinMode (BP1,INPUT);//definit les bouton comme des sorties.
pinMode (BP2,INPUT);

}

void loop() {
bras=digitalRead(BP1);
avbras=digitalRead(BP2);

if(bras==HIGH)
{ posiMoteur+1;
monservo1.write(posiMoteur);
monservo2.write(posiMoteur);
delay(150);
}

if(avbras==HIGH)
{ posiMoteur-1;
monservo1.write(posiMoteur);
monservo2.write(posiMoteur);
delay(150);
}
}
