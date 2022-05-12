/****************************************************************************************************************************
  FTPClient_Generic_Impl.h

  FTP Client for Generic boards using SD, FS, etc.
  
  Based on and modified from 
  
  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient
    
  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
  
  Version: 1.0.0
    
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      31/03/2022 Initial porting and coding to support many more boards, using WiFi or Ethernet
 *****************************************************************************************************************************/

#pragma once

#ifndef FTPCLIENT_GENERIC_IMPL_H
#define FTPCLIENT_GENERIC_IMPL_H

#include "FTPClient_Generic.hpp"

FTPClient_Generic::FTPClient_Generic(char* _serverAdress, uint16_t _port, char* _userName, char* _passWord, uint16_t _timeout)
{
  userName 			= _userName;
  passWord 			= _passWord;
  serverAdress 	= _serverAdress;
  port 					= _port;
  timeout 			= _timeout;
}

FTPClient_Generic::FTPClient_Generic(char* _serverAdress, char* _userName, char* _passWord, uint16_t _timeout)
{
  userName 			= _userName;
  passWord 			= _passWord;
  serverAdress 	= _serverAdress;
  port 					= FTP_PORT;
  timeout 			= _timeout;
}

theFTPClient* FTPClient_Generic::GetDataClient()
{
  return &dclient;
}

bool FTPClient_Generic::isConnected()
{
  if (!_isConnected)
  {
    FTP_LOGWARN1("FTP error: ", outBuf);
  }

  return _isConnected;
}

void FTPClient_Generic::GetLastModifiedTime(const char  * fileName, char* result)
{
  FTP_LOGINFO("Send MDTM");

  if (!isConnected())
    return;

  client.print(COMMAND_FILE_LAST_MOD_TIME);
  client.println(fileName);
  GetFTPAnswer (result, 4);
}

void FTPClient_Generic::WriteClientBuffered(theFTPClient* cli, unsigned char * data, int dataLength)
{
  if (!isConnected())
    return;

  size_t clientCount = 0;

  for (int i = 0; i < dataLength; i++)
  {
    clientBuf[clientCount] = data[i];
    //client.write(data[i])
    clientCount++;

    if (clientCount > bufferSize - 1)
    {
      cli->write(clientBuf, bufferSize);
      clientCount = 0;
    }
  }

  if (clientCount > 0)
  {
    cli->write(clientBuf, clientCount);
  }
}

void FTPClient_Generic::GetFTPAnswer (char* result, int offsetStart)
{
  char thisByte;
  outCount = 0;

  unsigned long _m = millis();
  while (!client.available() && millis() < _m + timeout) delay(1);

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
    FTP_LOGDEBUG("Result start");

    // Deprecated
    for (uint32_t i = offsetStart; i < sizeof(outBuf); i++)
    {
      result[i] = outBuf[i - offsetStart];
    }

    FTP_LOGDEBUG1("Result: ", outBuf);
    FTP_LOGDEBUG("Result end");
  }
}

void FTPClient_Generic::WriteData (unsigned char * data, int dataLength)
{
  FTP_LOGDEBUG(F("Writing"));

  if (!isConnected())
    return;

  WriteClientBuffered(&dclient, &data[0], dataLength);
}

void FTPClient_Generic::CloseFile ()
{
  FTP_LOGDEBUG(F("Close File"));
  dclient.stop();

  if (!_isConnected)
    return;

  GetFTPAnswer();
}

void FTPClient_Generic::Write(const char * str)
{
  FTP_LOGDEBUG(F("Write File"));

  if (!isConnected())
    return;

  GetDataClient()->print(str);
}

void FTPClient_Generic::CloseConnection()
{
  client.println(COMMAND_QUIT);
  client.stop();
  FTP_LOGINFO(F("Connection closed"));
}

