#include <Wire.h>
#include <AHT20.h>
#include <Adafruit_BMP280.h>
#include <BH1750.h>
#include "sensorData.h"

AHT20 aht20;
Adafruit_BMP280 bmp280;
BH1750 bh1750; 

float sensorTemp;
float sensorHumi;
float sensorPressure;
float sensorAltitu;
float sensorLight;
void getAllSensorData(){
  Wire.begin();
  
  if(!aht20.begin()){
    Serial.println("Sensor AHT20 ERROR!");
    sensorTemp = 0.0;
    sensorHumi = 0.0;
  }
  if(!bmp280.begin()){
    Serial.println("Sensor bmp280 ERROR!");
    sensorPressure = 0.0;
    sensorAltitu = 0.0;
  }
  if(!bh1750.begin()){
    Serial.println("Sensor bh1750 ERROR!");
    sensorLight = 0.0;
  }
  sensorTemp = aht20.getTemperature();
  sensorHumi = aht20.getHumidity();
  bmp280.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
  sensorPressure = bmp280.readPressure();
  sensorAltitu = bmp280.readAltitude(1013.25);
  sensorLight = bh1750.readLightLevel();
}


