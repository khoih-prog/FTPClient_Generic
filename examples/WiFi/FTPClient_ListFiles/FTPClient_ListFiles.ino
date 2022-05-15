/******************************************************************************
  FTPClient_DownloadFile.ino

  FTP Client for Generic boards using SD, FS, etc.

  Based on and modified from

  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient

  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
******************************************************************************/

#include "Arduino.h"

#include "defines.h"

// To use `true` with the following PASV mode asnswer from server
// 227 Entering Passive Mode (192,168,2,112,157,218)
// Using `false` with old style PASV answer, such as `FTP_Server_Teensy41` library
#define USING_NEW_PASSIVE_MODE_ANSWER_TYPE      true

#include <FTPClient_Generic.h>

// Change according to your FTP server
char ftp_server[] = "192.168.2.112";

char ftp_user[]   = "ftp_test";
char ftp_pass[]   = "ftp_test";

// FTPClient_Generic(char* _serverAdress, char* _userName, char* _passWord, uint16_t _timeout = 10000);
FTPClient_Generic ftp (ftp_server, ftp_user, ftp_pass, 60000);

char dirName[]    = "/home/ftp_test";
char newDirName[] = "/home/ftp_test/NewDir";


void setup()
{
  Serial.begin( 115200 );
  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting FTPClient_ListFiles on ")); Serial.print(BOARD_NAME);
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

  //Create a new Directory
  ftp.InitFile(COMMAND_XFER_TYPE_BINARY);
  ftp.RemoveDir(newDirName);
  ftp.MakeDir(newDirName);

  //Enter the directory
  ftp.ChangeWorkDir(newDirName);

  Serial.println("CloseConnection");

  ftp.CloseConnection();
}

void loop()
{
}
