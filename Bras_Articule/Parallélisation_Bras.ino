// L'utilisation d'une class et la parallélisation du mouvement des bras est librement inspiré de ce tuto
// expliquant comme paralléliser de multiples actions
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1/overview

#include <Servo.h>

// Objet permettant la parallélisation des servos
class ServoBox
{
  Servo servo; // Instance du servo
  int pos; // Position courante du servo
  int increment; // Valeur d'incrément du servo
  int posMax; // Position Maximum acceptée par le servo : par ex l'avant bras va de 0 à 120° alors que l'épaule peut aller de 0 à 180°
  int updateInterval;
  unsigned long lastUpdate;

  public:
    // Constantes permettant de connaitre la "direction" du mouvement 
    const static int FORWARD = 1;
    const static int BACKWARD = -1;

    // Initialisation
    // interval permettant un mouvement plus ou moins rapide
    // setPosMax est la valeur maximum acceptée par le servo
    ServoBox(int interval, int setPosMax)
    {
      posMax = setPosMax;
      updateInterval = interval;
      increment = 1;
    }

    void Attach(int pin)
    {
      servo.attach(pin);
    }

    void Detach()
    {
      servo.detach();
    }

    // Fonction de mise à jour du mouvement du servo
    void Update(int movementDirection)
    {
      //Serial.println(lastUpdate);
      if ((millis() - lastUpdate) > updateInterval)
      {
        lastUpdate = millis();
        // Serial.println(pos);
        switch (movementDirection) {
          case FORWARD:
            if (pos < posMax) {
              pos += increment;
              servo.write(pos);
            }
          break;
          case BACKWARD:
            if (pos > 0) {
              pos -= increment;
              servo.write(pos);
            }
          break;
        }
      }
    }

    void Init(int pos)
    {
      servo.write(pos);
    }
};

// Initialisation de mes deux servos avec les valeurs maximum autorisées
ServoBox monServo1(15, 120);
ServoBox monServo2(15, 90);

int inputButton1 = 2;
int inputButton2 = 3;

void setup() {
  pinMode(inputButton1, INPUT);
  pinMode(inputButton2, INPUT);
  Serial.begin(9600); // Debug
  monServo1.Attach(4);
  monServo1.Init(0);
  monServo2.Attach(5);
  monServo2.Init(0);
}

void loop() {
  if (digitalRead(inputButton1) == HIGH) {
    // Lorsqu'on presse le bouton, le bras se "lève"
    monServo1.Update(ServoBox::FORWARD);
  } else {
    // Lorsqu'on relâche le bouton, le bras se baisse automatiquement
    monServo1.Update(ServoBox::BACKWARD);
  }

  if (digitalRead(inputButton2) == HIGH) {
    // Lorsqu'on presse le bouton, l'avant-bras se "lève"
    monServo2.Update(ServoBox::FORWARD);
  } else {
    // Lorsqu'on relâche le bouton, l'avant-bras se baisse automatiquement
    monServo2.Update(ServoBox::BACKWARD);
  }
}
