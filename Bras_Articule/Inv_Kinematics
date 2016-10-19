// This is an inverse kinematics program for a two-linked robot arm on Arduino
// Created by Jonathan Trevier on June 6 2016
// More on www.robobox.fr
#include <Servo.h> 
 
Servo myservo1;  // Créé un objet 'Servo' et l'apelle 'monServo1'
Servo myservo2; // Créé un objet 'Servo' et l'apelle 'monServo2'
int pos = 0; // Défini une variable pour positionner nos moteurs
int i = 0;
float XY[2]; // créé un array de deux ints
float XA; // Coordonnée X du point désiré
float YA; // Coordonnée Y du point désiré
int coord = 1;
float L1 = 9.0; // longueur de la première partie du bras
float L2 = 11.0; // longueur de la seconde partie du bras


void setup() 
{ 
  myservo1.attach(2);
  myservo2.attach(4);
  Serial.begin(9600);
  Serial.write("Enter target X coordinates :");
} 
 

void loop() 
{ 
    
    while(Serial.available()) 
    {
        int number = (Serial.read() - 48); // Transforme ASCII en nombre
        XY[i] = number;    
        i += 1;   
    }
   
   if(i==2 && coord ==1)
   {
       XA = XY[0]*10 + XY[1];
       Serial.println(XA);
       coord =2;
       i = 0;
       Serial.write("Enter target Y coordinates :");
   }
   
   if(i==2 && coord ==2)
   {
       YA = XY[0]*10.0 + XY[1];
       Serial.println(YA);
       coord =1;
       i = 0;

       float th2 = ( acos( ( (XA*XA) + (YA*YA) - (L1*L1) - (L2*L2))  / (2.0 * L1 * L2) ) ) * (180.0/PI);
       
       float th1 = ( atan2(YA,XA) - atan2(L1 + L2 * cos(th2 * PI/180 ), L2 * sin(th2 * PI/180 ) ) ) * (180.0/PI);
       if (th1 < 0)
       { th1 = -th1 ;};
       
       myservo1.write(th1);
       myservo2.write(th2);
       
       Serial.print("Angles Th1 and Th2 are :");
       Serial.print(th1);
       Serial.print(", ");
       Serial.println(th2);   
    
       Serial.write("Enter target X coordinates :");
   }
} 
