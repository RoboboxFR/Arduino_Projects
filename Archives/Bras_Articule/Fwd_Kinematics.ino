// This is a forward kinematics program for a two-linked robot arm on Arduino
// Created by Jonathan Trevier on June 6 2016
// Watch how it works on https://www.youtube.com/watch?v=0TTM0aJidOY
// More on www.robobox.fr

#include <Servo.h> 
 
Servo myservo1;  // Créé un objet 'Servo' et l'apelle 'monServo1'
Servo myservo2; // Créé un objet 'Servo' et l'apelle 'monServo2'
int pos = 0; // Défini une variable pour positionner nos moteurs
int i = 0;
int th[2]; // créé un array de deux ints
int thA; // Premier angle
int thB; // Second angle
int angle = 1;
float L1 = 10.0; // longueur de la première partie du bras
float L2 = 10.0; // longueur de la seconde partie du bras


void setup() 
{ 
  myservo1.attach(2); 
  myservo2.attach(4);
  Serial.begin(9600);
  Serial.write("Enter Th1 angle :");
} 
 

void loop() 
{ 
    
    while(Serial.available()) 
    {
        int number = (Serial.read() - 48); // Transforme ASCII en nombre
        th[i] = number;    
        i += 1;   
    }
   
   if(i==2 && angle ==1)
   {
       thA = th[0]*10 + th[1];
       Serial.println(thA);
       myservo1.write(thA);
       angle =2;
       i = 0;
       Serial.write("Enter Th2 angle :");
   }
   
   if(i==2 && angle ==2)
   {
       thB = th[0]*10 + th[1];
       Serial.println(thB);
       myservo2.write(thB);
       angle =1;
       i = 0;
       
       float x = L1 * cos(thA*(PI/180)) + L2 * cos((thA+thB)*PI/180);
       float y = L1 * sin(thA*(PI/180)) + L2 * sin((thA+thB)*PI/180);
       
       Serial.print("EndPoint x,y coordinates are : ");
       Serial.print(x);
       Serial.print(", ");
       Serial.println(y);   
    
       Serial.write("Enter Th1 angle :");
   }
} 
