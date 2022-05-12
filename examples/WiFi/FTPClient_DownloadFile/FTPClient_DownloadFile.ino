/******************************************************************************
  FTPClient_DownloadFile.ino

  FTP Client for Generic boards using SD, FS, etc.

  Based on and modified from

  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient

  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
******************************************************************************/

#include "Arduino.h"

#include "defines.h"

#include <FTPClient_Generic.h>

char ftp_server[] = "192.168.2.241";
char ftp_user[]   = "teensy4x";
char ftp_pass[]   = "ftp_test";

// FTPClient_Generic(char* _serverAdress, char* _userName, char* _passWord, uint16_t _timeout = 10000);
FTPClient_Generic ftp (ftp_server, ftp_user, ftp_pass, 60000);

char fileName[] = "helloworld.txt";

void setup()
{
  Serial.begin( 115200 );
  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting FTPClient_DownloadFile on ")); Serial.print(BOARD_NAME);
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

  //Change directory
  ftp.ChangeWorkDir("/");

  Serial.println("Creating new file helloworld.txt");

  // Create a new file to use as the download example below:
  ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  ftp.NewFile(fileName);
  ftp.Write("Hi, I'm a new file");
  ftp.CloseFile();

  //Download the text file or read it
  String response = "";
  ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  ftp.DownloadString("helloworld.txt", response);
  Serial.println("The file content is: " + response);

  // Get the file size
  size_t       fileSize = 0;
  String       list[128];

  // Get the directory content in order to allocate buffer
  // my server response => type=file;modify=20190101000010;size=18; helloworld.txt

  ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  ftp.ContentList("", list);

  for (uint16_t i = 0; i < sizeof(list); i++)
  {
    uint8_t indexSize = 0;

    if (list[i].length() > 0)
    {
      list[i].toLowerCase();

      if ( list[i].indexOf(fileName) > -1 )
      {
        indexSize = list[i].indexOf("size") + 5;

        fileSize = list[i].substring(indexSize, indexSize + 6).toInt();
      }

      // Print the directory details
      Serial.println(list[i]);
    }
    else
      break;
  }

  // Print file size
  Serial.println("\nFile size is: " + String(fileSize));

  //Dynammically alocate buffer
  unsigned char * downloaded_file = (unsigned char *) malloc(fileSize);

  // And download the file
  ftp.InitFile(COMMAND_XFER_TYPE_BINARY);
  ftp.DownloadFile(fileName, downloaded_file, fileSize, false);

  //Create a new Directory
  ftp.InitFile(COMMAND_XFER_TYPE_BINARY);
  ftp.MakeDir("myNewDir");

  //Enter the directory
  ftp.ChangeWorkDir("/myNewDir");

  //And upload the file to the new directory
  ftp.NewFile( fileName );
  ftp.WriteData(downloaded_file, fileSize);
  ftp.CloseFile();

  free(downloaded_file);

  Serial.println("CloseConnection");

  ftp.CloseConnection();
}

void loop()
{

}
