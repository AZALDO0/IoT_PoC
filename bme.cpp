/*Ceci est le module qui gère la récupération de la température et de l'humidité ambiante grace au capteur BME 680*/

#include "bme.h"
Adafruit_BME680 bme;  // I2C
float get_BME_humidity() {// Fonction pour récupérer la température du module 
  if (!bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return 0;
  }
  return bme.humidity;
}

void BME_680_Setup() {  //  Fonction pour initialiser le module 

  Serial.println(F("BME680 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1)
      ;
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150);  // 320*C for 150 ms
}