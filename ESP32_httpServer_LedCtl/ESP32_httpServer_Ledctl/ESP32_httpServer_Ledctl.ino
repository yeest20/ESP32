#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include"led.h"

#define SSID "YEEiPhone"
#define PASSWD "12312345"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<style>
  <style>
    /* Flexbox layout to center the button */
    body {
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
      margin: 0;
    }
    html {
      font-family: Arial;
      display: inline-block;
      margin: 0px auto;
      text-align: center;
    }

    h2 {
      font-size: 3.0rem;
      text-align: center;
    }

    p {
      font-size: 3.0rem;
    }

    .units {
      font-size: 1.2rem;
    }

    .dht-labels {
      font-size: 1.5rem;
      vertical-align: middle;
      padding-bottom: 15px;
    }

    /* Button Style */
    .custom-button {
      display: inline-block;
      background-color: #007BFF;
      color: white;
      border-radius: 10px;
      padding: 20px 40px;
      font-size: 2.5rem;
      cursor: pointer;
      transition: background-color 0.3s ease;
    }

    .custom-button:hover {
      background-color: #0056b3;
    }
</style>
</head>
<body>
  <div><h2>ESP32 LED Control</h2></div>
  <p>
    <button onclick="toggleLED()" class="custom-button">Toggle LED</button>
  </p>
</body>
<script>
function toggleLED() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      // 请求成功后，更新按钮文本以反映LED状态
      var button = document.querySelector("button");
      if (button.innerText === "Toggle LED") {
        button.innerText = "LED ON";
      } else {
        button.innerText = "Toggle LED";
      }
    }
  };

  // 发送LED控制请求到服务器端
  var ledState = document.querySelector("button").innerText === "Toggle LED" ? 1 : 0;
  xhttp.open("POST", "/led", true);
  xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhttp.send("state=" + ledState);
}
</script>
</html>)rawliteral";
AsyncWebServer server(80);   // 设置监听端口


void webone(AsyncWebServerRequest *request){
  //Serial.println("web one running...");
  request->send(200, "text/html", "Hello from ESP32!");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // 连接wifi
  led_init();
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
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request){
    request->send_P(200, "text/html", index_html);    
  }); // 注册 根服务函数
  server.on("/led", [](AsyncWebServerRequest* request){
    if(request->hasParam("state", true)){
      int ledState = request->getParam("state", true)->value().toInt();
      led_ctrl(ledState);
    }
    request->send(200, "text/plain", "LED State Changed!");
  }); 
  server.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

}
