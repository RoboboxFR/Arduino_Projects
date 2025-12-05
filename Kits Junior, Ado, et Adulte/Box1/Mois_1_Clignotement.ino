/*
  Blink

  Allume un LED pendant une seconde, puis l'atteind pendant une seconde, de manière répétée.

  La plupart des cartes Arduinos ont une LED intégrée que vous pouvez contrôler.
  Sur les ONU, MEGA et ZERO il est relié à la broche numérique 13,
  sur le MKR1000 à la broche 6. LED_BUILTIN est défini sur la broche LED correcte indépendamment de la carte utilisée.
  Si vous voulez savoir à quelle broche le voyant intégré est connecté sur votre modèle Arduino,
  vérifiez les spécifications techniques de votre conseil à: https://www.arduino.cc/en/Main/Products

  traduit le 11 novembre 2019
  par Robobox

*/

// la fonction "setup" est exécutée une fois lorsque vous appuyez sur le bouton reset ou que vous alimentez la carte
void setup() {
  // initialise le pin digitale LED_BUILTIN comme une sortie (OUTPUT).
  pinMode(12, OUTPUT);
}

// la fonction loop est exécuté encore et encore pour toujours.
void loop() {
  digitalWrite(12, HIGH);   // alume la LED (mise au potentiel de tension HIGH = HAUT)
  delay(1000);                       // attente pendant 1000 mili-seconde (1 seconde)
  digitalWrite(12, LOW);    // éteindre la LED (mise au potentiel de tension LOW = BAS)
  delay(1000);                       // attente pendant 1000 mili-seconde (1 seconde)
}