void FTPClient_Generic::OpenConnection()
{
  FTP_LOGINFO1(F("Connecting to: "), serverAdress);

#if (ESP32)
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

void FTPClient_Generic::RenameFile(char* from, char* to)
{
  FTP_LOGINFO("Send RNFR");

  if (!isConnected())
    return;

  client.print(COMMAND_RENAME_FILE_FROM);
  client.println(from);
  
  GetFTPAnswer();

  FTP_LOGINFO("Send RNTO");
  
  client.print(F("RNTO "));
  client.println(to);
  
  GetFTPAnswer();
}

void FTPClient_Generic::NewFile (const char* fileName)
{
  FTP_LOGINFO("Send STOR");

  if (!isConnected())
    return;

  client.print(COMMAND_FILE_UPLOAD);
  client.println(fileName);
  
  GetFTPAnswer();
}

void FTPClient_Generic::InitFile(const char* type)
{
  FTP_LOGINFO1("Send TYPE", type);

  if (!isConnected())
    return;

  client.println(type);
  GetFTPAnswer();

  FTP_LOGINFO("Send PASV");
  
  client.println(COMMAND_PASSIVE_MODE);
  GetFTPAnswer();

  // KH
  FTP_LOGDEBUG1("outBuf =", outBuf);
  //

  char *subStr = strchr(outBuf, '(') + 1;
  char *ptr = strtok(subStr, ",");
  char *tmpPtr;
  uint32_t ret = strtoul( ptr, &tmpPtr, 10 );

  // get IP of data client
  _dataAddress = IPAddress(ret);

  subStr = strchr(outBuf, ')');
  ptr = strtok(subStr, "port ");

  _dataPort = strtol( ptr, &tmpPtr, 10 );

  FTP_LOGINFO3(F("_dataAddress: "), _dataAddress, F(", Data port: "), _dataPort);

#if (ESP32)
  if (dclient.connect(_dataAddress, _dataPort, timeout))
#else
  if (dclient.connect(_dataAddress, _dataPort))
#endif
  {
    FTP_LOGDEBUG(F("Data connection established"));
  }
}

void FTPClient_Generic::AppendFile (char* fileName)
{
  FTP_LOGINFO("Send APPE");

  if (!isConnected())
    return;

  client.print(COMMAND_APPEND_FILE);
  client.println(fileName);
  GetFTPAnswer();
}

void FTPClient_Generic::ChangeWorkDir(const char * dir)
{
  FTP_LOGINFO("Send CWD");

  if (!isConnected())
    return;

  client.print(COMMAND_CURRENT_WORKING_DIR);
  client.println(dir);
  GetFTPAnswer();
}

void FTPClient_Generic::DeleteFile(const char * file)
{
  FTP_LOGINFO("Send DELE");

  if (!isConnected())
    return;

  client.print(COMMAND_DELETE_FILE);
  client.println(file);
  GetFTPAnswer();
}

void FTPClient_Generic::MakeDir(const char * dir)
{
  FTP_LOGINFO("Send MKD");

  if (!isConnected())
    return;

  client.print(COMMAND_MAKE_DIR);
  client.println(dir);
  
  GetFTPAnswer();
}

void FTPClient_Generic::ContentList(const char * dir, String * list)
{
  char _resp[ sizeof(outBuf) ];
  uint16_t _b = 0;

  FTP_LOGINFO("Send MLSD");

  if (!isConnected())
    return;

  client.print(COMMAND_LIST_DIR_STANDARD);
  client.println(dir);
  GetFTPAnswer(_resp);

  // Convert char array to string to manipulate and find response size
  // each server reports it differently, TODO = FEAT
  //String resp_string = _resp;
  //resp_string.substring(resp_string.lastIndexOf('matches')-9);
  //FTP_LOGDEBUG(resp_string);

  unsigned long _m = millis();
  while ( !dclient.available() && millis() < _m + timeout) delay(1);

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

void FTPClient_Generic::ContentListWithListCommand(const char * dir, String * list)
{
  char _resp[ sizeof(outBuf) ];
  uint16_t _b = 0;

  FTP_LOGINFO("Send LIST");

  if (!isConnected())
    return;

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
  while ( !GetDataClient()->available() && millis() < _m + timeout) delay(1);

  while ( GetDataClient()->available() )
  {
    str += GetDataClient()->readString();
  }
}

void FTPClient_Generic::DownloadFile(const char * filename, unsigned char * buf, size_t length, bool printUART )
{
  FTP_LOGINFO("Send RETR");

  if (!isConnected())
    return;

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
        dclient.readBytes(_buf, 1),
                          Serial.print(_buf[0], HEX);
      }
    }
  }
}

#endif    // FTPCLIENT_GENERIC_IMPL_H
