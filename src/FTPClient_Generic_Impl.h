/****************************************************************************************************************************
  FTPClient_Generic_Impl.h

  FTP Client for Generic boards using SD, FS, etc.

  Based on and modified from

  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient

  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic

  Version: 1.4.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      11/05/2022 Initial porting and coding to support many more boards, using WiFi or Ethernet
  1.1.0   K Hoang      13/05/2022 Add support to Teensy 4.1 using QNEthernet or NativeEthernet
  1.2.0   K Hoang      14/05/2022 Add support to other FTP Servers. Fix bug
  1.2.1   K Hoang      14/05/2022 Auto detect server response type in PASV mode
  1.3.0   K Hoang      16/05/2022 Fix uploading issue of large files for WiFi, QNEthernet
  1.4.0   K Hoang      05/11/2022 Add support to ESP32/ESP8266 using Ethernet W5x00 or ENC28J60
 *****************************************************************************************************************************/

#pragma once

#ifndef FTPCLIENT_GENERIC_IMPL_H
#define FTPCLIENT_GENERIC_IMPL_H

#include "FTPClient_Generic.hpp"

#if !defined(USING_NEW_PASSIVE_MODE_ANSWER_TYPE)
  #define USING_NEW_PASSIVE_MODE_ANSWER_TYPE    true
#endif

/////////////////////////////////////////////

FTPClient_Generic::FTPClient_Generic(char* _serverAdress, uint16_t _port, char* _userName, char* _passWord,
                                     uint16_t _timeout)
{
  userName      = _userName;
  passWord      = _passWord;
  serverAdress  = _serverAdress;
  port          = _port;
  timeout       = _timeout;
}

/////////////////////////////////////////////

FTPClient_Generic::FTPClient_Generic(char* _serverAdress, char* _userName, char* _passWord, uint16_t _timeout)
{
  userName      = _userName;
  passWord      = _passWord;
  serverAdress  = _serverAdress;
  port          = FTP_PORT;
  timeout       = _timeout;
}

/////////////////////////////////////////////

theFTPClient* FTPClient_Generic::GetDataClient()
{
  return &dclient;
}

/////////////////////////////////////////////

bool FTPClient_Generic::isConnected()
{
  if (!_isConnected)
  {
    FTP_LOGWARN1("FTP error: ", outBuf);
  }

  return _isConnected;
}

/////////////////////////////////////////////

void FTPClient_Generic::GetLastModifiedTime(const char  * fileName, char* result)
{
  FTP_LOGINFO("Send MDTM");

  if (!isConnected())
  {
    FTP_LOGERROR("GetLastModifiedTime: Not connected error");
    return;
  }

  client.print(COMMAND_FILE_LAST_MOD_TIME);
  client.println(fileName);
  GetFTPAnswer (result, 4);
}

/////////////////////////////////////////////

void FTPClient_Generic::WriteClientBuffered(theFTPClient* cli, unsigned char * data, int dataLength)
{
  if (!isConnected())
    return;

  size_t clientCount = 0;

  for (int i = 0; i < dataLength; i++)
  {
    clientBuf[clientCount] = data[i];
    clientCount++;

    if (clientCount > bufferSize - 1)
    {
#if FTP_CLIENT_USING_QNETHERNET
      cli->writeFully(clientBuf, bufferSize);
#else
      cli->write(clientBuf, bufferSize);
#endif

      FTP_LOGDEBUG3("Written: num bytes = ", bufferSize, ", index = ", i);
      FTP_LOGDEBUG3("Written: clientBuf = ", (uint32_t) clientBuf, ", clientCount = ", clientCount);

      clientCount = 0;
    }
  }

  if (clientCount > 0)
  {
    cli->write(clientBuf, clientCount);

    FTP_LOGDEBUG1("Last Written: num bytes = ", clientCount);
  }
}

/////////////////////////////////////////////

