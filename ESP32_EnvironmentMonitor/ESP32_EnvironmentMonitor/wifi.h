#ifndef _MYWIFI
#define _MYWIFI
// -------------------------------------------WIFI -------------------------------------------------------//
#define MAX_WIFI_LIST 64
extern String Wifilist[MAX_WIFI_LIST];
extern int Wifinum;
void deJson(const String&);
bool Wifi_connect(const String&);
void Wifi_setAPmode();
void Wifi_scan();
#endif