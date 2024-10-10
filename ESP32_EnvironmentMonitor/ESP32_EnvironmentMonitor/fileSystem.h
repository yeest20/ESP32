#ifndef _FILESYSTEM
#define _FILESYSTEM

// ------------------------------------------ File -----------------------------------------------------//

void fileSystem_init();
bool fileSystem_writeWiFiConfig(String&);
bool fileSystem_readWiFiConfig(String&);
bool clearSPIFFS();


#endif