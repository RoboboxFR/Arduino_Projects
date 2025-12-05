#include <Voiture_Robobox.h>

Voiture Ma_Voiture(4, 3, 5, 7, 8, 6);

void setup()
{
}

void loop() {
  Ma_Voiture.avance(50);
  delay(500);
  Ma_Voiture.stop();
  delay(500);
}
