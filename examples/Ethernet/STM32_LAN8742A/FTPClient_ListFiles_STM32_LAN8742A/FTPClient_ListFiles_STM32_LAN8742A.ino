/******************************************************************************
  FTPClient_ListFiles_STM32_LAN8742A.ino

  FTP Client for Generic boards using SD, FS, etc.

  Based on and modified from

  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient

  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
******************************************************************************/

#include "Arduino.h"

#include "defines.h"

#include <FTPClient_Generic.h>

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

	Serial.print(F("\nStarting FTPClient_ListFiles_STM32_LAN8742A on "));
	Serial.print(BOARD_NAME);
	Serial.print(F(" with "));
	Serial.println(SHIELD_TYPE);
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
