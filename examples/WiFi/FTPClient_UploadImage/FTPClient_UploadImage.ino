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

// To use `true` with the following PASV mode asnswer from server, such as `VSFTP`
// 227 Entering Passive Mode (192,168,2,112,157,218)
// Using `false` with old style PASV answer, such as `FTP_Server_Teensy41` library
// 227 Entering Passive Mode (4043483328, port 55600)
#define USING_VSFTP_SERVER      true

#if USING_VSFTP_SERVER

  // Change according to your FTP server
  char ftp_server[] = "192.168.2.112";
  
  char ftp_user[]   = "ftp_test";
  char ftp_pass[]   = "ftp_test";

  char dirName[]    = "/home/ftp_test";
  char newDirName[] = "/home/ftp_test/NewDir";

#else

  // Change according to your FTP server
  char ftp_server[] = "192.168.2.241";
  
  char ftp_user[]   = "teensy4x";
  char ftp_pass[]   = "ftp_test";

  char dirName[]    = "/";
  char newDirName[] = "/NewDir";

#endif

// FTPClient_Generic(char* _serverAdress, char* _userName, char* _passWord, uint16_t _timeout = 10000);
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

  Serial.print("Connecting WiFi, SSID = "); Serial.println(WIFI_SSID);

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

  //Change directory
  ftp.ChangeWorkDir(dirName);

  // Get the file size
  String       list[128];

  // Get the directory content in order to allocate buffer
  // my server response => type=file;modify=20190101000010;size=18; helloworld.txt

  ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  
  ftp.ContentListWithListCommand("", list);

  for (uint16_t i = 0; i < sizeof(list); i++)
  {
    if (list[i].length() > 0)
      Serial.println(list[i]);
    else
      break;
  }

#if !(ESP8266)
  // Make a new directory
  //ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  //ftp.MakeDir("myNewDir");

  // Create the new file and send the image
  //ftp.ChangeWorkDir("myNewDir");
  Serial.print("Writing octocat.jpg, size = "); Serial.println(sizeof(octocat_pic));
  
  ftp.InitFile(COMMAND_XFER_TYPE_BINARY);
  ftp.NewFile("octocat.jpg");
  ftp.WriteData( octocat_pic, sizeof(octocat_pic) );
  ftp.CloseFile();

  // Create the file new and write a string into it
  Serial.println("Writing hello_world.txt");
  
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
