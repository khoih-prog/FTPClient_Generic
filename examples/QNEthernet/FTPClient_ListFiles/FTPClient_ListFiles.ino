/******************************************************************************
  FTPClient_ListFiles.ino

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

void initEthernet()
{ 
#if USE_NATIVE_ETHERNET
  ET_LOGWARN(F("========= USE_NATIVE_ETHERNET ========="));
#elif USE_QN_ETHERNET
  ET_LOGWARN(F("=========== USE_QN_ETHERNET ==========="));
#else
  ET_LOGWARN(F("======================================="));
#endif

#if USE_NATIVE_ETHERNET

  // start the ethernet connection and the server:
  // Use DHCP dynamic IP and random mac
  uint16_t index = millis() % NUMBER_OF_MAC;
  // Use Static IP
  //Ethernet.begin(mac[index], ip);
  Ethernet.begin(mac[index]);

  ET_LOGWARN(F("======================================="));

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

  Serial.print(F("\nStarting FTPClient_ListFiles on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(FTPCLIENT_GENERIC_VERSION);

  initEthernet();

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
