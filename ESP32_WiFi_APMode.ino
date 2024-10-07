#include <WiFi.h>

#define ESP32WiFi_SSID "ESP32_WiFi"
#define ESP32WiFi_PASSWD "12312345"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //delay(5000);
  Serial.println("Setting Ap ...");
  WiFi.softAP(ESP32WiFi_SSID, ESP32WiFi_PASSWD); // 同步函数，配置完才退出
  //delay(5000);
  IPAddress apip = WiFi.softAPIP();
  Serial.printf("ESP32 AP IP: %s\n", apip.toString());
  Serial.println(apip);
} 

void loop() {
  // put your main code here, to run repeatedly:

}
