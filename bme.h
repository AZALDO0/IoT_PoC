#ifndef _WIFI_PERSO_C
#define _WIFI_PERSO_C

#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <bme68x.h>
#include <bme68x_defs.h>
#include <SPI.h>
#include <Wire.h>

#define SEALEVELPRESSURE_HPA (1013.25)



float get_BME_humidity();

void BME_680_Setup();
#endif