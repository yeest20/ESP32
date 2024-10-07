#include<AHT20.h>
#include<Adafruit_BMP280.h>
#include<Wire.h> // pin脚功能
AHT20 aht20;
Adafruit_BMP280 bmp;
#define IIC_SDA 4
#define IIC_SCL 15 

void setup() {
  // put your setup code here, to run once:
  // 开机设置
  Serial.begin(115200);
  Wire.begin();
  pinMode(2,OUTPUT);
  if(!aht20.begin()){
    Serial.println("Couldn't open aht20 sensor!.......");
    while(1);
  }

  if(!bmp.begin()){
    Serial.println(("Couldn't open bmp280 sensor!......"));
    while(1);
  }
  delay(1000);

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  float temp = aht20.getTemperature();
  float humi = aht20.getHumidity();
  float temp2 = bmp.readTemperature();
  float press = bmp.readPressure();
  float altitude = bmp.readAltitude(1013.25);
  Serial.print("Temp-aht:");
  Serial.println(temp);
  Serial.print("Humi:");
  Serial.println(humi);
  Serial.print("Temp-bmp:");
  Serial.println(temp2);
  Serial.print("Press:");
  Serial.println(press);
  Serial.print("Altitude:");
  Serial.println(altitude);
  delay(500);
  digitalWrite(2, LOW);
  delay(1000);
  
}
