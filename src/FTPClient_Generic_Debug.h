/****************************************************************************************************************************
  FTPClient_Generic_Debug.h

  FTP Client for Generic boards using SD, FS, etc.
  
  Based on and modified from 
  
  1) esp32_ftpclient Library         https://github.com/ldab/ESP32_FTPClient
    
  Built by Khoi Hoang https://github.com/khoih-prog/FTPClient_Generic
  
  Version: 1.2.1
    
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      11/05/2022 Initial porting and coding to support many more boards, using WiFi or Ethernet
  1.1.0   K Hoang      13/05/2022 Add support to Teensy 4.1 using QNEthernet or NativeEthernet
  1.2.0   K Hoang      14/05/2022 Add support to other FTP Servers. Fix bug
  1.2.1   K Hoang      14/05/2022 Auto detect server response type in PASV mode
 *****************************************************************************************************************************/

#pragma once

#ifndef FTPCLIENT_GENERIC_DEBUG_H
#define FTPCLIENT_GENERIC_DEBUG_H

#include <stdio.h>

#ifdef DEBUG_FTP_GENERIC_PORT
#define FTP_DEBUG_OUTPUT 			DEBUG_FTP_GENERIC_PORT
#else
#define FTP_DEBUG_OUTPUT 			Serial
#endif

// Change _FTP_LOGLEVEL_ to set tracing and logging verbosity
// 0: DISABLED: no logging
// 1: ERROR: errors
// 2: WARN: errors and warnings
// 3: INFO: errors, warnings and informational (default)
// 4: DEBUG: errors, warnings, informational and debug

#ifndef _FTP_LOGLEVEL_
	#define _FTP_LOGLEVEL_       1
#endif

///////////////////////////////////////

const char FTP_MARK[]  = "[FTP] ";
const char FTP_SPACE[] = " ";
const char FTP_LINE[]  = "========================================\n";

#define FTP_PRINT_MARK   FTP_PRINT(FTP_MARK)
#define FTP_PRINT_SP     FTP_PRINT(FTP_SPACE)
#define FTP_PRINT_LINE   FTP_PRINT(FTP_LINE)

#define FTP_PRINT        FTP_DEBUG_OUTPUT.print
#define FTP_PRINTLN      FTP_DEBUG_OUTPUT.println

///////////////////////////////////////

#define FTP_LOGERROR(x)         if(_FTP_LOGLEVEL_>0) { FTP_PRINT_MARK; FTP_PRINTLN(x); }
#define FTP_LOGERROR_LINE(x)    if(_FTP_LOGLEVEL_>0) { FTP_PRINT_MARK; FTP_PRINTLN(x); FTP_PRINT_LINE; }
#define FTP_LOGERROR0(x)        if(_FTP_LOGLEVEL_>0) { FTP_PRINT(x); }
#define FTP_LOGERROR1(x,y)      if(_FTP_LOGLEVEL_>0) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINTLN(y); }
#define FTP_LOGERROR2(x,y,z)    if(_FTP_LOGLEVEL_>0) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINTLN(z); }
#define FTP_LOGERROR3(x,y,z,w)  if(_FTP_LOGLEVEL_>0) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINT(z); FTP_PRINT_SP; FTP_PRINTLN(w); }
#define FTP_LOGERROR5(x,y,z,w, xx, yy)  if(_FTP_LOGLEVEL_>0) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINT(z); FTP_PRINT_SP; FTP_PRINT(w); FTP_PRINT_SP; FTP_PRINT(xx); FTP_PRINT_SP; FTP_PRINTLN(yy);}

///////////////////////////////////////

