
// Fonction de musique
// par Jonathan et Théodore Lafarge
// jonathan.lafarge [at] gmail.com
// janvier 2017

// déclaration des variables globales :
const int ledPin=5;                   // Définition du 'pin' de sortie de la LED
const int ledPin2=3;
const int inputPin=2;                 // Définition de 'pin' d'entrée du capteur de mouvement 
const int pinSpeaker=6;               // Définition du 'pin' de sortie du buzzer
int pirState=LOW;                     // Initialisation du statut du capteur de présence à 'LOW'
int val=0;                            // la variable 'val' contiendra le résultat de la lecture de l'état du capteur infrarouge
int compteur=0;                       // la variable 'compteur' comptera le nombre de détection du capteur
int tempo=120;                        // tempo de la musique, en beats par minute

/////////////////////////////////////////////////////////
// fonction setup() - début de l'exécution du programme :

void setup() 
    {
    pinMode(ledPin,OUTPUT);           //on définit que le 'pin' de la LED est une sortie
    pinMode(ledPin2,OUTPUT);
    pinMode(inputPin,INPUT);          //on définit que le 'pin' du capteur est une entrée
    pinMode(pinSpeaker,OUTPUT);       //on precise que le 'pin' du buzzer est en sortie
    }

/////////////////////////////////////////////////////////
//deuxième étape: création du son

void joueSon(long duree, int frequence)
    {                                 //début de notre function
    duree *=1000;
    int period=(1.0/frequence)*1000000;
    long temps_passe=0;

    while(temps_passe<duree)
        {                             //début de la boucle 'while'
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period/2);
        digitalWrite(pinSpeaker,LOW);
        delayMicroseconds(period/2);
        temps_passe+=(period);
        }                             //fin de la boucle   
    }                                 //fin de notre fonction

////////////////////////////////////////////////////////

void allume(long duree)
    {
    digitalWrite(ledPin,HIGH);    //on allume la diode : on donne donc l'instruction de passer sur la broche de la LED en HIGH
    delay(duree);                 //on laisse la diode allumée pendant le temps 'duree' ms
    digitalWrite(ledPin,LOW);     //on éteint la diode : on donne donc l'instruction de passer sur la broche de la LED en LOW
    }
    
void allume2(long duree)
    {
    digitalWrite(ledPin2,HIGH);    //on allume la diode : on donne donc l'instruction de passer sur la broche de la LED en HIGH
    delay(duree);                 //on laisse la diode allumée pendant le temps 'duree' ms
    digitalWrite(ledPin2,LOW);     //on éteint la diode : on donne donc l'instruction de passer sur la broche de la LED en LOW
    }

////////////////////////////////////////////////////////////////////
//FONCTION DE MUSIQUE

//Fonction de calcul de fréquence d'une note en fonction de sa hauteur et de son octave
float frequenceNote(String hauteur, int octave)
    {
	  float r=1.05946;               // rapport des fréquences de deux demi-tons. Source : http://www.deleze.name/~marcel//physique/musique/Frequences.pdf
  	int ecartAuLa=-100;            // on initialise l'écart au la à -100 demi-tons, par sécurité et par défaut
    float frequence=0;             // on initialise la fréquence à zéro, par sécurité et par défaut

    // on identifie le nombre de demi-ton jusqu'à la note la :
    if(hauteur=="do")                     {ecartAuLa=-9;}
    if(hauteur=="dod" || hauteur=="reb")  {ecartAuLa=-8;}
    if(hauteur=="re")                     {ecartAuLa=-7;}
    if(hauteur=="red" || hauteur=="mib")  {ecartAuLa=-6;}
    if(hauteur=="mi")                     {ecartAuLa=-5;}
    if(hauteur=="fa")                     {ecartAuLa=-4;}
    if(hauteur=="fad" || hauteur=="solb") {ecartAuLa=-3;}     
    if(hauteur=="sol")                    {ecartAuLa=-2;}       
    if(hauteur=="sold" || hauteur=="lab") {ecartAuLa=-1;}      
    if(hauteur=="la")                     {ecartAuLa=0;}
    if(hauteur=="sib" || hauteur=="lad")  {ecartAuLa=1;}       
    if(hauteur=="si")                     {ecartAuLa=2;}

    // on calcule la fréquence en Hertz correspondante à la note et à l'octave, par rapport au la 440 Hz :
    frequence=pow(2,(octave-3))*pow(r,(ecartAuLa))*440; //source : http://www.deleze.name/~marcel//physique/musique/Frequences.pdf
    
    return(frequence);
    }

// Fonction de calcul de la durée d'une note en milliseconde en fonction du tempo et du type de note
int dureeNote(String duration,int tempo)
    {
    int msParBeat=(60*100/tempo)*10;      // à partir du tempo, on calcule la durée entre deux "beats", en millisecondes
    float temps=0;                        // "temps" contiendra le nombre de temps de la mesure que durera la note.
    int duree;                            // "duree" contiendra la durée en milliseconde de la note au tempo demandé
    
    if(duration=="ronde")   {temps=4;}
    if(duration=="blanche") {temps=2;}
    if(duration=="noire")   {temps=1;}
    if(duration=="croche")  {temps=1/2;}
    if(duration=="triolet") {temps=1/3;}  // triolet de croche
    if(duration=="double")  {temps=1/4;}  // double-croche
    if(duration=="triple")  {temps=1/8;}  // triple croche   
    
    // pour jouer une note pointée, il suffira de jouer la note, puis immédiatement jouer la moitié de la note
    // par exemple, noire pointée = noire puis croche 

    duree=msParBeat*temps;
    return(duree);
    }
    
