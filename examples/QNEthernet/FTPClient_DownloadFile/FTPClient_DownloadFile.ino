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


void initEthernet()
{ 
#if USE_NATIVE_ETHERNET
  ET_LOGWARN(F("======== USE_NATIVE_ETHERNET ========"));
#elif USE_QN_ETHERNET
  ET_LOGWARN(F("=========== USE_QN_ETHERNET ==========="));
#else
  ET_LOGWARN(F("========================="));
#endif

#if USE_NATIVE_ETHERNET

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  Serial.println(F("========================="));

  Serial.print(F("Using mac index = "));
  Serial.println(index);

  Serial.print(F("Connected! IP address: "));
  Serial.println(Ethernet.localIP());

#else

  #if USING_DHCP
    // Start the Ethernet connection, using DHCP
    Serial.print("Initialize Ethernet using DHCP => ");
    Ethernet.begin();
    // give the Ethernet shield minimum 1 sec for DHCP and 2 secs for staticP to initialize:
    delay(1000);
  #else   
    // Start the Ethernet connection, using static IP
    Serial.print("Initialize Ethernet using static IP => ");
    Ethernet.begin(myIP, myNetmask, myGW);
    Ethernet.setDNSServerIP(mydnsServer);
  #endif

  if (!Ethernet.waitForLocalIP(5000))
  {
    Serial.println("Failed to configure Ethernet");

    if (!Ethernet.linkStatus())
    {
      Serial.println("Ethernet cable is not connected.");
    }

    // Stay here forever
    while (true)
    {
      delay(1);
    }
  }
  else
  {
    Serial.print("IP Address = ");
    Serial.println(Ethernet.localIP());
  }

  // give the Ethernet shield minimum 1 sec for DHCP and 2 secs for staticP to initialize:
  delay(2000);

#endif
}

void setup()
{
  Serial.begin( 115200 );
  while (!Serial && millis() < 5000);

  delay(500);

  Serial.print(F("\nStarting FTPClient_DownloadFile on ")); Serial.print(BOARD_NAME);
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
