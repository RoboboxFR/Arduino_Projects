#include <IRremote.h>

IRsend irsend;

void setup() {
  Serial.begin(9600);
}

void loop() {

int X = analogRead(A3);
int Y = analogRead(A2);

X = map(X , 0 , 1024 , 0 , 10);
Y = map(Y , 0 , 1024 , 0 , 10);

Crypt(X,'x');

Crypt(Y,'y');

}


void Crypt(unsigned int val, char axis){

unsigned int f1;
unsigned int f2;
int a = 0;
unsigned int axisCode[3];

if (axis == 'x'){axisCode[0] = 300; axisCode[1] = 800; axisCode[2] = 300;}; 
if (axis == 'y'){axisCode[0] = 500; axisCode[1] = 300; axisCode[2] = 800;};


if (val < 5){
  f1 = 800;
  f2 = val+4;
  f2 = f2*100;
  };

if (val >= 5){
  f1 = 400;
  f2 = val-1 ;
  f2 = f2*100;
  };

unsigned int envoiSignal[11] = {5000, axisCode[0], axisCode[1],
axisCode[2], f1, f1, f2, f2, 1000,
500,500};

while (a < 10){
 Serial.print(envoiSignal[a]);
 Serial.print(',');
  a++;
}
 Serial.println();

//irsend.sendRaw(powerOn,10,38); // 38kHz
irsend.sendRaw(envoiSignal,11,38); // 38kHz
delay(100);
}