void FTPClient_Generic::GetFTPAnswer (char* result, int offsetStart)
{
  char thisByte;
  outCount = 0;

  unsigned long _m = millis();

  while (!client.available() && millis() < _m + timeout)
    delay(100);

  if ( !client.available())
  {
    memset( outBuf, 0, sizeof(outBuf) );
    strcpy( outBuf, "Offline");

    _isConnected = false;
    isConnected();

    return;
  }

  while (client.available())
  {
    thisByte = client.read();

    if (outCount < sizeof(outBuf))
    {
      outBuf[outCount] = thisByte;
      outCount++;
      outBuf[outCount] = 0;
    }
  }

  if (outBuf[0] == '4' || outBuf[0] == '5' )
  {
    _isConnected = false;
    isConnected();

    return;
  }
  else
  {
    _isConnected = true;
  }

  if (result != NULL)
  {
    // Deprecated
    for (uint32_t i = offsetStart; i < sizeof(outBuf); i++)
    {
      result[i] = outBuf[i - offsetStart];
    }

    FTP_LOGDEBUG1("Result: ", outBuf);
  }
}

/////////////////////////////////////////////

void FTPClient_Generic::WriteData (unsigned char * data, int dataLength)
{
  FTP_LOGDEBUG(F("Writing"));

  if (!isConnected())
  {
    FTP_LOGERROR("WriteData: Not connected error");
    return;
  }

  FTP_LOGDEBUG1("WriteData: datalen = ", dataLength);

  WriteClientBuffered(&dclient, &data[0], dataLength);
}

/////////////////////////////////////////////

