#ifndef _WIFI_PERSO_B
#define _WIFI_PERSO_B
#include <HTTPClient.h>

#include <ArduinoJson.h>
extern const String current;
extern const String weather_info;
extern const String query;

#define ACCESS_KEY "b79b0b5d87ddd2ec1b8a2ebc91f8f65f"


String get_weather_value(String JSON_Data, String current, String type, int last);
String get_data_weatherStack();
void http_send_request(String url, String current, String Access_key, String query);
#endif
