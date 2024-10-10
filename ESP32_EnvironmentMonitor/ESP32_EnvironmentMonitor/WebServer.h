#ifndef _MYWENSERVER
#define _MYWENSERVER
#include <ESPAsyncWebServer.h>
extern AsyncWebServer server;

void Web_setPage();
void Web_setWiFiConfig();
void Web_clearSPIFFS();
void Web_rootPage();
#endif