#include <SPIFFS.h>


// -------------------------------------------------SPIFFS-----------------------------------------------------------------------------------------//
#define PATH "/test.txt"
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

void readFile(fs::FS &fs, const char * path){
  Serial.printf("[Filesystem] Reading %s.......\n", path);
  
  File file = fs.open(path, FILE_READ);
  if(!file){
    Serial.println("[ERROR] [Filesystem] Failed to open file for reading");
    return;
  }
  
  Serial.println("[Filesystem] Read from file :");
  while(file.available()){
    Serial.write(file.read());
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

  writeFile(SPIFFS, PATH, "Test, SPIFFS");
  readFile(SPIFFS, PATH);
  removeFile(SPIFFS, PATH);
}


void loop() {

}
