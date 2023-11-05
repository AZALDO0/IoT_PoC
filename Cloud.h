#ifndef _WIFI_PERSO_A
#define _WIFI_PERSO_A
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "wireless.h"




#define AIO_SERVERPORT 1883  // use 8883 for SSL
//---------------------------------------------Server_Usernames--------------------
#define AIO_USERNAME "azaldo"

#define AIO_KEY "aio_xsJB62U2VIFlS4GSBCR4g22lcCF5"

#define AIO_SERVER "io.adafruit.com"


  


void MQTT_connect();

void mqtt_setup();

String receive_cloud();

void publish_cloud(String weather_value);
#endif