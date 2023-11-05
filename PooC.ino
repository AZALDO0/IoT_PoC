
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include "Cloud.h"
#include "bme.h"
#include "wireless.h"
#include "weather.h"

#define SEALEVELPRESSURE_HPA (1013.25)
//------------------------------------------------Wifi------------------------------
//#define WLAN_SSID "Livebox-09A0"
//#define WLAN_PASS "bfv3FAUW3uK5AoX9JG"


//-------------------------------------------------Servers---------------------

//-----------------------------------------------------API_keys------------------

//-----------------------------------------------------PORT----------------------

#define AIO_SERVERPORT 1883  // use 8883 for SSL
//---------------------------------------------Server_Usernames--------------------
#define AIO_USERNAME "azaldo"
#define LED_PIN 2


void serialSetup();

void setup() {
  serialSetup();
  BME_680_Setup();
  Wifi_setup(WLAN_SSID, WLAN_PASS);


  pinMode(LED_PIN, OUTPUT);
}


void loop() {
 
  int humid = 50;
  if (get_BME_humidity() > 20) {
    humid = int(get_BME_humidity());
    Serial.println(humid);
    Wifi_test_connection();
    http_send_request(WEATHER_SERVER, current, ACCESS_KEY, query);
    String weather = get_weather_value(get_data_weatherStack(), current, weather_info, 0);
    Serial.println("Description de la météo : " + weather);
    int index = weather.indexOf(' '); // Après avoir récupérer les données qui nous intéressent , on split la variable afin de les séparer en deux données humidité et météo 
    String sub_weather = weather.substring(0, index);
    int length = weather.length();
    int sub_humidity = weather.substring(index, length).toInt();
    if ( sub_weather =="Overcast" &&sub_humidity < humid) {// Bloc pour envoyé une ouverture du Store 
      publish_cloud(sub_weather);
      digitalWrite(LED_PIN, HIGH); // Alumage d'une led pour vérifier que l'envoie à bien été fait ! 
      delay(1000);
      digitalWrite(LED_PIN, LOW);
    } else {
      Serial.println("La météo n'est pas bonne pour ouvrir la fenêtre.");
    }


  } else {

    Serial.println("L'humidité est bonne");
  }
  int tmp = int(1 - (humid / 100)); // Augmentation de la fréquence de vérification de l'humidité en fonction du pourcentage de cette dernière! 
  Serial.println("le temps de delai est : " + tmp);
  delay(tmp);
}




void serialSetup() {// Initialisation de la connection série
  Serial.begin(115200);
  while (!Serial) { delay(100); }

  // We start by connecting to a WiFi network

  Serial.println();
}
