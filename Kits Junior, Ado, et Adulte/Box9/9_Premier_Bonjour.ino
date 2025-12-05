#include <LiquidCrystal.h>
#define RS 2
#define E 6
#define D4 7
#define D5 11
#define D6 12
#define D7 13
#define COLS 16
#define ROWS 2
int pinRetro = A4;

LiquidCrystal lcd(RS,E,D4,D5,D6,D7);

void setup() {
  lcd.begin(COLS,ROWS);
  pinMode(pinRetro, OUTPUT);
}

void loop() {
  digitalWrite(pinRetro , HIGH);
  lcd.setCursor(0,0);
  lcd.print("   Bonjour !  ");
  lcd.setCursor(0,1);
  lcd.print("Je suis Robobox!");
  delay(2000);
  digitalWrite(pinRetro , LOW);
  lcd.clear();
  for( int i = 3 ; i>-1; i--){
  lcd.setCursor(6,0);
  lcd.print(i);
  delay(1000);
  lcd.clear();
  }
}
