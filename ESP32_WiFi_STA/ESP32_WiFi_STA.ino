#include <WiFi.h>

#define SSID "YEEiPhone"
#define PASSWD "12312345"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWD);
  int cnt = 0;
  while(WiFi.status() != WL_CONNECTED && cnt <= 20){
    delay(500);
    Serial.println("Connecting......");
    cnt++;
  }
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Disconneted...");
    Serial.printf("ERROR NUM : %d\n", WiFi.status());
  }else{
    Serial.println("Connected...");
    Serial.print("IP:");
    Serial.println(WiFi.localIP());
  }

  // delay(5000);
  // if(WiFi.status() == WL_CONNECTED){
  //   Serial.println("WiFi Connected...");
  // }else{
  //   Serial.println("WiFi Disconnected...");
  //   Serial.printf("ERROR NUM: %d\n", WiFi.status());
  // }
}

void loop() {
  // put your main code here, to run repeatedly:

}
