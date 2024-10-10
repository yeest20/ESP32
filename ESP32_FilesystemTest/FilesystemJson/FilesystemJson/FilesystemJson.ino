#include <SPIFFS.h>
#include <ArduinoJson.h>

// -------------------------------------------------SPIFFS-----------------------------------------------------------------------------------------//
#define PATH "/WiFiCofig.json"
void filesystem_init(){
  if(!SPIFFS.begin(true)){
    Serial.println("[Filesystem] SPIFFS Mount Falied!");
    return;
  }
  Serial.println("[Filesystem] SPIFFS Mount Successful!");
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("[Filesystem] Writing.......\n");
  
  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("[ERROR] [Filesystem] Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("[Filesystem] File written Successful!");
  }else{
    Serial.println("[ERROR] Write Failed");
  }
  file.close();
}

void readFile(fs::FS &fs, const char * path, String &wifi){
  Serial.printf("[Filesystem] Reading %s.......\n", path);
  
  File file = fs.open(path, FILE_READ);
  if(!file){
    Serial.println("[ERROR] [Filesystem] Failed to open file for reading");
    return;
  }
  
  Serial.println("[Filesystem] Read from file :");
  while(file.available()){
    wifi += file.readString();
    //Serial.write(file.read());
  }
  Serial.printf("\n");
  file.close();
}

void removeFile(fs::FS &fs, const char * path){
  if(!fs.exists(path)){
    Serial.println("[ERROR] [Filesystem] File not exists!");
    return;
  }
  if(fs.remove(path)){
    Serial.printf("[FileSystem] %s removed\n", path);
  }else{
    Serial.println("[ERROR] [FileSystem] file removed Failed");
  }
}

//------------------------------------------------------设置---------------------------------------------------------------------------------------------------------//
void setup() {
  Serial.begin(115200);
  filesystem_init();

// ---------------SPIFFS---------------//
  //writeFile(SPIFFS, PATH, wifi);
//json串
  String wifi;
  readFile(SPIFFS, PATH, wifi);
  //removeFile(SPIFFS, PATH);
  //-----------------JSON-----------------//
//json文件
StaticJsonDocument<50> doc;
//解析
DeserializationError error = deserializeJson(doc, wifi);
if(error){
  Serial.println("[ERROR][JSON] deserializeJson Failed");
  Serial.println(error.f_str());
  return;
}
const char * SSID = doc["SSID"];
const char * PASSWD = doc["PASSWD"];
Serial.printf("SSID: %s\nPASSWD: %s\n", SSID, PASSWD);

}

void loop() {

}
