int TRIG_PIN = 2;
int ECHO_PIN = 4;

int distActuelle = 0;
int cm;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //initialise la communication série
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  
    distActuelle = lectureDistance();

    Serial.println(distActuelle);

    if (distActuelle > 20) {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
    }
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
