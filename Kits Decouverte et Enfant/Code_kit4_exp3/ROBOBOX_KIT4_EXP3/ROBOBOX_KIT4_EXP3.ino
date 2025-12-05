void setup() {
  pinMode(A0, INPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  if (analogRead(A6) > 512) {
    digitalWrite(12, HIGH);
  }
  if (analogRead(A6) < 512) {
    digitalWrite(12, LOW);
  }
  if (analogRead(A0) > 512) {
    digitalWrite(11, HIGH);
  }
  if (analogRead(A0) < 512) {
    digitalWrite(11, LOW);
  }

}
