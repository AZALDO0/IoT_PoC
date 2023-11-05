
/*Ceci est le module pour établir la connection Wifi de l'ESP 32 */
#include "wireless.h"

WiFiClient client;

void Wifi_setup(String ssid, String password) {//Initialisation de la connection Wifi en se connectant au point d'accès
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.

void Wifi_test_connection() { // test de connection 

  if (!client.connect(WEATHER_SERVER, HTTP_PORT)) {
    return;
  }
}