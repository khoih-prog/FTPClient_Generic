/******************************************************************************
  FTPClient_UploadImage.ino

  FTP Client for Generic boards using SD, FS, etc.
  
  Based on and modified from 
  
  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient
    
  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
******************************************************************************/

#include "Arduino.h"

#include "defines.h"

//#include <WiFi.h>
//#include <WiFiClient.h>

#include <FTPClient_Generic.h>
#include "octocat.h"

#define WIFI_SSID       "HueNet1"
#define WIFI_PASS       "jenniqqs"
//#define WIFI_SSID      ""
//#define WIFI_PASS      ""

char ftp_server[] = "192.168.2.241";
char ftp_user[]   = "teensy4x";
char ftp_pass[]   = "ftp_test";

// FTPClient_Generic(char* _serverAdress, char* _userName, char* _passWord, uint16_t _timeout = 10000, uint8_t _verbose = 1);
FTPClient_Generic ftp (ftp_server, ftp_user, ftp_pass, 60000);


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

  Serial.print(F("\nStarting FTPClient_UploadImage on ")); Serial.print(BOARD_NAME);
  Serial.print(F(" with ")); Serial.println(SHIELD_TYPE);
  Serial.println(FTPCLIENT_GENERIC_VERSION);

  initEthernet();

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

#if !(ESP8266)
  // Make a new directory
  //ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
  //ftp.MakeDir("myNewDir");

  // Create the new file and send the image
  //ftp.ChangeWorkDir("myNewDir");
  Serial.println("Writing octocat.jpg");
  
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