#define FTP_LOGWARN(x)          if(_FTP_LOGLEVEL_>1) { FTP_PRINT_MARK; FTP_PRINTLN(x); }
#define FTP_LOGWARN_LINE(x)     if(_FTP_LOGLEVEL_>1) { FTP_PRINT_MARK; FTP_PRINTLN(x); FTP_PRINT_LINE; }
#define FTP_LOGWARN0(x)         if(_FTP_LOGLEVEL_>1) { FTP_PRINT(x); }
#define FTP_LOGWARN1(x,y)       if(_FTP_LOGLEVEL_>1) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINTLN(y); }
#define FTP_LOGWARN2(x,y,z)     if(_FTP_LOGLEVEL_>1) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINTLN(z); }
#define FTP_LOGWARN3(x,y,z,w)   if(_FTP_LOGLEVEL_>1) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINT(z); FTP_PRINT_SP; FTP_PRINTLN(w); }
#define FTP_LOGWARN5(x,y,z,w, xx, yy)  if(_FTP_LOGLEVEL_>1) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINT(z); FTP_PRINT_SP; FTP_PRINT(w); FTP_PRINT_SP; FTP_PRINT(xx); FTP_PRINT_SP; FTP_PRINTLN(yy);}

///////////////////////////////////////

#define FTP_LOGINFO(x)          if(_FTP_LOGLEVEL_>2) { FTP_PRINT_MARK; FTP_PRINTLN(x); }
#define FTP_LOGINFO_LINE(x)     if(_FTP_LOGLEVEL_>2) { FTP_PRINT_MARK; FTP_PRINTLN(x); FTP_PRINT_LINE; }
#define FTP_LOGINFO0(x)         if(_FTP_LOGLEVEL_>2) { FTP_PRINT(x); }
#define FTP_LOGINFO1(x,y)       if(_FTP_LOGLEVEL_>2) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINTLN(y); }
#define FTP_LOGINFO2(x,y,z)     if(_FTP_LOGLEVEL_>2) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINTLN(z); }
#define FTP_LOGINFO3(x,y,z,w)   if(_FTP_LOGLEVEL_>2) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINT(z); FTP_PRINT_SP; FTP_PRINTLN(w); }
#define FTP_LOGINFO5(x,y,z,w, xx, yy)  if(_FTP_LOGLEVEL_>2) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINT(z); FTP_PRINT_SP; FTP_PRINT(w); FTP_PRINT_SP; FTP_PRINT(xx); FTP_PRINT_SP; FTP_PRINTLN(yy);}

///////////////////////////////////////

#define FTP_LOGDEBUG(x)         if(_FTP_LOGLEVEL_>3) { FTP_PRINT_MARK; FTP_PRINTLN(x); }
#define FTP_LOGDEBUG_LINE(x)    if(_FTP_LOGLEVEL_>3) { FTP_PRINT_MARK; FTP_PRINTLN(x); FTP_PRINT_LINE; }
#define FTP_LOGDEBUG0(x)        if(_FTP_LOGLEVEL_>3) { FTP_PRINT(x); }
#define FTP_LOGDEBUG1(x,y)      if(_FTP_LOGLEVEL_>3) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINTLN(y); }
#define FTP_LOGHEXDEBUG1(x,y)   if(_FTP_LOGLEVEL_>3) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINTLN(y, HEX); }
#define FTP_LOGDEBUG2(x,y,z)    if(_FTP_LOGLEVEL_>3) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINTLN(z); }
#define FTP_LOGDEBUG3(x,y,z,w)  if(_FTP_LOGLEVEL_>3) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINT(z); FTP_PRINT_SP; FTP_PRINTLN(w); }
#define FTP_LOGDEBUG5(x,y,z,w, xx, yy)  if(_FTP_LOGLEVEL_>3) { FTP_PRINT_MARK; FTP_PRINT(x); FTP_PRINT_SP; FTP_PRINT(y); FTP_PRINT_SP; FTP_PRINT(z); FTP_PRINT_SP; FTP_PRINT(w); FTP_PRINT_SP; FTP_PRINT(xx); FTP_PRINT_SP; FTP_PRINTLN(yy);}

/////////////////////////////////////////////

#endif		// FTPCLIENT_GENERIC_DEBUG_H
