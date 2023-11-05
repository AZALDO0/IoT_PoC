#ifndef _WIFI_PERSO_
#define _WIFI_PERSO_
#include <WiFi.h>


extern WiFiClient client;

#define WEATHER_SERVER "http://api.weatherstack.com/"
#define HTTP_PORT 80
#define WLAN_SSID "AZALDO"
#define WLAN_PASS "azertyui"
void Wifi_setup(String ssid, String password) ;
void Wifi_test_connection();

#endif

