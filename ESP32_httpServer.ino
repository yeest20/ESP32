#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#define SSID "YEEiPhone"
#define PASSWD "12312345"

AsyncWebServer server(80);   // 设置监听端口

void webroot(AsyncWebServerRequest *request){
  //Serial.println("web root running.....");
  request->send(200, "text/html", "Hello from ESP32!");
  return ;
}

void webone(AsyncWebServerRequest *request){
  //Serial.println("web one running...");
  request->send(200, "text/html", "Hello from ESP32!");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // 连接wifi
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
  
  server.on("/", webroot); // 注册 根服务函数
  server.on("/1", webone); 
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}
