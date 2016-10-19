#define LONGUEUR_GAMME 15

float anInput;
int scaledInput;
int level;
int gamme[LONGUEUR_GAMME];
int action = 0;
int pinLed = 6;
int pinAn = A5;
int pinDig = 4;


void setup() {
  // put your setup code here, to run once:
  pinMode(pinAn,INPUT);
  pinMode(pinDig,INPUT);
  pinMode(pinLed,OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // initialise l'array à 0
  for(int i = 0 ; i < LONGUEUR_GAMME ; i++){
  gamme[i] = 0;
  }

  // lis la valeur en input
  anInput = analogRead(pinAn);
  scaledInput = anInput/(1024/LONGUEUR_GAMME); // donne une valeur entre 1 et 15 à l'input
  level = digitalRead(pinDig);
  
  gamme[scaledInput] = 1;
  
  for(int i = 0 ; i < LONGUEUR_GAMME ; i++){
    if (gamme[i] == 1){
     Serial.print("o");
    }
    else{Serial.print(" ");
  }
  }

  Serial.print(level);
  Serial.println("");
  
  allumeLed(level);
  
}

void allumeLed(int level){
  if(level == 0){
    action = (action-1) * (action-1);
    digitalWrite(pinLed,action);
    delay(200);
  }
}
