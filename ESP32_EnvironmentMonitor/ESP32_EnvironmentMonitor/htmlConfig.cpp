#include "htmlConfig.h"

// -------------------------------------------------------配置WiFi页面 --------------------------------------------------//
const char* htmlSetPage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WiFi Config</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
        }
        input, select {
            margin-bottom: 10px;
        }
    </style>
</head>
<body>
    <h1>WiFi Configuration</h1>
    <label for="ssid">Select SSID:</label>
    <select id="ssid" required></select><br>
    
    <label for="password">Enter Password:</label>
    <input type="password" id="password" placeholder="Enter WiFi Password" required><br>
    
    <button id="submitBtn">开始配置</button>
    
    <p id="status"></p>

    <script>
        // 加载 WiFi 列表
        function loadWifiList() {
            fetch("/getWifiList")
                .then(response => response.json())
                .then(data => {
                    const ssidSelect = document.getElementById("ssid");
                    ssidSelect.innerHTML = ""; // 清空选择框
                    data.forEach(ssid => {
                        const option = document.createElement("option");
                        option.value = ssid;
                        option.textContent = ssid;
                        ssidSelect.appendChild(option);
                    });
                });
        }

        document.getElementById("submitBtn").addEventListener("click", function() {
            const ssid = document.getElementById("ssid").value;
            const password = document.getElementById("password").value;

            // 发送 POST 请求
            fetch("/setWiFiConfig", {
                method: "POST",
                headers: {
                    "Content-Type": "application/x-www-form-urlencoded",
                },
                body: `ssid=${encodeURIComponent(ssid)}&password=${encodeURIComponent(password)}`
            })
            .then(response => response.json())
            .then(data => {
                document.getElementById("status").innerText = data.message; // 显示状态信息
            })
            .catch(error => {
                document.getElementById("status").innerText = "Error: " + error;
            });
        });

        // 页面加载时加载 WiFi 列表
        window.onload = loadWifiList;
    </script>
</body>
</html>
)rawliteral";


// ------------------------------------------- 清除SPIFFS页面 -----------------------------------------------------------------------------------//
const char* htmlClearPage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Clear SPIFFS</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 50px;
        }
        button {
            font-size: 18px;
            padding: 10px 20px;
        }
        #status {
            margin-top: 20px;
            font-size: 16px;
            color: green;
        }
    </style>
</head>
<body>
    <h1>Clear SPIFFS</h1>
    <button id="clearBtn">Clear SPIFFS</button>
    <p id="status"></p>

    <script>
        document.getElementById("clearBtn").addEventListener("click", function() {
            // 发送请求到 /clearSPIFFS
            fetch("/clearSPIFFS", {
                method: "POST"
            })
            .then(response => response.json())  // 解析响应为 JSON
            .then(data => {
                // 根据响应结果更新页面状态
                document.getElementById("status").innerText = data.message;
            })
            .catch(error => {
                // 处理错误情况
                document.getElementById("status").innerText = "Error: " + error;
                document.getElementById("status").style.color = "red";
            });
        });
    </script>
</body>
</html>
)rawliteral";

// ---------------------------------------- 主页面------------------------------------------------------------------------//
const char* htmlHomePage = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>ESP32 Environment Moniter</title>
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

function fetchAllSensorData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var sensorData = JSON.parse(this.responseText);
        document.getElementById("sensorTemp").innerHTML = sensorData.temperature;
        document.getElementById("sensorHumi").innerHTML = sensorData.humidity;
        document.getElementById("sensorPressure").innerHTML = sensorData.pressure;
        document.getElementById("sensorAltitu").innerHTML = sensorData.altitude;
        document.getElementById("sensorLight").innerHTML = sensorData.light;
      }
    };
    xhttp.open("GET", "/getAllSensorData", true);
    xhttp.send();
}
setInterval(fetchAllSensorData, 1000);

</script>
</body>
</html>

)rawliteral";




