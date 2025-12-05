#include <LiquidCrystal.h>
#include <Voiture_Robobox.h>

#define RS 2
#define E 6
#define D4 7
#define D5 11
#define D6 12
#define D7 13
#define COLS 16
#define ROWS 2

LiquidCrystal lcd(RS,E,D4,D5,D6,D7);
byte Caract1[8] = {1, 3, 7, 14, 28, 24, 24, 24};
byte Caract2[8] = {31, 31, 0, 0, 0, 0, 14, 31};
byte Caract3[8] = {16, 24, 28, 14, 7, 3, 3, 3};
byte Caract4[8] = {24, 24, 24, 28, 14, 7, 3, 1};
byte Caract5[8] = {31, 14, 0, 0, 0, 0, 31, 31};
byte Caract6[8] = {3, 3, 3, 7, 14, 28, 24, 16};

Voiture Ma_Voiture(8, 9, 10, 3, 4, 5);


void setup() {
  lcd.begin(COLS,ROWS);
  lcd.setCursor(0,0);
  lcd.print("   Bonjour !  ");
  lcd.setCursor(0,1);
  lcd.print("Je suis Robobox!");
  delay(2000);
  lcd.clear();
  lcd.createChar(0, Caract1);
  lcd.createChar(1, Caract2);
  lcd.createChar(2, Caract3);
  lcd.createChar(3, Caract4);
  lcd.createChar(4, Caract5);
  lcd.createChar(5, Caract6);
}

void loop() {
  // Afficher les yeux au centre sur l'écran
  Eyes(0);
  Ma_Voiture.avance(50);
  delay(2000);
  // Afficher les yeux à gauche sur l'écran
  Eyes(-2);
  Ma_Voiture.tourneDroite(50);
  delay(2000);
  // Afficher les yeux à droite sur l'écran
  Eyes(2);
  Ma_Voiture.tourneGauche(50);
  delay(2000);
}

void Eyes(int pos){ 
  lcd.clear();
  int b = 4+pos;
  for( int i=0; i<2; i++ ){
    int a = 5 * i;
    lcd.setCursor(0+b+a,0);
    lcd.write(byte(0));
    lcd.setCursor(1+b+a,0);
    lcd.write(byte(1));
    lcd.setCursor(2+b+a,0);
    lcd.write(byte(2));
    lcd.setCursor(0+b+a,1);
    lcd.write(byte(3));
    lcd.setCursor(1+b+a,1);
    lcd.write(byte(4));
    lcd.setCursor(2+b+a,1);
    lcd.write(byte(5));
  }
}
