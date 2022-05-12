/****************************************************************************************************************************
  FTPClient_Generic.h

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

#ifndef FTPCLIENT_GENERIC_H
#define FTPCLIENT_GENERIC_H

/////////////////////////////////////////////////////////

#define FTPCLIENT_GENERIC_VERSION            "FTPCLIENT_GENERIC v1.0.0"

#define FTPCLIENT_GENERIC_VERSION_MAJOR      1
#define FTPCLIENT_GENERIC_VERSION_MINOR      0
#define FTPCLIENT_GENERIC_VERSION_PATCH      0

#define FTPCLIENT_GENERIC_VERSION_INT        1000000


/////////////////////////////////////////////////////////

#include "FTPClient_Generic.hpp"
#include "FTPClient_Generic_Impl.h"

/////////////////////////////////////////////////////////

#endif  // FTPCLIENT_GENERIC_H
