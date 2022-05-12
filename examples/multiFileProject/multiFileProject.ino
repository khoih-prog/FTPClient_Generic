/****************************************************************************************************************************
  multiFileProject.ino
  FTP Client for Generic boards using SD, FS, etc.

  Based on and modified from

  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient

  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#define FTPCLIENT_GENERIC_VERSION_MIN_TARGET      "EthernetWebServer v1.0.0"
#define FTPCLIENT_GENERIC_VERSION_MIN             1000000

#include "multiFileProject.h"

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include <FTPClient_Generic.h>      // https://github.com/khoih-prog/FTPClient_Generic

void setup() 
{
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  delay(500);
  
  Serial.println("\nStart multiFileProject");
  Serial.println(FTPCLIENT_GENERIC_VERSION);

#if defined(FTPCLIENT_GENERIC_VERSION_MIN)
  if (FTPCLIENT_GENERIC_VERSION_INT < FTPCLIENT_GENERIC_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(FTPCLIENT_GENERIC_VERSION_MIN_TARGET);
  }
#endif

  Serial.print("You're OK now");
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
