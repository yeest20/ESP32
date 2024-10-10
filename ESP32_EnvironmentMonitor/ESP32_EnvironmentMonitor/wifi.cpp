#include <WiFi.h>
#include <ArduinoJson.h>
#include "wifi.h"

#define ESP32_SSID "ESP32"
#define ESP32_PASSWD ""
String SSID;
String PASSWD;
String Wifilist[MAX_WIFI_LIST];
int Wifinum;

bool Wifi_connect(const String &WifiConfig){
//------------------------------------ De json --------------------------------------------//
  deJson(WifiConfig);
// ----------------------------------- Connect -------------------------------------------//
  Serial.println(SSID);
  Serial.println(PASSWD);
  WiFi.begin(SSID, PASSWD);
  delay(300);
  int cnt = 20;
  while(WiFi.status() != WL_CONNECTED && cnt--){
    delay(1000);
    Serial.println("[WiFi] Connecting......");
  }
  switch(WiFi.status()){
    case WL_CONNECTED: 
      Serial.println("[WiFi] Connected!");
      Serial.printf("[WiFi] Local IP: %s\n", WiFi.localIP().toString());
      return true;
    default:
      Serial.println("[ERROR] [WiFi] Disconnected!");
      return false;
  }
}
void deJson(const String& WifiConfig){
  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, WifiConfig);
  if(error){
    Serial.println("[ERROR][JSON] deserializeJson Failed");
    Serial.println(error.f_str());
    return;
  }
  SSID = doc["SSID"].as<String>();
  PASSWD = doc["PASSWD"].as<String>();
}
void Wifi_setAPmode(){
  WiFi.softAP(ESP32_SSID, ESP32_PASSWD);
  Serial.printf("ESP32 AP IP : %s\n", WiFi.softAPIP().toString());
}
void Wifi_scan(){
  WiFi.disconnect();
  delay(100);
 
  Wifinum = WiFi.scanNetworks();
  for(int i = 0; i < Wifinum && i < MAX_WIFI_LIST; i++){
    Wifilist[i] = WiFi.SSID(i);
    //Serial.println(Wifilist[i]);
  }
}