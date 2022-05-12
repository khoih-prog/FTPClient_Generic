/******************************************************************************
  FTPClient_UploadImage.ino

  FTP Client for Generic boards using SD, FS, etc.
  
  Based on and modified from 
  
  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient
    
  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
******************************************************************************/

#include "Arduino.h"

#include "defines.h"

#include <FTPClient_Generic.h>
#include "octocat.h"

char ftp_server[] = "192.168.2.241";
char ftp_user[]   = "teensy4x";
char ftp_pass[]   = "ftp_test";

// FTPClient_Generic(char* _serverAdress, char* _userName, char* _passWord, uint16_t _timeout = 10000, uint8_t _verbose = 1);
FTPClient_Generic ftp (ftp_server, ftp_user, ftp_pass, 60000);

void setup()
{
  Serial.begin( 115200 );
  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting FTPClient_UploadImage on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(FTPCLIENT_GENERIC_VERSION);

  WiFi.begin( WIFI_SSID, WIFI_PASS );

  Serial.println("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());

#if (ESP32)
  Serial.print("Max Free Heap: "); Serial.println(ESP.getMaxAllocHeap());
#endif  

  ftp.OpenConnection();

  // Get directory content
  ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  String list[128];

  ftp.ChangeWorkDir("/");

  ftp.ContentList("", list);
  Serial.println("\nDirectory info: ");

  for (uint16_t i = 0; i < sizeof(list); i++)
  {
    if (list[i].length() > 0)
      Serial.println(list[i]);
    else
      break;
  }

#if !(ESP8266  || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(__SAMD21E18A__) || defined(__SAMD21G18A__))
  // Make a new directory
  //ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  //ftp.MakeDir("myNewDir");

  // Create the new file and send the image
  //ftp.ChangeWorkDir("myNewDir");
  ftp.InitFile(COMMAND_XFER_TYPE_BINARY);
  ftp.NewFile("octocat.jpg");
  ftp.WriteData( octocat_pic, sizeof(octocat_pic) );
  ftp.CloseFile();

  // Create the file new and write a string into it
  ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  ftp.NewFile("hello_world.txt");
  ftp.Write("Hello World");
  ftp.CloseFile();
#endif

  ftp.CloseConnection();
}

void loop()
{

}
