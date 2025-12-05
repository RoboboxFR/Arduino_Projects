int TRIG_PIN = A0;
int ECHO_PIN = A1;

int distActuelle = 0;
int cm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //initialise la communication série
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  
    distActuelle = lectureDistance();

    Serial.println(distActuelle);

}

int lectureDistance() { // Envoi la distance mesurée par le capteur de distance
  long lecture_echo;
  long cm;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  lecture_echo = pulseIn(ECHO_PIN, HIGH);
  cm = lecture_echo/58;
  
  return cm;
}
