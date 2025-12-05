int potentiometre;

void setup() {
  pinMode(A6, INPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  potentiometre = analogRead(A6);
  potentiometre = potentiometre * 2;
  digitalWrite(12, HIGH);
  digitalWrite(8, HIGH);
  delay(potentiometre);
  potentiometre = analogRead(A6);
  potentiometre = potentiometre * 2;
  digitalWrite(12, LOW);
  digitalWrite(8, LOW);
  delay(potentiometre);

}
