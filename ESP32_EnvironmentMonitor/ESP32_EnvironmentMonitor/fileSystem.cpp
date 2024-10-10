#include "FS.h"
#include <SPIFFS.h>
#include "fileSystem.h"

#define PATH "/WiFiCofig.json"

void fileSystem_init(){
  if(!SPIFFS.begin(true)){
    Serial.println("[ERROR] [Filesystem] SPIFFS Mount Failure!");
    return;
  }
    Serial.println("[Filesystem] SPIFFS Mount Successful!");
    Serial.printf("[Filesystem] TotalBytes : %lu Bytes\n", SPIFFS.totalBytes());
    Serial.printf("[Filesystem] FreeBytes : %lu Bytes\n", SPIFFS.totalBytes() - SPIFFS.usedBytes());
}

bool fileSystem_writeWiFiConfig(String& WiFiConfig){
  File file = SPIFFS.open(PATH, FILE_WRITE);
  if(!file){
    Serial.printf("[ERROR] [FileSystem] Open %s for Writing Failed!\n", PATH);
    return false;
  }
  file.print(WiFiConfig);
  file.close();
  return true;
}

bool fileSystem_readWiFiConfig(String &WifiConfig){
  if(!SPIFFS.exists(PATH)) return false;
  File file = SPIFFS.open(PATH, FILE_READ);
  Serial.printf("File size : %lu bytes\n", file.size());
  if(!file.available()){
    Serial.printf("[ERROR] [Filesystem] Open %s For Reading Failed!\n", PATH);
    return false;
  }

  WifiConfig = "";
  WifiConfig += file.readString();
  file.close();
  return true;
}

bool clearSPIFFS(){
  SPIFFS.format();
  return true;
}