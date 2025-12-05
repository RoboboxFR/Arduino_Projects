#include <SPI.h>
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;

const int chipSelect = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("Initialisation de la carte SD ... ");

  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("echec de l'initialisation. Il faut vérifier:");
    Serial.println("* est ce que la carte est bien inserrée?");
    Serial.println("* est ce que le câblage est correct?");
    Serial.println("* est ce que la carte SD est correctement formatée?");
    while (1);
  } else {
    Serial.println("Le câblage est bon et la carte est présente.");
  }

  Serial.println();
  Serial.print("Type de carte:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Inconnu");
  }

  if (!volume.init(card)) {
    Serial.println("Imposible de trouver une partition FAT16/FAT32.\nVérifier le formatage de la carte.");
    while (1);
  }

  Serial.print("Nombre de Clusters:    ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:      ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Nombre de Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  uint32_t volumesize;
  Serial.print("Le type de volume est: FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Taille du volume (Kb): ");
  Serial.println(volumesize);
  Serial.print("Taille du volume (Mb): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Taille du volume (Gb): ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nListe des fichiers trouvés sur la carte (nom, date et taille en octets): ");
  root.openRoot(volume);

  root.ls(LS_R | LS_DATE | LS_SIZE);
}

void loop(void) {
}
