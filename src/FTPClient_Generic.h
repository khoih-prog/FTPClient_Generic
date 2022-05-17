/****************************************************************************************************************************
  FTPClient_Generic.h

  FTP Client for Generic boards using SD, FS, etc.
  
  Based on and modified from 
  
  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient
    
  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
  
  Version: 1.3.0
    
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      11/05/2022 Initial porting and coding to support many more boards, using WiFi or Ethernet
  1.1.0   K Hoang      13/05/2022 Add support to Teensy 4.1 using QNEthernet or NativeEthernet
  1.2.0   K Hoang      14/05/2022 Add support to other FTP Servers. Fix bug
  1.2.1   K Hoang      14/05/2022 Auto detect server response type in PASV mode
  1.3.0   K Hoang      16/05/2022 Fix uploading issue of large files for WiFi, QNEthernet
 *****************************************************************************************************************************/

#pragma once

#ifndef FTPCLIENT_GENERIC_H
#define FTPCLIENT_GENERIC_H

/////////////////////////////////////////////////////////

#define FTPCLIENT_GENERIC_VERSION            "FTPCLIENT_GENERIC v1.3.0"

#define FTPCLIENT_GENERIC_VERSION_MAJOR      1
#define FTPCLIENT_GENERIC_VERSION_MINOR      3
#define FTPCLIENT_GENERIC_VERSION_PATCH      0

#define FTPCLIENT_GENERIC_VERSION_INT        1003000

/////////////////////////////////////////////////////////

#include "FTPClient_Generic.hpp"
#include "FTPClient_Generic_Impl.h"

/////////////////////////////////////////////////////////

#endif  // FTPCLIENT_GENERIC_H
