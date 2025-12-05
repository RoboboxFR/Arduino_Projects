#include <IRremote.h>
#include <Voiture_Robobox.h>

Voiture Ma_Voiture(8, 9, 10, 3, 4, 5);

int Coordinate[2];

IRrecv irrecv(A3);
decode_results results;

void setup()
{
Serial.begin(9600);
// Démarrage de la réception IR
irrecv.enableIRIn();
}

void loop() {
if (irrecv.decode(&results)) {
analyze(&results);
// Réception des données suivantes
irrecv.resume();
}
}

void analyze(decode_results *results)
{
int recieved[11];
int count = results->rawlen;

for (int i = 0; i < count; i++) {
recieved[i] = results->rawbuf[i] * USECPERTICK;}

if (abs(recieved[1] - 5000) < 200 && abs(recieved[9] - 1000) < 100 && abs(recieved[10] - 500) < 100)
{
char Axis = checkAxis(recieved);
int Position = checkValue(recieved);
if (Axis == 'X') {
Coordinate[0] = Position;
}
if (Axis == 'Y') {
Coordinate[1] = Position;
}

Serial.print('[');
Serial.print(Coordinate[0]);
Serial.print('-');
Serial.print(Coordinate[1]);
Serial.println(']');

Ma_Voiture.bouge(Coordinate[0] , Coordinate[1]);

}
}

char checkAxis(int *recieved)
{
int a = recieved[2];
int b = recieved[3];
int c = recieved[4];

int sumDiff = abs(a - 300) + abs(b - 800) + abs(c - 300);

if (sumDiff < 500) {
return 'X';
}
else {
return 'Y';
};
}

int checkValue(int *recieved)
{
int a = recieved[5];
int b = recieved[6];
int c = recieved[7];
int d = recieved[8];

if ( ((a + b) / 2) > 700) {
return ((c + d) / 2) / 100 - 4 ;
}

if ( ((a + b) / 2) < 600) {
return (((c + d) / 2) / 100) + 1;
}
}
