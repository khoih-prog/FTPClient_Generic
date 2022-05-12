/******************************************************************************
  FTPClient_DownloadFile_STM32_LAN8742A.ino

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

void initEthernet()
{ 
#if USE_ETHERNET_GENERIC
  Serial.println(ETHERNET_GENERIC_VERSION);
#endif
  
  Serial.println(ETHERNET_WEBSERVER_STM32_VERSION);

#if !(USE_BUILTIN_ETHERNET)
  #if (USING_SPI2)
    #if defined(CUR_PIN_MISO)
      ET_LOGWARN(F("Default SPI pinout:"));
      ET_LOGWARN1(F("MOSI:"), CUR_PIN_MOSI);
      ET_LOGWARN1(F("MISO:"), CUR_PIN_MISO);
      ET_LOGWARN1(F("SCK:"),  CUR_PIN_SCK);
      ET_LOGWARN1(F("SS:"),   CUR_PIN_SS);
      ET_LOGWARN(F("========================="));
    #endif
  #else
    ET_LOGWARN(F("Default SPI pinout:"));
    ET_LOGWARN1(F("MOSI:"), MOSI);
    ET_LOGWARN1(F("MISO:"), MISO);
    ET_LOGWARN1(F("SCK:"),  SCK);
    ET_LOGWARN1(F("SS:"),   SS);
    ET_LOGWARN(F("========================="));
  #endif
#endif

#if !(USE_BUILTIN_ETHERNET || USE_UIP_ETHERNET)
  // For other boards, to change if necessary
  #if ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
  Ethernet.init (USE_THIS_SS_PIN);

  #elif USE_CUSTOM_ETHERNET
  // You have to add initialization for your Custom Ethernet here
  // This is just an example to setCSPin to USE_THIS_SS_PIN, and can be not correct and enough
  //Ethernet.init(USE_THIS_SS_PIN);

  #endif  //( ( USE_ETHERNET_GENERIC || USE_ETHERNET_ENC )
#endif

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());
}

void setup()
{
  Serial.begin( 115200 );
  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting FTPClient_DownloadFile_STM32_LAN8742A on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(FTPCLIENT_GENERIC_VERSION);

  initEthernet();

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
