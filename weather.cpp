/*Ceci est le module qui permet de gérer la vérification de la météo extérieur en
interrogeant un serveur weatherstack */

#include "weather.h"
HTTPClient http;
String JSON_Data;
String const current = "current";
String const forcast = "forcast";
String const weather_info = "weather_descriptions";
String const query = "Paris";
void http_send_request(String url, String current, String Access_key, String query) {  //Fonction pour envoyer la requêtre Http contenant l'url , les données météos actuellls , la clée d'accès ainsi que la localisation souhaité

  http.begin(url + current + "?access_key=" + Access_key + "&query=" + query);  //
}

String get_data_weatherStack() { //Fonction permettant de récupérer le retour de la requête Http 

  int httpCode = http.GET();
  if (httpCode > 0) {
    JSON_Data = http.getString();
    Serial.println(JSON_Data);



    http.end();
  } else {
    Serial.println("Error on HTTP request");
  }
  return JSON_Data;
}
/*Fonction permettant de récupérer la fichier JSON envoyé par le serveur et de récupérer les valeurs qui nous interessent ! */
String get_weather_value(String JSON_Data, String current, String type, int last = -1) { 
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, JSON_Data);
  //Display the Current Weather Info

  if (last != -1) {
    String value1 = doc[current][type][last];
    String value2 = doc[current]["humidity"];
    Serial.println("Valeur de météo : " + value1 + " "+value2);

     return value1 + " "+value2;
  } else {
    String val1 = doc[current][type];
    String val2 = doc["current"]["humidity"];
    Serial.println("Valeur de météo : " + val1 + " "+val2);

    return val1 + " "+val2;
  }
}