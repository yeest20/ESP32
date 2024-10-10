#ifndef _LED_H
#define _LED_H

#define LED_PIN 2

void led_init();
void led_ctrl(int state);

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
    .sensor-value {
      font-size: 2.0rem;
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
  <h2>ESP32 Sensor Data</h2>
  <p class="sensor-remind"> Temp </p>
  <p class="sensor-value" id="sensorTemp">Loading...</p>
  <p class="sensor-remind"> Humi </p>
  <p class="sensor-value" id="sensorHumi">Loading...</p>
  <p class="sensor-remind"> Press </p>
  <p class="sensor-value" id="sensorPressure">Loading...</p>
  <p class="sensor-remind"> Altitu </p>
  <p class="sensor-value" id="sensorAltitu">Loading...</p>
  <p class="sensor-remind"> Light </p>
  <p class="sensor-value" id="sensorLight">Loading...</p>
</body>
<script>

// -----------------------------------------------------------------------获取传感器数据--------------------------------------------------------------//
//温度
function fetchSensorDataTemp() {
    console.log("Fetching sensor data...");
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorTemp").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorTemp", true);
    xhttp.send();
  }
//湿度
function fetchSensorDataHumi() {
    console.log("Fetching sensor data...");
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorHumi").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorHumi", true);
    xhttp.send();
  }
//压力
function fetchSensorDataPressure() {
    console.log("Fetching sensor data...");
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorPressure").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorPressure", true);
    xhttp.send();
  }
//海拔
function fetchSensorAltitu() {
    console.log("Fetching sensor data...");
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorAltitu").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorAltitu", true);
    xhttp.send();
  }
//光强
function fetchSensorLight() {
    console.log("Fetching sensor data...");
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorLight").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorLight", true);
    xhttp.send();
  }
setInterval(fetchSensorDataTemp, 1000);  // 每1000毫秒（1秒）请求一次数据
setInterval(fetchSensorDataHumi, 1000);  // 每1000毫秒（1秒）请求一次数据
setInterval(fetchSensorDataPressure, 1000);  // 每1000毫秒（1秒）请求一次数据
setInterval(fetchSensorAltitu, 1000);  // 每1000毫秒（1秒）请求一次数据
setInterval(fetchSensorLight, 1000);  // 每1000毫秒（1秒）请求一次数据

// ------------------------------------------------------LED响应----------------------------------------------------------------------//
function toggleLED() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      // 请求成功后,更新按钮文本以反映LED状态
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
#endif