void FTPClient_Generic::CloseFile ()
{
  FTP_LOGDEBUG(F("Close File"));
  dclient.stop();

  if (!isConnected())
  {
    FTP_LOGERROR("CloseFile: Not connected error");
    return;
  }

  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::Write(const char * str)
{
  FTP_LOGDEBUG(F("Write File"));

  if (!isConnected())
  {
    FTP_LOGERROR("Write: Not connected error");
    return;
  }

  GetDataClient()->print(str);
}

/////////////////////////////////////////////

void FTPClient_Generic::CloseConnection()
{
  client.println(COMMAND_QUIT);
  client.stop();
  FTP_LOGINFO(F("Connection closed"));
}

/////////////////////////////////////////////

void FTPClient_Generic::OpenConnection()
{
  FTP_LOGINFO1(F("Connecting to: "), serverAdress);

#if ( (ESP32) && !FTP_CLIENT_USING_ETHERNET )

  if ( client.connect(serverAdress, port, timeout) )
#else
  if ( client.connect(serverAdress, port) )
#endif
  {
    FTP_LOGINFO(F("Command connected"));
  }

  GetFTPAnswer();

  FTP_LOGINFO1("Send USER = ", userName);

  client.print(COMMAND_USER);
  client.println(userName);

  GetFTPAnswer();

  FTP_LOGINFO1("Send PASSWORD = ", passWord);

  client.print(COMMAND_PASS);
  client.println(passWord);

  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::RenameFile(char* from, char* to)
{
  FTP_LOGINFO("Send RNFR");

  if (!isConnected())
  {
    FTP_LOGERROR("RenameFile: Not connected error");
    return;
  }

  client.print(COMMAND_RENAME_FILE_FROM);
  client.println(from);

  GetFTPAnswer();

  FTP_LOGINFO("Send RNTO");

  client.print(COMMAND_RENAME_FILE_TO);
  client.println(to);

  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::NewFile (const char* fileName)
{
  FTP_LOGINFO("Send STOR");

  if (!isConnected())
  {
    FTP_LOGERROR("NewFile: Not connected error");
    return;
  }

  client.print(COMMAND_FILE_UPLOAD);
  client.println(fileName);

  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::InitFile(const char* type)
{
  FTP_LOGINFO1("Send TYPE", type);

  if (!isConnected())
  {
    FTP_LOGERROR("InitFile: Not connected error");
    return;
  }

  FTP_LOGINFO("Send PASV");

  client.println(COMMAND_PASSIVE_MODE);
  GetFTPAnswer();

  // KH
  FTP_LOGDEBUG1("outBuf =", outBuf);

  char *tmpPtr;
  //FTP_LOGDEBUG1("outBuf =", strtol(outBuf, &tmpPtr, 10 ));

  while (strtol(outBuf, &tmpPtr, 10 ) != ENTERING_PASSIVE_MODE)
  {
    client.println(COMMAND_PASSIVE_MODE);
    GetFTPAnswer();
    FTP_LOGDEBUG1("outBuf =", outBuf);
    delay(1000);
  }

  // Test to know which format
  // 227 Entering Passive Mode (192,168,2,112,157,218)
  // 227 Entering Passive Mode (4043483328, port 55600)
  char *passiveIP = strchr(outBuf, '(') + 1;
  //FTP_LOGDEBUG1("passiveIP =", atoi(passiveIP));

  if (atoi(passiveIP) <= 0xFF)
  {
    char *tStr = strtok(outBuf, "(,");
    int array_pasv[6];

    for ( int i = 0; i < 6; i++)
    {
      tStr = strtok(NULL, "(,");

      //FTP_LOGDEBUG1("tStr =", tStr);

      if (tStr == NULL)
      {
        FTP_LOGDEBUG(F("Bad PASV Answer"));

        CloseConnection();
        return;
      }

      array_pasv[i] = atoi(tStr);
    }

    unsigned int hiPort, loPort;
    hiPort = array_pasv[4] << 8;
    loPort = array_pasv[5] & 255;

    _dataAddress = IPAddress(array_pasv[0], array_pasv[1], array_pasv[2], array_pasv[3]);

    _dataPort = hiPort | loPort;

    FTP_LOGDEBUG1(F("Data port: "), _dataPort);
  }
  else
  {
    // Using with old style PASV answer, such as `FTP_Server_Teensy41` library

    //char *subStr = strchr(outBuf, '(') + 1;
    char *ptr = strtok(passiveIP, ",");
    uint32_t ret = strtoul( ptr, &tmpPtr, 10 );

    // get IP of data client
    _dataAddress = IPAddress(ret);

    passiveIP = strchr(outBuf, ')');
    ptr = strtok(passiveIP, "port ");

    _dataPort = strtol( ptr, &tmpPtr, 10 );
  }

  FTP_LOGINFO3(F("_dataAddress: "), _dataAddress, F(", Data port: "), _dataPort);

#if ( (ESP32) && !FTP_CLIENT_USING_ETHERNET )

  if (dclient.connect(_dataAddress, _dataPort, timeout))
#else
  if (dclient.connect(_dataAddress, _dataPort))
#endif
  {
    FTP_LOGDEBUG(F("Data connection established"));
  }

  client.println(type);
  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::AppendFile (char* fileName)
{
  FTP_LOGINFO("Send APPE");

  if (!isConnected())
  {
    FTP_LOGERROR("AppendFile: Not connected error");
    return;
  }

  client.print(COMMAND_APPEND_FILE);
  client.println(fileName);
  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::ChangeWorkDir(const char * dir)
{
  FTP_LOGINFO("Send CWD");

  if (!isConnected())
  {
    FTP_LOGERROR("ChangeWorkDir: Not connected error");
    return;
  }

  client.print(COMMAND_CURRENT_WORKING_DIR);
  client.println(dir);
  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::DeleteFile(const char * file)
{
  FTP_LOGINFO("Send DELE");

  if (!isConnected())
  {
    FTP_LOGERROR("DeleteFile: Not connected error");
    return;
  }

  client.print(COMMAND_DELETE_FILE);
  client.println(file);
  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::MakeDir(const char * dir)
{
  FTP_LOGINFO("Send MKD");

  if (!isConnected())
  {
    FTP_LOGERROR("MakeDir: Not connected error");
    return;
  }

  client.print(COMMAND_MAKE_DIR);
  client.println(dir);

  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::RemoveDir(const char * dir)
{
  FTP_LOGINFO("Send RMD");

  if (!isConnected())
  {
    FTP_LOGERROR("RemoveDir: Not connected error");
    return;
  }

  client.print(COMMAND_REMOVE_DIR);
  client.println(dir);

  GetFTPAnswer();
}

/////////////////////////////////////////////

void FTPClient_Generic::ContentList(const char * dir, String * list)
{
  char _resp[ sizeof(outBuf) ];
  uint16_t _b = 0;

  FTP_LOGINFO("Send MLSD");

  if (!isConnected())
  {
    FTP_LOGERROR("ContentList: Not connected error");
    return;
  }

  client.print(COMMAND_LIST_DIR_STANDARD);
  client.println(dir);
  GetFTPAnswer(_resp);

  // Convert char array to string to manipulate and find response size
  // each server reports it differently, TODO = FEAT
  //String resp_string = _resp;
  //resp_string.substring(resp_string.lastIndexOf('matches')-9);
  //FTP_LOGDEBUG(resp_string);

  unsigned long _m = millis();

  while ( !dclient.available() && millis() < _m + timeout)
    delay(1);

  while (dclient.available())
  {
    if ( _b < 128 )
    {
      list[_b] = dclient.readStringUntil('\n');
      //FTP_LOGDEBUG(String(_b) + ":" + list[_b]);
      _b++;
    }
  }
}

/////////////////////////////////////////////

void FTPClient_Generic::ContentListWithListCommand(const char * dir, String * list)
{
  char _resp[ sizeof(outBuf) ];
  uint16_t _b = 0;

  FTP_LOGINFO("Send LIST");

  if (!isConnected())
  {
    FTP_LOGERROR("ContentListWithListCommand: Not connected error");
    return;
  }

  client.print(COMMAND_LIST_DIR);
  client.println(dir);

  GetFTPAnswer(_resp);

  // Convert char array to string to manipulate and find response size
  // each server reports it differently, TODO = FEAT
  //String resp_string = _resp;
  //resp_string.substring(resp_string.lastIndexOf('matches')-9);
  //FTP_LOGDEBUG(resp_string);

  unsigned long _m = millis();

  while ( !dclient.available() && millis() < _m + timeout)
    delay(1);

  while (dclient.available())
  {
    if ( _b < 128 )
    {
      String tmp = dclient.readStringUntil('\n');
      list[_b] = tmp.substring(tmp.lastIndexOf(" ") + 1, tmp.length());

      //FTP_LOGDEBUG(String(_b) + ":" + tmp);

      _b++;
    }
  }
}

/////////////////////////////////////////////

void FTPClient_Generic::DownloadString(const char * filename, String &str)
{
  FTP_LOGINFO("Send RETR");

  if (!isConnected())
    return;

  client.print(COMMAND_DOWNLOAD);
  client.println(filename);

  char _resp[ sizeof(outBuf) ];
  GetFTPAnswer(_resp);

  unsigned long _m = millis();

  while ( !GetDataClient()->available() && millis() < _m + timeout)
    delay(1);

  while ( GetDataClient()->available() )
  {
    str += GetDataClient()->readString();
  }
}

/////////////////////////////////////////////

void FTPClient_Generic::DownloadFile(const char * filename, unsigned char * buf, size_t length, bool printUART )
{
  FTP_LOGINFO("Send RETR");

  if (!isConnected())
  {
    FTP_LOGERROR("DownloadFile: Not connected error");
    return;
  }

  client.print(COMMAND_DOWNLOAD);
  client.println(filename);

  char _resp[ sizeof(outBuf) ];
  GetFTPAnswer(_resp);

  char _buf[2];

  unsigned long _m = millis();

  while ( !dclient.available() && millis() < _m + timeout)
    delay(1);

  while (dclient.available())
  {
    if ( !printUART )
      dclient.readBytes(buf, length);
    else
    {
      for (size_t _b = 0; _b < length; _b++ )
      {
        dclient.readBytes(_buf, 1);
        //FTP_LOGDEBUG0(_buf[0]);
      }
    }
  }
}

/////////////////////////////////////////////

#endif    // FTPCLIENT_GENERIC_IMPL_H