void joueNote(String hauteur, String duration, int octave)
    {
    //NOTICE DE LA FONCTION joueNote() :
    // hauteur : do, re, mi, fa, sol, la, si, silence
    // ajouter d pour dièse et b pour bemol. Exemple : dod = do dièse

    // duration : ronde, blanche, noire, croche, double

    // octave : de 0 (grave) à 9 (aiguë)
    
    int freq=0;
    int dur=0;

    freq=frequenceNote(hauteur,octave);
    dur=dureeNote(duration,tempo);   
                
    if(hauteur=="silence") // silence
        {
        delay(dur);
        }
    else
        {
        joueSon(dur,freq);
        }
      
    }

    
//////////////////////////////////////////////////////
// quelques morceaux

void starwars() 
    {
    tempo=90;
    
    joueNote("sol","noire",1);
    allume(20);
    joueNote("sol","noire",1);
    allume(20);
    joueNote("sol","noire",1);
    allume(20);
    joueNote("mib","croche",1);     
    joueNote("mib","double",1);
    allume(20);
    joueNote("sib","double",1);
    allume(20);
    joueNote("sol","noire",1);
    allume(20);
    joueNote("mib","croche",1);
    joueNote("mib","double",1);
    allume(20);
    joueNote("sib","double",1);
    allume(20);
    joueNote("sol","noire",1);
    joueNote("sol","croche",1);
    joueNote("silence","croche",1);
    
    joueNote("re","noire",2);
    allume(20);
    joueNote("re","noire",2);
    allume(20);
    joueNote("re","noire",2);
    allume(20);
    joueNote("mib","croche",2);
    joueNote("mib","double",2);
    allume(20);
    joueNote("sib","double",1);
    allume(20);
    joueNote("fad","noire",1);
    allume(20);
    joueNote("mib","croche",1);
    joueNote("mib","double",1);
    allume(20);
    joueNote("sib","double",1);
    allume(20);
    joueNote("sol","noire",1);
    joueNote("sol","croche",1);
    allume(20);
    joueNote("silence","croche",1);
   }
//////////////////////////////////////////////////////
void happybirthday()
    {
	tempo=140;
    joueNote("do","croche",1);
    joueNote("do","double",1);
    allume(50);
    joueNote("do","double",1);
    allume(50);
    joueNote("re","noire",2);
    allume(50);
    joueNote("do","noire",1);
    allume(50);
    joueNote("fa","noire",2);
    allume(50);
    joueNote("mi","blanche",2);
    allume(50);
    joueNote("do","croche",1);
    joueNote("do","double",1);
    allume(50);
    joueNote("do","double",1);
    allume(50);
    joueNote("re","noire",2);
    allume(50);
    joueNote("do","noire",1);
    allume(50);
    joueNote("sol","noire",2);
    allume(50);
    joueNote("fa","blanche",2);
    allume(50);
    joueNote("do","croche",1);
    joueNote("do","double",1);
    allume(50);
    joueNote("do","double",1);
    allume(50);
    joueNote("do","noire",2);
    allume(50);
    joueNote("la","noire",2);
    allume(50);
    joueNote("fa","noire",2);
    allume(50);
    joueNote("mi","noire",2);
    allume(50);
    joueNote("re","noire",2);
    allume(50);
    joueNote("sib","croche",2);
    joueNote("sib","double",2);
    allume(50);
    joueNote("sib","double",2);
    allume(50);
    joueNote("la","noire",2);
    allume(50);
    joueNote("fa","noire",2);
    allume(50);
    joueNote("sol","noire",2);
    allume(50);
    joueNote("fa","blanche",2);
    }

/////////////////////////////////////////////////////
void j_ai_du_bon_tabac()
  {
   tempo=200;
    
    joueNote("fa","croche",1); //Fa croche (première octave)
    joueNote("sol","croche",1); //Sol croche (première octave)
    joueNote("la","croche",1); //La croche (première octave)
    joueNote("fa","croche",1); //Fa croche (première octave)
    joueNote("sol","croche",1); //Sol croche (première octave)
    joueNote("silence","croche",1);
    joueNote("sol","croche",1); //Sol croche (première octave)
    joueNote("la","croche",1); //La croche (première octave)
    joueNote("sib","croche",1); //Si bemol croche (première octave)
    joueNote("silence","croche",1);
    joueNote("sib","croche",1); //Si bemol croche (première octave)
    joueNote("silence","croche",1);    
    joueNote("la","croche",1); //La croche (première octave)
    joueNote("silence","croche",1);
    joueNote("la","croche",1); //La croche (première octave)
    joueNote("silence","croche",1);

