// Montage 1 modifié ... defi personnel
//
// sans buzzer mais 2 leds indiquent l'état du composant :
// led1 allumée : quelquechose bouge + temps de latence.
// led2 allumée : le composant ecoute. ( la led 2 est connecté sur le breadboard,
// fil court sur la même colonne que led 1, avant la ressistance,
// fil long sur une autre colonne de la breadboard reliée à l'emplacement D6 par un fil (MM)
// les messages indiquant l'état du montage s'affichent sur la console Arduino.)
//
//mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm

int led1Pin = 5;
int led2Pin = 6;
int inputPin = 2;
int val = 0;
int flg = 1;
int cpt = 0;
String msg1;

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(inputPin, INPUT);
  Serial.begin(9600);

  digitalWrite ( led1Pin, LOW );
  digitalWrite ( led2Pin, HIGH );

}

void loop() {

  val = digitalRead( inputPin );

  if ( val == HIGH ) {

    flg = 0;
    digitalWrite ( led2Pin, LOW );
    digitalWrite ( led1Pin, HIGH );
    cpt += 1;
    msg1 = "\n Percu ";
    msg1 += cpt;
    Serial.println( msg1 );
    Serial.print( "Latence du composant " );

    while ( val == HIGH ) {
      val = digitalRead( inputPin );
      delay( 300 );
      Serial.print( "." );

    }
  }

  if ( val == LOW && flg == 0 )  {

    digitalWrite ( led1Pin, LOW );
    digitalWrite ( led2Pin, HIGH );
    Serial.print( " dispo ! " );
    flg = 1;

  }
}
