#include <ESPAsyncWebServer.h>
#include "WebServer.h"
#include "htmlConfig.h"
#include "fileSystem.h"
#include "sensorData.h"
#include "wifi.h"

AsyncWebServer server(80);

void Web_setPage(){
  Wifi_scan();
  delay(1000);
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(200, "text/html", htmlSetPage);
  });
  server.on("/getWifiList", HTTP_GET, [](AsyncWebServerRequest* request){
    String jsonList = "[";
    for(size_t i = 0; i < Wifinum && i < MAX_WIFI_LIST; i++){
      jsonList += "\"" + Wifilist[i] + "\"";
      if (i < Wifinum - 1) jsonList += ",";
    }
    jsonList += "]";
    //Serial.println(jsonList);
    request->send(200, "application/json", jsonList);
  });
}

void Web_setWiFiConfig(){
  server.on("/setWiFiConfig", HTTP_POST, [](AsyncWebServerRequest* request){
    String ssid;
    String passwd;
    if(request->hasParam("ssid", true)){
      ssid = request->getParam("ssid", true)->value();
    }
    if(request->hasParam("password", true)){
      passwd = request->getParam("password", true)->value();
    }
    String WiFiConfig = "{\"SSID\": \"" + ssid + "\", \"PASSWD\" : \"" + passwd + "\" }";
    if(fileSystem_writeWiFiConfig(WiFiConfig)){
      String respondMessage = "{\"message\":\"Configuration saved Successfully!\"}";
      request->send(200, "application/json", respondMessage);
      ESP.restart();
    }else{
      String respondMessage = "{\"message\":\"Configuration saved Failed\"}";
      request->send(200, "application/json", respondMessage);
    }
  });
}

void Web_clearSPIFFS(){
  server.on("/clearPage", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(200, "text/html", htmlClearPage);
  });

  server.on("/clearSPIFFS", HTTP_POST, [](AsyncWebServerRequest* request){
    request->send(200, "application/json", "{\"message\" : \"SPIFFS Cleared Successfully!\"}");
    clearSPIFFS();
  });
}

void Web_rootPage(){
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send(200, "text/html", htmlHomePage);
  });

  server.on("/getAllSensorData", HTTP_GET, [](AsyncWebServerRequest* request){
    getAllSensorData();
    String jsonData = "{\"temperature\":\"" + String(sensorTemp) + 
                      "\", \"humidity\":\"" + String(sensorHumi) + 
                      "\", \"pressure\":\"" + String(sensorPressure) + 
                      "\", \"altitude\":\"" + String(sensorAltitu) + 
                      "\", \"light\":\"" + String(sensorLight) + 
                      "\"}";
    request->send(200, "application/json", jsonData);
  });


}