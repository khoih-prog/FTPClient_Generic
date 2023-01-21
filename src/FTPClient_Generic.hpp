/****************************************************************************************************************************
  FTPClient_Generic.h

  FTP Client for Generic boards using SD, FS, etc.
  
  Based on and modified from 
  
  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient
    
  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
  
  Version: 1.6.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      11/05/2022 Initial porting and coding to support many more boards, using WiFi or Ethernet
  1.1.0   K Hoang      13/05/2022 Add support to Teensy 4.1 using QNEthernet or NativeEthernet
  1.2.0   K Hoang      14/05/2022 Add support to other FTP Servers. Fix bug
  1.2.1   K Hoang      14/05/2022 Auto detect server response type in PASV mode
  1.3.0   K Hoang      16/05/2022 Fix uploading issue of large files for WiFi, QNEthernet
  1.4.0   K Hoang      05/11/2022 Add support to ESP32/ESP8266 using Ethernet W5x00 or ENC28J60
  1.5.0   K Hoang      20/01/2023 Add support to RP2040W using `arduino-pico` core
  1.5.0   K Hoang      20/01/2023 Add support to Ethernet W6100 using Ethernet_Generic library
 *****************************************************************************************************************************/

#pragma once

#ifndef FTPCLIENT_GENERIC_HPP
#define FTPCLIENT_GENERIC_HPP

#include "FTPClient_Generic_Debug.h"

/////////////////////////////////////////////

#define BUFFER_SIZE       1500

#define TIMEOUT_MS        10000UL

/////////////////////////////////////////////

#if FTP_CLIENT_USING_QNETHERNET

  #include <QNEthernetClient.h>
  #define theFTPClient    EthernetClient
  
#elif FTP_CLIENT_USING_NATIVE_ETHERNET

  #include <NativeEthernetClient.h>
  #define theFTPClient    EthernetClient  
  
#elif FTP_CLIENT_USING_ETHERNET

  #include <EthernetClient.h>
  #define theFTPClient    EthernetClient
  
#elif FTP_CLIENT_USING_WIFININA

  #include <WiFiClient_Generic.h>
  #define theFTPClient    WiFiClient
  
#else

  #include <WiFiClient.h>
  #define theFTPClient    WiFiClient
  
#endif

/////////////////////////////////////////////

#define FTP_PORT                        21

#define COMMAND_QUIT                    F("QUIT")
#define COMMAND_USER                    F("USER ")
#define COMMAND_PASS                    F("PASS ")

#define COMMAND_RENAME_FILE_FROM        F("RNFR ")
#define COMMAND_RENAME_FILE_TO          F("RNTO ")

#define COMMAND_FILE_LAST_MOD_TIME      F("MDTM ")

#define COMMAND_APPEND_FILE             F("APPE ")
#define COMMAND_DELETE_FILE             F("DELE ")

#define COMMAND_CURRENT_WORKING_DIR     F("CWD ")
#define COMMAND_MAKE_DIR                F("MKD ")
#define COMMAND_REMOVE_DIR              F("RMD ")
#define COMMAND_LIST_DIR_STANDARD       F("MLSD ")
#define COMMAND_LIST_DIR                F("LIST ")

#define COMMAND_DOWNLOAD                F("RETR ")
#define COMMAND_FILE_UPLOAD             F("STOR ")

#define COMMAND_PASSIVE_MODE            F("PASV")

#define COMMAND_XFER_TYPE_ASCII         ("Type A")
#define COMMAND_XFER_TYPE_BINARY        ("Type I")

/////////////////////////////////////////////

#define ENTERING_PASSIVE_MODE           227

/////////////////////////////////////////////

class FTPClient_Generic
{
  private:
  
    void WriteClientBuffered(theFTPClient* cli, unsigned char * data, int dataLength);
    
    theFTPClient  client;
    theFTPClient  dclient;
    
    char outBuf[128];
    unsigned char outCount;

    char*         userName;
    char*         passWord;
    char*         serverAdress;
    uint16_t      port;
    bool          _isConnected = false;
    unsigned char clientBuf[BUFFER_SIZE];
    size_t        bufferSize = BUFFER_SIZE;
    uint16_t      timeout = TIMEOUT_MS;
    
    theFTPClient* GetDataClient();

    // KH
    IPAddress     _dataAddress;
    uint16_t      _dataPort;
    
    bool          inASCIIMode = false;
    //////

  public:
  
    FTPClient_Generic(char* _serverAdress, uint16_t _port, char* _userName, char* _passWord, uint16_t _timeout = 10000);
    FTPClient_Generic(char* _serverAdress, char* _userName, char* _passWord, uint16_t _timeout = 10000);
    
    void OpenConnection();
    void CloseConnection();
    bool isConnected();
    void NewFile (const char* fileName);
    void AppendFile(const char* fileName);
    void WriteData (unsigned char * data, int dataLength);
    void CloseFile ();
    void GetFTPAnswer (char* result = NULL, int offsetStart = 0);
    void GetLastModifiedTime(const char* fileName, char* result);
    void RenameFile(const char* from, const char* to);
    void Write(const char * str);
    void InitFile(const char* type);
    void ChangeWorkDir(const char * dir);
    void DeleteFile(const char * file);
    void MakeDir(const char * dir);
    void RemoveDir(const char * dir);
    void ContentList(const char * dir, String * list);
    void ContentListWithListCommand(const char * dir, String * list);
    void DownloadString(const char * filename, String &str);
    void DownloadFile(const char * filename, unsigned char * buf, size_t length, bool printUART = false);
};

#endif  // FTPCLIENT_GENERIC_HPP
