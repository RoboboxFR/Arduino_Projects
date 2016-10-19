// Created by EricN

int ledPin = 5;
int inputPin = 2;
int pinSpeaker = 6;
int pirState = LOW;
int val = 0;
int length = 13; // the number of notes
char notes[] = "cesagecAFFFG "; // a space represents a rest
int beats[] = { 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 1, 2, 5 };
int tempo = 100;


void setup() {
// put your setup code here, to run once:
pinMode(ledPin, OUTPUT);
pinMode(inputPin, INPUT);
pinMode(pinSpeaker, OUTPUT);
}

void playTone(int tone, int duration) {
for (long i = 0; i < duration * 1000L; i += tone * 2) {
digitalWrite(pinSpeaker, HIGH);
delayMicroseconds(tone);
digitalWrite(pinSpeaker, LOW);
delayMicroseconds(tone);
}
}

void playNote(char note, int duration) {
char names[] = { 'F', 'G', 'A', 'c', 'd', 'e', 'f', 's', 'g', 'a', 'b', 'C' };
int tones[] = { 2703, 2551, 2273, 1915, 1700, 1519, 1432, 1351, 1275, 1136, 1014, 956 };

// play the tone corresponding to the note name
for (int i = 0; i < 12; i++) {
if (names[i] == note) {
playTone(tones[i], duration);
}
}
}

void joueSon(long duree, int frequence){
duree *=1000;
int period = (1.0 / frequence) * 1000000;
long temps_passe = 0;
while (temps_passe < duree){
digitalWrite(pinSpeaker, HIGH);
delayMicroseconds(period/ 2);
digitalWrite(pinSpeaker, LOW);
delayMicroseconds(period / 2);
temps_passe += (period); 
}
}
void loop() {
// put your main code here, to run repeatedly:
val = digitalRead(inputPin);

if(val == HIGH){
for (int i = 0; i < length; i++) {
if (notes[i] == ' ') {
delay(beats[i] * tempo); // rest
} else {
playNote(notes[i], beats[i] * tempo);
}

// pause between notes
delay(tempo / 2); 
}
}
else {
digitalWrite(ledPin, LOW);
joueSon(0,0);
delay(300);
}
}
