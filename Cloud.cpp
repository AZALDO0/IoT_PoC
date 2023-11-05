#include "Cloud.h"
/*Module qui gère l'envoie et la réception de données depuis le serveur Adafruit IO */
//--------------------------------------MQTT_Setup-------------------------------
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
// Setup a feed called 'photocell' for publishing.
Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");
// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/onoff");

/*Ceci est la boucle qui permet de faire la connection MQTT afin 
de pouvoir envoyer les données vers un serveur cloud*/

void MQTT_connect() { //Fonction pour la mise en place de la connection avec le serveur ! 
  int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {  // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1)
        ;
    }
  }
  Serial.println("MQTT Connected!");
}

void publish_cloud(String weather_value) {  // Fonction pour l'envoie des données vers le serveur 
  MQTT_connect();
  Serial.print(F("\nSending weather val "));
  Serial.print("Valeur envoyé par publish_cloud : (1)  " + weather_value); // Dans notre cas nous envoyons la valeur 1 , ce qui permet d'allumer la Led (Store , servomoteur)
  Serial.print("...");
  if (!photocell.publish(1)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }
}

String receive_cloud() { // Fonction permettant de recevoir des données depuis le serveur via les souscription
   MQTT_connect();
  String lastRead;
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(1000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      lastRead = (char *)onoffbutton.lastread;
      Serial.println(lastRead);
    }
  }
  return lastRead;
}