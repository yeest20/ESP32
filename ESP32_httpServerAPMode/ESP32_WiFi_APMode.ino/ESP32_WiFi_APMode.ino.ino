#include <WiFi.h>
#include <Wire.h>
#include <ESPAsyncWebServer.h>
#include <AHT20.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include"set.h"

#define WIFI_STA_MODE 0

#if WIFI_STA_MODE
#define SSID "YEEiPhone"
#define PASSWD "12312345"
#else
#define SSID "ESP32AP"
#define PASSWD "12312345"
#endif
// -------------------------------------------创建对象 -------------------------------------------------------------------------------------------------------------------//
AsyncWebServer server(80);   // 服务器对象
AHT20 aht20; // 温湿度传感器
Adafruit_BMP280 bmp280; //压强传感器
BH1750 bh1750; //光强传感器

//-------------------------------------------读取不同传感器数据------------------------------------------------------------------------------------------------------------//
float readSensorTemp(){
  float Temp = aht20.getTemperature();
  return Temp;
}
float readSensorHumi(){
  float Humi = aht20.getHumidity();
  return Humi;
}
float readSensorPressure(){
  float Press = bmp280.readPressure();
  return Press;
}
float readSensorAltitu(){
  float Altitu = bmp280.readAltitude(1013.25);
  return Altitu;
} 
float readSensorLight(){
  float Lux = bh1750.readLightLevel();
  return Lux;
}
void setup() {
//-------------------------------------------开启各类对象------------------------------------------------------------------------------------------------------------//
// 串口
  Serial.begin(115200);
  delay(500);
//WiFi
#if WIFI_STA_MODE
  WiFi.begin(SSID, PASSWD);
  int cnt = 20;
  while(WiFi.status() != WL_CONNECTED && cnt--){
    delay(500);
    Serial.println("Connecting....");
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Disconnect...");
    Serial.printf("ERROR NUM : ");
    Serial.println(WiFi.status());
  }else{
    Serial.println("Connected!");
    Serial.printf("IP:");
    Serial.println(WiFi.localIP());
  }

#else
  WiFi.softAP(SSID,PASSWD);
  delay(1000);
  Serial.print("APIP : ");
  Serial.println(WiFi.softAPIP().toString());
#endif
// AHT20
  Wire.begin();
  if(!aht20.begin()){
    Serial.println("Sensor AHT20 ERROR!");
    while(1);
  }
  delay(500);
// BMP280
  if(!bmp280.begin()){
    Serial.println("Sensor BMP280 ERROR!");
    while(1);
  }
  bmp280.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
  delay(500);
// BH1750
  if(!bh1750.begin()){
    Serial.println("Sensor BH1750 begin Faliure!");
    while(1);
  }
//LED
  led_init();
  delay(500);
//---------------------------------------------------------挂起服务器服务---------------------------------------------------------------------------------------------------------------//
// 根页面
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send_P(200, "text/html", index_html);  
  }); 
// LED响应
  server.on("/led", HTTP_POST, [](AsyncWebServerRequest* request){
    if(request->hasParam("state", true)){
      int ledState = request->getParam("state", true)->value().toInt();
      led_ctrl(ledState);
    }
    request->send(200, "text/plain", "LED State Changed!");

  }); 
// Sensor响应
  server.on("/sensorTemp", HTTP_GET, [](AsyncWebServerRequest* request){
      float sensorValue = readSensorTemp();
      //Serial.println(sensorValue);
      request->send(200, "text/plain", String(sensorValue));
      
  });
  server.on("/sensorHumi", HTTP_GET, [](AsyncWebServerRequest* request){
      float sensorValue = readSensorHumi();
      //Serial.println(sensorValue);
      request->send(200, "text/plain", String(sensorValue));
      
  });
  server.on("/sensorPressure", HTTP_GET, [](AsyncWebServerRequest* request){
      float sensorValue = readSensorPressure();
      //Serial.println(sensorValue);
      request->send(200, "text/plain", String(sensorValue));
      
  });
  server.on("/sensorAltitu", HTTP_GET, [](AsyncWebServerRequest* request){
      float sensorValue = readSensorAltitu();
      //Serial.println(sensorValue);
      request->send(200, "text/plain", String(sensorValue));
      
  });
  server.on("/sensorLight", HTTP_GET, [](AsyncWebServerRequest* request){
      float sensorValue = readSensorLight();
      //Serial.println(sensorValue);
      request->send(200, "text/plain", String(sensorValue));
      
  });
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}

