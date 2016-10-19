// Transmits IR signal using the IR LED
// Transmets un signal infrarouge grâce à la LED IR

#include <IRremote.h>
IRsend irsend;
unsigned int powerOn[10] = {4450,4500,550,1700,500,1750,500,1750,500,600};

void setup()
{
    Serial.begin(9600);
}

void loop() {
    irsend.sendRaw(powerOn,10,38); // 38kHz
    delay(100);
}
