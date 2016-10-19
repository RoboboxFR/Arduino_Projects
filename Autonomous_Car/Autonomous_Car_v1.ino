#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>
 
#define TRIG_PIN A3 // Pin A3 on the Motor Drive Shield connected to the ultrasonic sensor
#define ECHO_PIN A5 // Pin A5 on the Motor Drive Shield connected to the ultrasonic sensor
#define MAX_DISTANCE_POSSIBLE 200 // sets maximum useable sensor measuring distance to 1000cm
#define MAX_VITESSE 210 // sets speed of DC traction motors to 120/256 or about 47% of full speed - to reduce power draining.
#define COLL_DIST 15 // sets distance at which robot stops and reverses to 10cm

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE_POSSIBLE); // sets up sensor library to use the correct pins to measure distance.
AF_DCMotor moteurGauche(3); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor moteurDroit(4); // create motor #2, using M2 output, set to 1kHz PWM frequency
Servo servoTourneTete;  // create servo object to control a servo
 
int posiServo = 0; // this sets up variables for use in the sketch (code)
int maxAngle = 0;
int distActuelle = 0;
String directionMotor = "";
int defVitesse = 0;
 
//-------------------------------------------- SETUP LOOP ----------------------------------------------------------------------------
void setup() {
  servoTourneTete.attach(9);  // attaches the servo on pin 9 (SERVO_2 on the Motor Drive Shield to the servo object
  servoTourneTete.write(90); // tells the servo to position at 90-degrees ie. facing forward.
  delay(2000); // delay for two seconds
  Avance(); // run function to make robot move forward
  Serial.begin(9600);
}
 
//---------------------------------------------MAIN LOOP ------------------------------------------------------------------------------
void loop() {
  
  forceAvance(); // check that if the robot is supposed to be moving forward, that the drive motors are set to move forward - this is needed to overcome some issues with only using 4 AA NiMH batteries
  
  int distActuelle = 0;
  int distActuelleTemp = 0;
  int distMax = 0;
  Serial.print("a");
  servoTourneTete.write(144); // set servo to face left 54-degrees from forward
  delay(120); // wait 120milliseconds for servo to reach position
  Serial.print("b");
  for (posiServo = 144; posiServo >= 36; posiServo -= 18) // loop to sweep the servo (& sensor) from 144-degrees left to 36-degrees right at 18-degree intervals.
  {
    servoTourneTete.write(posiServo);  // tell servo to go to position in variable 'posiServo'
      Serial.print("c");
    delay(200); // wait 90ms for servo to get to position
    forceAvance(); // check the robot is still moving forward
  Serial.print("d");
    // Récupère une distance observée > 0 , ( 0 = bug )
    distActuelleTemp = 0;
    while (distActuelleTemp == 0){ 
      distActuelleTemp = lectureDistance();
        Serial.print("e");
      Serial.println(distActuelleTemp);

    }
    distActuelle = distActuelleTemp;

    // Evite un objet si proche
    if (distActuelle < COLL_DIST) { // if the current distance to object is less than the collision distance
      EviteObjet(); // run the EviteObjet function
      break; // jump out of this loop
    }

    // Enregistre l'angle avec la plus grande distance
    if (distActuelle > distMax) {
      distMax = distActuelle;
      maxAngle = posiServo;
    }

  }
}


//-------------------------------------------------------------------------------------------------------------------------------------
void EviteObjet() { // we're about to hit something so move backwards, stop, find where the empty Route is.
  Recule();
  delay(500);
  Arret();
  ChoixMeilleureDirection();
  Avance();
}

//-------------------------------------------------------------------------------------------------------------------------------------
int lectureDistance() { // read the ultrasonic sensor distance
  delay(70);
  unsigned int uS = sonar.ping();
  int cm = uS / US_ROUNDTRIP_CM;
  return cm;
}

//-------------------------------------------------------------------------------------------------------------------------------------
// Force le mouvement en avant
void forceAvance() {
  if (directionMotor == "AVANCE") {
    moteurGauche.run(FORWARD);  // ensure motors are going forward
    moteurDroit.run(FORWARD);
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------
void ChoixMeilleureDirection() { // set direction for travel based on a very basic distance map, simply which direction has the greatest distance to and object - turning right or left?
  if (maxAngle < 90) {
    TourneDroite();
  }
  if (maxAngle > 90) {
    TourneGauche();
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------
void Avance() {
  directionMotor = "AVANCE";
  moteurGauche.run(FORWARD);      // turn it on going forward
  moteurDroit.run(FORWARD);      // turn it on going forward
  for (defVitesse = 0; defVitesse < MAX_VITESSE; defVitesse += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    moteurGauche.setSpeed(defVitesse);
    moteurDroit.setSpeed(defVitesse);
    delay(5);
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------
void Recule() {
  directionMotor = "RECULE";
  moteurGauche.run(BACKWARD);      // turn it on going forward
  moteurDroit.run(BACKWARD);     // turn it on going forward
  for (defVitesse = 0; defVitesse < MAX_VITESSE; defVitesse += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    moteurGauche.setSpeed(defVitesse);
    moteurDroit.setSpeed(defVitesse);
    delay(5);
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------
void TourneDroite() {
  directionMotor = "DROIT";
  moteurGauche.run(FORWARD);      // turn motor 1 forward
  moteurDroit.run(BACKWARD);     // turn motor 2 backward
  delay(1000); // run motors this way for 400ms
}

//-------------------------------------------------------------------------------------------------------------------------------------
void TourneGauche() {
  directionMotor = "GAUCHE";
  moteurGauche.run(BACKWARD);     // turn motor 1 backward
  moteurDroit.run(FORWARD);      // turn motor 2 forward
  delay(1000); // run motors this way for 400ms
}

//-------------------------------------------------------------------------------------------------------------------------------------
void Arret() {
  moteurGauche.run(RELEASE);
  moteurDroit.run(RELEASE);
}
