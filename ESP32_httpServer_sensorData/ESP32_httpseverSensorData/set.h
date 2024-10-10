#ifndef _LED_H
#define _LED_H

#define LED_PIN 2

void led_init();
void led_ctrl(int state);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="zh">
<head>
<meta charset="UTF-8">
<title>ESP32 LED Control</title>
<style>
  body {
    background-color: #121212;
    color: #e0e0e0;
    font-family: Arial, sans-serif;
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height: 100vh;
    margin: 0;
  }

  h2 {
    font-size: 3rem;
    margin: 20px 0; /* 增加顶部间距 */
    color: #BB86FC;
  }

  .sensor-value {
    font-size: 2.5rem;
    color: #03DAC6;
  }

  .sensor-remind {
    font-size: 1.5rem;
    color: #B0BEC5;
  }

  .custom-button {
    display: inline-block;
    background-color: #6200EE;
    color: white;
    border-radius: 10px;
    padding: 15px 30px;
    font-size: 2rem;
    cursor: pointer;
    transition: background-color 0.3s ease, transform 0.2s ease;
    margin: 20px 0;
  }

  .custom-button:hover {
    background-color: #3700B3;
    transform: scale(1.05);
  }

  .sensor-container {
    display: flex;
    flex-wrap: wrap; /* 允许换行 */
    justify-content: center; /* 居中对齐 */
    width: 100%; /* 占满宽度 */
    max-width: 800px; /* 设置最大宽度 */
    margin: 20px 0; /* 增加上下间距 */
  }

  .sensor-row {
    display: flex;
    flex-direction: column; /* 纵向排列 */
    align-items: center; /* 居中对齐 */
    margin: 10px;
    width: calc(33.33% - 20px); /* 第一排三个控件，第二排两个控件 */
  }

  .sensor-row:nth-child(4), .sensor-row:nth-child(5) {
    width: calc(50% - 20px); /* 第二排两个控件 */
  }
</style>
</head>
<body>
  <h2>ESP32 LED Control</h2>
  <button onclick="toggleLED()" class="custom-button">Toggle LED</button>

  <h2>ESP32 Sensor Data</h2>
  <div class="sensor-container">
    <div class="sensor-row">
      <p class="sensor-remind">温度:</p>
      <p class="sensor-value" id="sensorTemp">Loading...</p>
    </div>
    <div class="sensor-row">
      <p class="sensor-remind">湿度:</p>
      <p class="sensor-value" id="sensorHumi">Loading...</p>
    </div>
    <div class="sensor-row">
      <p class="sensor-remind">压力:</p>
      <p class="sensor-value" id="sensorPressure">Loading...</p>
    </div>
    <div class="sensor-row">
      <p class="sensor-remind">海拔:</p>
      <p class="sensor-value" id="sensorAltitu">Loading...</p>
    </div>
    <div class="sensor-row">
      <p class="sensor-remind">光强:</p>
      <p class="sensor-value" id="sensorLight">Loading...</p>
    </div>
  </div>

<script>
// Sensor data fetching functions remain unchanged
// -----------------------------------------------------------------------获取传感器数据--------------------------------------------------------------//
function fetchSensorDataTemp() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorTemp").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorTemp", true);
    xhttp.send();
}

function fetchSensorDataHumi() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorHumi").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorHumi", true);
    xhttp.send();
}

function fetchSensorDataPressure() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorPressure").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorPressure", true);
    xhttp.send();
}

function fetchSensorAltitu() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorAltitu").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorAltitu", true);
    xhttp.send();
}

function fetchSensorLight() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        document.getElementById("sensorLight").innerHTML = this.responseText;
      }
    };
    xhttp.open("GET", "/sensorLight", true);
    xhttp.send();
}

setInterval(fetchSensorDataTemp, 1000);
setInterval(fetchSensorDataHumi, 1000);
setInterval(fetchSensorDataPressure, 1000);
setInterval(fetchSensorAltitu, 1000);
setInterval(fetchSensorLight, 1000);

// LED control function remains unchanged
function toggleLED() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      var button = document.querySelector("button");
      button.innerText = button.innerText === "Toggle LED" ? "LED ON" : "Toggle LED";
    }
  };
  var ledState = document.querySelector("button").innerText === "Toggle LED" ? 1 : 0;
  xhttp.open("POST", "/led", true);
  xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhttp.send("state=" + ledState);
}
</script>
</body>
</html>

)rawliteral";
#endif