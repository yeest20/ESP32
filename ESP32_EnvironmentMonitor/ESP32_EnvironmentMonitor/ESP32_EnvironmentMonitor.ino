#include "wifi.h"
#include "fileSystem.h"
#include "WebServer.h"

String wifiConfig;
unsigned long perviousMillis = 0;
const long interval = 10000;

void setup() {
  Serial.begin(115200);
  fileSystem_init();
  if(fileSystem_readWiFiConfig(wifiConfig)){
    Serial.println("Load Config Successfully!");
    if(Wifi_connect(wifiConfig)){
      Web_rootPage();
      Web_clearSPIFFS();
      server.begin();
    }else{
      return;
    }
  }else{
    Serial.println("No Config!");
    Wifi_setAPmode();
    Web_setPage(); 
    Web_setWiFiConfig();
    Web_clearSPIFFS();
    server.begin();
    while(1);
  }
}

void loop() {
  unsigned long currentMillis = millis();
  // WiFi 重连
  if(currentMillis - perviousMillis >= interval){
    perviousMillis = currentMillis;
    if(WiFi.status() != WL_CONNECTED){
      int cnt = 10;
      while(cnt && !Wifi_connect(wifiConfig)) cnt--;
      if(WiFi.status() != WL_CONNECTED) return; 
    }
  }
}
