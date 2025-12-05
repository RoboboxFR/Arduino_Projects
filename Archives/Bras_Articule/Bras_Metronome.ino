// Merci à Sacha pour son innovation
// Il propose un bras métronome qui peut frapper une cymbale !

Servo monServo1;
Servo monServo2;
int posiMoteur =0;

void setup() 
{

monServo1.attach(4);
monServo2.attach(4);
}

void loop() 
{
for(posiMoteur = 0; posiMoteur <=90;posiMoteur +=1)
{
monServo1.write(posiMoteur);
monServo2.write(posiMoteur);
delay(7); 
}
for(posiMoteur = 90; posiMoteur >=0;posiMoteur -=1)
{
monServo1.write(posiMoteur);
monServo2.write(posiMoteur);
   delay(7);
  }
}
