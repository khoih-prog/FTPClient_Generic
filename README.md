## FTPClient_Generic

[![arduino-library-badge](https://www.ardu-badge.com/badge/FTPClient_Generic.svg?)](https://www.ardu-badge.com/FTPClient_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/FTPClient_Generic.svg)](https://github.com/khoih-prog/FTPClient_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/FTPClient_Generic/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/FTPClient_Generic.svg)](http://github.com/khoih-prog/FTPClient_Generic/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents

* [Why do we need this FTPClient_Generic library](#why-do-we-need-this-FTPClient_Generic-library)
  * [Features](#features)
  * [Currently supported Boards using Ethernet](#currently-supported-boards-using-Ethernet)
  * [Currently supported Ethernet shields/modules](#currently-supported-ethernet-shieldsmodules)
  * [Currently supported Boards using WiFi](#currently-supported-boards-using-WiFi)
  * [Currently supported WiFi shields/modules](#currently-supported-wifi-shieldsmodules)
* [Changelog](changelog.md) 
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Adafruit nRF52840 and nRF52832 boards](#1-for-adafruit-nRF52840-and-nRF52832-boards)
  * [2. For Teensy boards](#2-for-teensy-boards)
  * [3. For Arduino SAM DUE boards](#3-for-arduino-sam-due-boards)
  * [4. For Arduino SAMD boards](#4-for-arduino-samd-boards)
      * [For core version v1.8.10+](#for-core-version-v1810)
      * [For core version v1.8.9-](#for-core-version-v189-)
  * [5. For Adafruit SAMD boards](#5-for-adafruit-samd-boards)
  * [6. For Seeeduino SAMD boards](#6-for-seeeduino-samd-boards)
  * [7. For STM32 boards](#7-for-stm32-boards) 
    * [7.1. For STM32 boards to use LAN8720](#71-for-stm32-boards-to-use-lan8720)
    * [7.2. For STM32 boards to use Serial1](#72-for-stm32-boards-to-use-serial1)
  * [8. For RP2040-based boards using Earle Philhower arduino-pico core](#8-for-rp2040-based-boards-using-earle-philhower-arduino-pico-core)
    * [8.1. To use BOARD_NAME](#81-to-use-board_name)
    * [8.2. To avoid compile error relating to microsecondsToClockCycles](#82-to-avoid-compile-error-relating-to-microsecondstoclockcycles)
  * [9. For Portenta_H7 boards using Arduino IDE in Linux](#9-for-portenta_h7-boards-using-arduino-ide-in-linux)
  * [10. For RTL8720DN boards using AmebaD core](#10-for-rtl8720dn-boards-using-amebad-core)
  * [11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core](#11-For-SAMD21-and-SAMD51-boards-using-ArduinoCore-fab-sam-core)
  * [12. For Seeeduino RP2040 boards](#12-For-Seeeduino-RP2040-boards)
* [Libraries' Patches](#libraries-patches)
  * [1. For application requiring 2K+ HTML page](#1-for-application-requiring-2k-html-page)
  * [2. For Ethernet library](#2-for-ethernet-library)
  * [3. For EthernetLarge library](#3-for-ethernetlarge-library)
  * [4. For Etherne2 library](#4-for-ethernet2-library)
  * [5. For Ethernet3 library](#5-for-ethernet3-library)
  * [6. For UIPEthernet library](#6-for-uipethernet-library)
  * [7. For fixing ESP32 compile error](#7-for-fixing-esp32-compile-error)
  * [8. For fixing ESP8266 compile error](#8-for-fixing-esp8266-compile-error)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error) 
* [HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)](#howto-use-analogread-with-esp32-running-wifi-andor-bluetooth-btble)
  * [1. ESP32 has 2 ADCs, named ADC1 and ADC2](#1--esp32-has-2-adcs-named-adc1-and-adc2)
  * [2. ESP32 ADCs functions](#2-esp32-adcs-functions)
  * [3. ESP32 WiFi uses ADC2 for WiFi functions](#3-esp32-wifi-uses-adc2-for-wifi-functions)
* [Configuration Notes for Ethernet](#configuration-notes-for-Ethernet)
  * [1. How to select which built-in Ethernet or shield to use](#1-how-to-select-which-built-in-ethernet-or-shield-to-use)
  * [Important](#important)
  * [2. How to select another CS/SS pin to use](#2-how-to-select-another-csss-pin-to-use)
  * [3. How to use W5x00 with ESP8266](#3-how-to-use-w5x00-with-esp8266)
  * [4. How to increase W5x00 TX/RX buffer](#4-how-to-increase-w5x00-txrx-buffer)
  * [5. How to adjust sendContent_P() and send_P() buffer size](#5-how-to-adjust-sendcontent_p-and-send_p-buffer-size)
  * [6. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library](#6-How-to-use-SPI2-for-ESP32-using-W5x00-and-Ethernet_Generic-Library)
  * [7. How to use SPI1 for RP2040 using W5x00 and Ethernet_Generic Library](#7-How-to-use-SPI1-for-RP2040-using-W5x00-and-Ethernet_Generic-Library)
  * [8. How to use SPI1/SPI2 for Teensy 4.x using W5x00 and Ethernet_Generic Library](#8-How-to-use-SPI1SPI2-for-Teensy-4x-using-W5x00-and-Ethernet_Generic-Library)
* [How to configure to use different WiFi Libraries](#how-to-configure-to-use-different-wifi-libraries) 
  * [1. Modify pin-to-pin connection in WiFiNINA_Generic library](#1-modify-pin-to-pin-connection-in-wifinina_generic-library)
  * [2. How to select which built-in WiFi or shield to use](#2-how-to-select-which-built-in-wifi-or-shield-to-use) 
  * [3. Important](#3-important) 
* [Usage](#usage)
  * [Class Constructor](#class-constructor)
  * [Basic Operation](#basic-operations)
* [Examples](#examples)
  * [Ethernet Examples](#Ethernet-examples)
    * [ 1. FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile)
    * [ 2. FTPClient_ListFiles](examples/Ethernet/FTPClient_ListFiles)
    * [ 3. FTPClient_UploadImage](examples/Ethernet/FTPClient_UploadImage)
    * [ 4. FTPClient_DownloadFile_RP2040_SPI1](examples/Ethernet/RP2040/FTPClient_DownloadFile_RP2040_SPI1)
    * [ 5. FTPClient_DownloadFile_STM32_LAN8742A](examples/Ethernet/STM32_LAN8742A/FTPClient_DownloadFile_STM32_LAN8742A)
    * [ 6. FTPClient_ListFiles_STM32_LAN8742A](examples/Ethernet/STM32_LAN8742A/FTPClient_ListFiles_STM32_LAN8742A)
  * [QNEthernet Examples](#QNEthernet-examples)
    * [ 1. FTPClient_DownloadFile](examples/QNEthernet/FTPClient_DownloadFile)
    * [ 2. FTPClient_ListFiles](examples/QNEthernet/FTPClient_ListFiles)
    * [ 3. FTPClient_UploadImage](examples/QNEthernet/FTPClient_UploadImage)
  * [WiFi Examples](#WiFi-examples)
    * [ 1. FTPClient_DownloadFile](examples/WiFi/FTPClient_DownloadFile)
    * [ 2. FTPClient_UploadImage](examples/WiFi/FTPClient_ListFiles)
    * [ 3. FTPClient_UploadImage](examples/WiFi/FTPClient_UploadImage)
  * [General Examples](#General-examples)
    * [ 1. multiFileProject](examples/multiFileProject)
* [Example FTPClient_DownloadFile](#example-FTPClient_DownloadFile)
  * [1. File FTPClient_DownloadFile.ino](#1-file-FTPClient_DownloadFileino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [ 1. FTPClient_DownloadFile on TEENSY 4.0 with W5x00 using Ethernet_Generic Library](#1-FTPClient_DownloadFile-on-TEENSY-40-with-W5x00-using-Ethernet_Generic-Library)
  * [ 2. FTPClient_UploadImage on Nano RP2040 Connect with WiFiNINA using WiFiNINA_Generic Library](#2-FTPClient_UploadImage-on-Nano-RP2040-Connect-with-WiFiNINA-using-WiFiNINA_Generic-Library)
  * [ 3. FTPClient_DownloadFile on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library](#3-FTPClient_DownloadFile-on-PORTENTA_H7_M7-with-Ethernet-using-Portenta_Ethernet-Library)
  * [ 4. FTPClient_UploadImage on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library](#4-FTPClient_UploadImage-on-MBED-RASPBERRY_PI_PICO-with-W5x00-using-Ethernet_Generic-Library)
  * [ 5. FTPClient_DownloadFile on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library](#5-FTPClient_DownloadFile-on-NUCLEO_L552ZE_Q-with-W5x00-using-Ethernet_Generic-Library)
  * [ 6. FTPClient_DownloadFile_STM32_LAN8742A on NUCLEO_F767ZI with LAN8742A Ethernet](#6-FTPClient_DownloadFile_STM32_LAN8742A-on-NUCLEO_F767ZI-with-LAN8742A-Ethernet)
  * [ 7. FTPClient_DownloadFile on ITSYBITSY_M4 with W5x00 using Ethernet_Generic Library](#7-FTPClient_DownloadFile-on-ITSYBITSY_M4-with-W5x00-using-Ethernet_Generic-Library)
  * [ 8. FTPClient_UploadImage on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library](#8-FTPClient_UploadImage-on-NRF52840_FEATHER-with-W5x00-using-Ethernet_Generic-Library)
  * [ 9. FTPClient_DownloadFile on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library](#9-FTPClient_DownloadFile-on-SAMD_NANO_33_IOT-with-WiFiNINA-using-WiFiNINA_Generic-Library)
  * [10. FTPClient_DownloadFile on ESP32S3_DEV with ESP WiFi using WiFi Library](#10-FTPClient_DownloadFile-on-ESP32S3_DEV-with-ESP-WiFi-using-WiFi-Library)
  * [11. FTPClient_UploadImage on TEENSY 4.1 with NativeEthernet](#11-FTPClient_UploadImage-on-TEENSY-41-with-NativeEthernet)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---


### Why do we need this [FTPClient_Generic library](https://github.com/khoih-prog/FTPClient_Generic)

#### Features

This [**FTPClient_Generic library**](https://github.com/khoih-prog/FTPClient_Generic) is a simple yet complete FTP Client library for **AVR, mega-AVR, Portenta_H7, Teensy, SAM DUE, Arduino SAMD21, Adafruit SAMD21/SAMD51, Adafruit nRF52, ESP32/ESP8266, STM32, RP2040-based, etc.** boards using either WiFi or Ethernet.

Library is based on and modified from:

1. [Leonardo Bispo's ESP32_FTPClient](https://github.com/ldab/ESP32_FTPClient)


Now supporting other new FTP Servers, such as [`vsftpd`](https://ubuntu.com/server/docs/service-ftp) in Linux, Ubuntu, Rasbberry Pi, etc.

---
---

#### Currently supported Boards using Ethernet

This [**FTPClient_Generic** library](https://github.com/khoih-prog/FTPClient_Generic) currently supports these following boards:

 1. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**
 2. **SAM DUE**
 3. **SAMD21**
  - Arduino SAMD21: ZERO, MKRs, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0): ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, Hallowing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 4. **SAMD51**
  - Adafruit SAMD51 (M4): Metro M4, Grand Central M4, ItsyBitsy M4, Feather M4 Express, Trellis M4, Metro M4 AirLift Lite, MONSTER M4SK Express, Hallowing M4, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 5. **Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC) with SPI, SPI1, SPI2**
 6. **AVR Mega1280, 2560, ADK.**
 7. ESP32
 8. ESP8266
 
 9. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico) with **SPI, SPI1**
 
 10. **Portenta_H7**
 
 11. **Arduino UNO WiFi Rev2, AVR_NANO_EVERY, etc.**

--- 

#### Currently supported Ethernet shields/modules

1. W5x00 using [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) library
2. W5x00 using [`Ethernet`](https://www.arduino.cc/en/Reference/Ethernet), [`EthernetLarge`](https://github.com/OPEnSLab-OSU/EthernetLarge), [`Ethernet2`](https://github.com/adafruit/Ethernet2) or [`Ethernet3`](https://github.com/sstaub/Ethernet3) library
3. ENC28J60 using [`EthernetENC`](https://github.com/jandrassy/EthernetENC) or [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
4. Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library. **From v1.1.0**
5. Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library. **From v1.1.0**
6. Portenta_H7 Ethernet using [`Portenta_Ethernet`](https://github.com/arduino/ArduinoCore-mbed/tree/master/libraries/Ethernet) library

---
---

#### Currently Supported Boards using WiFi

This [**FTPClient_Generic library**](https://github.com/khoih-prog/FTPClient_Generic) currently supports these following boards:

 1. SAM DUE

 2. SAMD21

  - Arduino: ZERO, MKR, NANO_33_IOT, etc.
  - Adafruit SAMD21 (M0) : ItsyBitsy M0, Feather M0, Feather M0 Express, Metro M0 Express, Circuit Playground Express, Trinket M0, PIRkey, HalloWing M0, Crickit M0, etc.
  - Seeeduino:  LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, etc.
  
 3. SAMD51

  - Adafruit SAMD51 (M4) : Metro M4, Grand Central M4, ItsyBitsy M4, Feather M44 Express, Trellis M4, Metro M4 AirLift lite, MONSTER M4SK Express, Hallowing EM4 xpress, etc.
  - Seeeduino: Wio Terminal, Grove UI Wireless
  
 4. Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0, LC)
 5. All STM32F/L/H/G/WB/MP1 with more than 32KB flash memory.
 6. AVR Mega1280, 2560, ADK, 32U4, 16U4, etc. using Arduino, Adafruit or Sparkfun core. To use patch for `ArduinoSTL` library.

 7. RP2040-based boards, such as **Nano RP2040 Connect**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico)
 
 8. RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed) or [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).

 9. **ESP32**
 
  - ESP32 boards, such as `ESP32_DEV`, etc.
  - ESP32S2-based boards, such as `ESP32S2_DEV`, `ESP32_S2 Saola`, etc.
  - ESP32C3-based boards, such as `ESP32C3_DEV`, etc. **New**
  - ESP32_S3 (ESP32S3_DEV, ESP32_S3_BOX, UM TINYS3, UM PROS3, UM FEATHERS3, etc.) **New**
  
10. **ESP8266**

11. **Portenta_H7**

12. **nRF52 boards**, such as **AdaFruit Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**

13. Arduino `megaAVR` boards using Arduino core

  - UNO WiFi Rev2   : `WiFi101`      **New**
  - Nano Every      : `WiFiEspAT`    **New**
  
14. CO2 Ampel

  - SAMD      : `WiFi101`      **New**

15. STM32 using `STM32duino Maple` core. **New**

16. Sparkfun SAMD

- SAMD21, SAMD51 : `WiFiEspAT`  **New**

17. Industruino SAMD

  - D21G : WiFiEspAT  **New**

18. Tlera Corp STM32WB boards

  - Firefly-WB55RG, Nucleo-WB55RG, etc. : `WiFiEspAT`  **New**

19. Maixduino boards

  - Sipeed Maixduino, etc. : `WiFiEspAT`  **New**

20. `RTL8720DN` using Realtek `AmebaD` core  **New**

21. Arduino, Sparkfun, Adafruit, etc. AVR boards (Mega, 32U4, etc.). To use patch for `ArduinoSTL` library **New**

  - Arduino Uno / Mega / Duemilanove / Diecimila / LilyPad / Mini / Fio / Nano, etc.
  - **Arduino ATMega 16U4, 32U4** such as AVR Leonardo, Leonardo ETH, YUN, Esplora, LILYPAD_USB, AVR_ROBOT_CONTROL, AVR_ROBOT_MOTOR, AVR_INDUSTRIAL101, etc.
  - **Adafruit ATMega 32U4** such as AVR_FLORA8, AVR_FEATHER32U4, AVR_CIRCUITPLAY, AVR_ITSYBITSY32U4_5V, AVR_ITSYBITSY32U4_3V, AVR_BLUEFRUITMICRO, AVR_ADAFRUIT32U4, etc.
  - **Adafruit ATMega 328(P)** such as AVR_METRO, AVR_FEATHER328P, AVR_PROTRINKET5, AVR_PROTRINKET3, AVR_PROTRINKET5FTDI, AVR_PROTRINKET3FTDI, etc.
  - **Generic or Sparkfun AVR ATmega_32U4** such as **AVR_MAKEYMAKEY, AVR_PROMICRO, etc.**
  - **Generic or Sparkfun AVR ATmega_328(P)** such as **ARDUINO_REDBOT, ARDUINO_AVR_DIGITAL_SANDBOX, etc.**
  - **Generic or Sparkfun AVR ATmega128RFA1** such as **ATMEGA128RFA1_DEV_BOARD, etc.**

---

#### Currently supported WiFi shields/modules

1. WiFiNINA using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
2. WiFi101 using [`WiFi101 library`](https://github.com/arduino-libraries/WiFi101) or [`Modified WiFi101 Library v0.16.1+`](https://github.com/khoih-prog/WiFi101)
3. u-blox W101, W102 using [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic)
4. ESP8266-AT command using [`WiFiEspAT library`](https://github.com/jandrassy/WiFiEspAT)
5. ESP8266/ESP32-AT command using [`ESP_AT_Lib library`](https://github.com/khoih-prog/ESP_AT_Lib)
6. Built-in WiFi of ESP32, ESP8266
7. Built-in WiFi of Portenta_H7


---
---


## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Arduino AVR core 1.8.5+`](https://github.com/arduino/ArduinoCore-avr) for Arduino (Use Arduino Board Manager) AVR boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-avr.svg)](https://github.com/arduino/ArduinoCore-avr/releases/latest)
 3. [`Teensy core v1.56+`](https://www.pjrc.com/teensy/td_download.html) for Teensy (4.1, 4.0, 3.6, 3.5, 3,2, 3.1, 3.0) boards.
 4. [`Arduino SAM DUE core v1.6.12+`](https://github.com/arduino/ArduinoCore-sam) for SAM DUE ARM Cortex-M3 boards.
 5. [`Arduino SAMD core 1.8.13+`](https://github.com/arduino/ArduinoCore-samd) for SAMD ARM Cortex-M0+ boards. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-samd.svg)](https://github.com/arduino/ArduinoCore-samd/releases/latest)
 6. [`Adafruit SAMD core 1.7.10+`](https://github.com/adafruit/ArduinoCore-samd) for SAMD ARM Cortex-M0+ and M4 boards (Nano 33 IoT, etc.). [![GitHub release](https://img.shields.io/github/release/adafruit/ArduinoCore-samd.svg)](https://github.com/adafruit/ArduinoCore-samd/releases/latest)
 7. [`Seeeduino SAMD core 1.8.2+`](https://github.com/Seeed-Studio/ArduinoCore-samd) for SAMD21/SAMD51 boards (XIAO M0, Wio Terminal, etc.). [![Latest release](https://img.shields.io/github/release/Seeed-Studio/ArduinoCore-samd.svg)](https://github.com/Seeed-Studio/ArduinoCore-samd/releases/latest/)
 8. [`Adafruit nRF52 v1.3.0+`](https://github.com/adafruit/Adafruit_nRF52_Arduino) for nRF52 boards such as Adafruit NRF52840_FEATHER, NRF52832_FEATHER, NRF52840_FEATHER_SENSE, NRF52840_ITSYBITSY, NRF52840_CIRCUITPLAY, NRF52840_CLUE, NRF52840_METRO, NRF52840_PCA10056, PARTICLE_XENON, **NINA_B302_ublox**, etc. [![GitHub release](https://img.shields.io/github/release/adafruit/Adafruit_nRF52_Arduino.svg)](https://github.com/adafruit/Adafruit_nRF52_Arduino/releases/latest)
 9. [`ESP32 Core 2.0.3+`](https://github.com/espressif/arduino-esp32) for ESP32-based boards. [![Latest release](https://img.shields.io/github/release/espressif/arduino-esp32.svg)](https://github.com/espressif/arduino-esp32/releases/latest/)
10. [`ESP8266 Core 3.0.2+`](https://github.com/esp8266/Arduino) for ESP8266-based boards. [![Latest release](https://img.shields.io/github/release/esp8266/Arduino.svg)](https://github.com/esp8266/Arduino/releases/latest/). To use ESP8266 core 2.7.1+ for LittleFS.
11. [`ArduinoCore-mbed mbed_rp2040, mbed_nano, mbed_portenta core 3.1.1+`](https://github.com/arduino/ArduinoCore-mbed) for Arduino (Use Arduino Board Manager) **Portenta_H7, RP2040-based boards, such as Nano_RP2040_Connect, RASPBERRY_PI_PICO**. [![GitHub release](https://img.shields.io/github/release/arduino/ArduinoCore-mbed.svg)](https://github.com/arduino/ArduinoCore-mbed/releases/latest)
12. [`Earle Philhower's arduino-pico core v2.0.1+`](https://github.com/earlephilhower/arduino-pico) for RP2040-based boards such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, etc. [![GitHub release](https://img.shields.io/github/release/earlephilhower/arduino-pico.svg)](https://github.com/earlephilhower/arduino-pico/releases/latest)
13. [`Arduino megaAVR core 1.8.7+`](https://github.com/arduino/ArduinoCore-megaavr/releases) for Arduino megaAVR boards such as **Arduino UNO WiFi Rev2, AVR_NANO_EVERY, etc.**
14. [`Functional-Vlpp library v1.0.2+`](https://github.com/khoih-prog/functional-vlpp) to use server's lambda function. To install. check [![arduino-library-badge](https://www.ardu-badge.com/badge/Functional-Vlpp.svg?)](https://www.ardu-badge.com/Functional-Vlpp)
15. Depending on which Ethernet card you're using:
   - [`Ethernet_Generic library v2.3.0+`](https://github.com/khoih-prog/Ethernet_Generic) for W5100, W5200 and W5500/WIZ550io/WIZ850io/USR-ES1 with Wiznet W5500 chip.  [![GitHub release](https://img.shields.io/github/release/khoih-prog/Ethernet_Generic.svg)](https://github.com/khoih-prog/Ethernet_Generic/releases/latest)
   - [`EthernetENC library v2.0.3+`](https://github.com/jandrassy/EthernetENC) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/jandrassy/EthernetENC.svg)](https://github.com/jandrassy/EthernetENC/releases/latest).
   - [`UIPEthernet library v2.0.12+`](https://github.com/UIPEthernet/UIPEthernet) for ENC28J60. [![GitHub release](https://img.shields.io/github/release/UIPEthernet/UIPEthernet.svg)](https://github.com/UIPEthernet/UIPEthernet/releases/latest)
   - [`NativeEthernet Library version stable111+`](https://github.com/vjmuzik/NativeEthernet) for Teensy 4.1 built-in Ethernet. **From v1.1.0**
   - [`QNEthernet Library version v0.14.0+`](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet. **From v1.1.0**
16. Depending on which WiFi you're using: 
   - [`WiFiNINA_Generic library v1.8.14-4+`](https://github.com/khoih-prog/WiFiNINA_Generic) if using WiFiNINA. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiNINA_Generic.svg?)](https://www.ardu-badge.com/WiFiNINA_Generic).
   - [`ESP_AT_Lib library v1.4.1+`](https://github.com/khoih-prog/ESP_AT_Lib) if using ESP8288/ESP32-AT shields. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/ESP_AT_Lib.svg?)](https://www.ardu-badge.com/ESP_AT_Lib).
   - [`Modified WiFi101 Library v0.16.1+`](https://github.com/khoih-prog/WiFi101) to use SAMD MKR1000, etc. boards with WiFi101.
   - [`WiFiEspAT library v1.3.2+`](https://github.com/jandrassy/WiFiEspAT) if using ESP8288/ESP32-AT shields. [![GitHub release](https://img.shields.io/github/release/jandrassy/WiFiEspAT.svg)](https://github.com/jandrassy/WiFiEspAT/releases/latest)
   - [`WiFiMulti_Generic library v1.1.1+`](https://github.com/khoih-prog/WiFiMulti_Generic) to use WiFiMulti function. To install, check [![arduino-library-badge](https://www.ardu-badge.com/badge/WiFiMulti_Generic.svg?)](https://www.ardu-badge.com/WiFiMulti_Generic). **New**

---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for `FTPClient_Generic`, then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/FTPClient_Generic.svg?)](https://www.ardu-badge.com/FTPClient_Generic) for more detailed instructions.

### Manual Install

1. Navigate to [FTPClient_Generic](https://github.com/khoih-prog/FTPClient_Generic) page.
2. Download the latest release `FTPClient_Generic-master.zip`.
3. Extract the zip file to `FTPClient_Generic-master` directory 
4. Copy the whole `FTPClient_Generic-master` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**FTPClient_Generic** library](https://registry.platformio.org/libraries/khoih-prog/FTPClient_Generic) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/FTPClient_Generic/installation). Search for FTPClient_Generic in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Adafruit nRF52840 and nRF52832 boards

**To be able to compile, run and automatically detect and display BOARD_NAME on nRF52840/nRF52832 boards**, you have to copy the whole [nRF52 Packages_Patches](Packages_Patches/adafruit/hardware/nrf52/1.3.0) directory into Adafruit nRF52 directory (~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0). 

Supposing the Adafruit nRF52 version is 1.3.0. These files must be copied into the directory:
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/1.3.0/cores/nRF5/Udp.h`**

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z
These files must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/boards.txt`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Print.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B302_ublox/variant.cpp`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.h`
- `~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/variants/NINA_B112_ublox/variant.cpp`
- **`~/.arduino15/packages/adafruit/hardware/nrf52/x.yy.z/cores/nRF5/Udp.h`**

#### 2. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

#### 3. For Arduino SAM DUE boards
 
 **To be able to compile and run on SAM DUE boards**, you have to copy the whole [SAM DUE](Packages_Patches/arduino/hardware/sam/1.6.12) directory into Arduino sam directory (~/.arduino15/packages/arduino/hardware/sam/1.6.12). 

Supposing the Arduino SAM core version is 1.6.12. This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/1.6.12/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/sam/x.yy.zz/platform.txt`

#### 4. For Arduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Arduino SAMD (Nano-33-IoT, etc) boards***, you have to copy the whole [Arduino SAMD Packages_Patches](Packages_Patches/arduino/hardware/samd/1.8.13) directory into Arduino SAMD directory (~/.arduino15/packages/arduino/hardware/samd/1.8.13).
 
#### For core version v1.8.10+

Supposing the Arduino SAMD version is 1.8.13. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.13/platform.txt`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.zz/platform.txt`
 
#### For core version v1.8.9-

Supposing the Arduino SAMD version is 1.8.9. These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/1.8.9/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/1.8.9/cores/arduino/Arduino.h`***

Whenever a new version is installed, remember to copy these files into the new version directory. For example, new version is x.yy.z

These files must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/samd/x.yy.z/platform.txt`
- ***`~/.arduino15/packages/arduino/hardware/samd/x.yy.z/cores/arduino/Arduino.h`***
 
 This is mandatory to fix the ***notorious Arduino SAMD compiler error***. See [Improve Arduino compatibility with the STL (min and max macro)](https://github.com/arduino/ArduinoCore-samd/pull/399)
 
```
 ...\arm-none-eabi\include\c++\7.2.1\bits\stl_algobase.h:243:56: error: macro "min" passed 3 arguments, but takes just 2
     min(const _Tp& __a, const _Tp& __b, _Compare __comp)
```

Whenever the above-mentioned compiler error issue is fixed with the new Arduino SAMD release, you don't need to copy the `Arduino.h` file anymore.

#### 5. For Adafruit SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Adafruit SAMD (Itsy-Bitsy M4, etc) boards***, you have to copy the whole [Adafruit SAMD Packages_Patches](Packages_Patches/adafruit/hardware/samd/1.7.10) directory into Adafruit samd directory (~/.arduino15/packages/adafruit/hardware/samd/1.7.10). 

Supposing the Adafruit SAMD core version is 1.7.10. This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/1.7.10/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/adafruit/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 6. For Seeeduino SAMD boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino SAMD (XIAO M0, Wio Terminal, etc) boards***, you have to copy the whole [Seeeduino SAMD Packages_Patches](Packages_Patches/Seeeduino/hardware/samd/1.8.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2). 

Supposing the Seeeduino SAMD core version is 1.8.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/1.8.2/cores/arduino/Print.cpp`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/platform.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Arduino.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.h`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/cores/arduino/Print.cpp`

#### 7. For STM32 boards

#### 7.1 For STM32 boards to use LAN8720

To use LAN8720 on some STM32 boards 

- **Nucleo-144 (F429ZI, NUCLEO_F746NG, NUCLEO_F746ZG, NUCLEO_F756ZG)**
- **Discovery (DISCO_F746NG)**
- **STM32F4 boards (BLACK_F407VE, BLACK_F407VG, BLACK_F407ZE, BLACK_F407ZG, BLACK_F407VE_Mini, DIYMORE_F407VGT, FK407M1)**

you have to copy the files [stm32f4xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F4xx) and [stm32f7xx_hal_conf_default.h](Packages_Patches/STM32/hardware/stm32/2.2.0/system/STM32F7xx) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system) to overwrite the old files.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F4xx/stm32f4xx_hal_conf_default.h` for STM32F4.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/system/STM32F7xx/stm32f7xx_hal_conf_default.h` for Nucleo-144 STM32F7.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F4xx/stm32f4xx_hal_conf_default.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/system/STM32F7xx/stm32f7xx_hal_conf_default.h


#### 7.2 For STM32 boards to use Serial1

**To use Serial1 on some STM32 boards without Serial1 definition (Nucleo-144 NUCLEO_F767ZI, Nucleo-64 NUCLEO_L053R8, etc.) boards**, you have to copy the files [STM32 variant.h](Packages_Patches/STM32/hardware/stm32/2.2.0) into STM32 stm32 directory (~/.arduino15/packages/STM32/hardware/stm32/2.2.0). You have to modify the files corresponding to your boards, this is just an illustration how to do.

Supposing the STM32 stm32 core version is 2.2.0. These files must be copied into the directory:

- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h` for Nucleo-144 NUCLEO_F767ZI.
- `~/.arduino15/packages/STM32/hardware/stm32/2.2.0/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h` for Nucleo-64 NUCLEO_L053R8.

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz,
theses files must be copied into the corresponding directory:

- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32F7xx/F765Z(G-I)T_F767Z(G-I)T_F777ZIT/NUCLEO_F767ZI/variant.h`
- `~/.arduino15/packages/STM32/hardware/stm32/x.yy.zz/variants/STM32L0xx/L052R(6-8)T_L053R(6-8)T_L063R8T/NUCLEO_L053R8/variant.h`

#### 8. For RP2040-based boards using [Earle Philhower arduino-pico core](https://github.com/earlephilhower/arduino-pico)

#### 8.1 To use BOARD_NAME

 **To be able to automatically detect and display BOARD_NAME on RP2040-based boards (RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040, GENERIC_RP2040, etc) boards**, you have to copy the file [RP2040 platform.txt](Packages_Patches/rp2040/hardware/rp2040/1.4.0) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0). 

Supposing the rp2040 core version is 1.4.0. This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/platform.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/platform.txt`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add -DBOARD_NAME="{build.board}" #136](https://github.com/earlephilhower/arduino-pico/pull/136).

#### 8.2 To avoid compile error relating to microsecondsToClockCycles

Some libraries, such as [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library), require the definition of microsecondsToClockCycles(). **To be able to compile and run on RP2040-based boards**, you have to copy the files in [**RP2040 Arduino.h**](Packages_Patches/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h) into rp2040 directory (~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0).

Supposing the rp2040 core version is 1.4.0. This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/1.4.0/cores/rp2040/Arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied to replace:

- `~/.arduino15/packages/rp2040/hardware/rp2040/x.yy.zz/cores/rp2040/Arduino.h`

With core after v1.5.0, this step is not necessary anymore thanks to the PR [Add defs for compatibility #142](https://github.com/earlephilhower/arduino-pico/pull/142).


#### 9. For Portenta_H7 boards using Arduino IDE in Linux

  **To be able to upload firmware to Portenta_H7 using Arduino IDE in Linux (Ubuntu, etc.)**, you have to copy the file [portenta_post_install.sh](Packages_Patches/arduino/hardware/mbed_portenta/3.0.1/portenta_post_install.sh) into mbed_portenta directory (~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.1/portenta_post_install.sh). 
  
  Then run the following command using `sudo`
  
```
$ cd ~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.1
$ chmod 755 portenta_post_install.sh
$ sudo ./portenta_post_install.sh
```

This will create the file `/etc/udev/rules.d/49-portenta_h7.rules` as follows:

```
# Portenta H7 bootloader mode UDEV rules

SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="035b", GROUP="plugdev", MODE="0666"
```

Supposing the ArduinoCore-mbed core version is 3.0.1. Now only one file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/3.0.1/portenta_post_install.sh`

Whenever a new version is installed, remember to copy this files into the new version directory. For example, new version is x.yy.zz

This file must be copied into the directory:

- `~/.arduino15/packages/arduino/hardware/mbed_portenta/x.yy.zz/portenta_post_install.sh`


#### 10. For RTL8720DN boards using AmebaD core
 
 To avoid compile error relating to PROGMEM, you have to copy the file [Realtek AmebaD core pgmspace.h](Packages_Patches/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h) into Realtek AmebaD directory (~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h). 

Supposing the Realtek AmebaD core version is 3.1.2. This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/3.1.2/cores/arduino/avr/pgmspace.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/realtek/hardware/AmebaD/x.yy.zz/cores/arduino/avr/pgmspace.h`


#### 11. For SAMD21 and SAMD51 boards using ArduinoCore-fab-sam core
 
 To avoid compile error relating to SAMD21/SAMD51, you have to copy the file [ArduinoCore-fab-sam core pgmspace.h](Packages_Patches/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt) into `ArduinoCore-fab-sam` samd directory (~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt). 

Supposing the `ArduinoCore-fab-sam` samd core version is 1.6.18-alpha2. This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/1.6.18-alpha2/boards.txt`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Fab_SAM_Arduino/hardware/samd/x.yy.zz/boards.txt`


#### 12. For Seeeduino RP2040 boards
 
 ***To be able to compile, run and automatically detect and display BOARD_NAME on Seeeduino RP2040 (XIAO RP2040, Wio RP2040 Mini) boards***, you have to copy the whole [Seeeduino RP2040 Packages_Patches](Packages_Patches/Seeeduino/hardware/rp2040/2.7.2) directory into Seeeduino samd directory (~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2). 

Supposing the Seeeduino SAMD core version is 2.7.2. This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/rp2040/2.7.2/variants/Seeed_XIAO_RP2040/pins_arduino.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
This file must be copied into the directory:

- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/boards.txt`
- `~/.arduino15/packages/Seeeduino/hardware/samd/x.yy.zz/variants/Seeed_XIAO_RP2040/pins_arduino.h`


---
---

### Libraries' Patches

#### 1. For application requiring 2K+ HTML page

If your application requires 2K+ HTML page, the current [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) must be modified if you are using W5200/W5500 Ethernet shields. W5100 is not supported for 2K+ buffer. If you use boards requiring different CS/SS pin for W5x00 Ethernet shield, for example ESP32, ESP8266, nRF52, etc., you also have to modify the following libraries to be able to specify the CS/SS pin correctly.

#### 2. For Ethernet library

To fix [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet), just copy these following files into the [`Ethernet library`](https://www.arduino.cc/en/Reference/Ethernet) directory to overwrite the old files:
- [Ethernet.h](LibraryPatches/Ethernet/src/Ethernet.h)
- [Ethernet.cpp](LibraryPatches/Ethernet/src/Ethernet.cpp)
- [EthernetServer.cpp](LibraryPatches/Ethernet/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/Ethernet/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/Ethernet/src/utility/w5100.cpp)

You can also use the forked and modified library at [Patched Ethernet](https://github.com/khoih-prog/Ethernet)

#### 3. For EthernetLarge library

To fix [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge), just copy these following files into the [`EthernetLarge library`](https://github.com/OPEnSLab-OSU/EthernetLarge) directory to overwrite the old files:
- [EthernetLarge.h](LibraryPatches/EthernetLarge/src/EthernetLarge.h)
- [EthernetLarge.cpp](LibraryPatches/EthernetLarge/src/EthernetLarge.cpp)
- [EthernetServer.cpp](LibraryPatches/EthernetLarge/src/EthernetServer.cpp)
- [w5100.h](LibraryPatches/EthernetLarge/src/utility/w5100.h)
- [w5100.cpp](LibraryPatches/EthernetLarge/src/utility/w5100.cpp)

You can also use the forked and modified library at [Patched EthernetLarge](https://github.com/khoih-prog/EthernetLarge)

#### 4. For Ethernet2 library

To fix [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2), just copy these following files into the [`Ethernet2 library`](https://github.com/khoih-prog/Ethernet2) directory to overwrite the old files:

- [Ethernet2.h](LibraryPatches/Ethernet2/src/Ethernet2.h)
- [Ethernet2.cpp](LibraryPatches/Ethernet2/src/Ethernet2.cpp)

To add UDP Multicast support, necessary for the [**UPnP_Generic library**](https://github.com/khoih-prog/UPnP_Generic):

- [EthernetUdp2.h](LibraryPatches/Ethernet2/src/EthernetUdp2.h)
- [EthernetUdp2.cpp](LibraryPatches/Ethernet2/src/EthernetUdp2.cpp)

You can also use the forked and modified library at [Patched Ethernet2](https://github.com/khoih-prog/Ethernet2)

#### 5. For Ethernet3 library

5. To fix [`Ethernet3 library`](https://github.com/sstaub/Ethernet3), just copy these following files into the [`Ethernet3 library`](https://github.com/sstaub/Ethernet3) directory to overwrite the old files:
- [Ethernet3.h](LibraryPatches/Ethernet3/src/Ethernet3.h)
- [Ethernet3.cpp](LibraryPatches/Ethernet3/src/Ethernet3.cpp)

You can also use the forked and modified library at [Patched Ethernet3](https://github.com/khoih-prog/Ethernet3)

#### 6. For UIPEthernet library

***To be able to compile and run on nRF52 boards with ENC28J60 using UIPEthernet library***, you have to copy these following files into the UIPEthernet `utility` directory to overwrite the old files:

- [UIPEthernet.h](LibraryPatches/UIPEthernet/UIPEthernet.h)
- [UIPEthernet.cpp](LibraryPatches/UIPEthernet/UIPEthernet.cpp)
- [Enc28J60Network.h](LibraryPatches/UIPEthernet/utility/Enc28J60Network.h)
- [Enc28J60Network.cpp](LibraryPatches/UIPEthernet/utility/Enc28J60Network.cpp)

#### 7. For fixing ESP32 compile error

To fix [`ESP32 compile error`](https://github.com/espressif/arduino-esp32), just copy the following file into the [`ESP32`](https://github.com/espressif/arduino-esp32) cores/esp32 directory (e.g. ./arduino-1.8.19/hardware/espressif/cores/esp32) to overwrite the old file:
- [Server.h](LibraryPatches/esp32/cores/esp32/Server.h)

#### 8. For fixing ESP8266 compile error

To fix `ESP8266 compile error` such as

```
error: 'class EthernetClass' has no member named 'init'
Ethernet.init (USE_THIS_SS_PIN);
```

just rename the following file in ./arduino-1.8.19/hardware/esp8266com/esp8266/libraries/Ethernet directory

- From `Ethernet.h` to `Ethernet_ESP8266.h`

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "FTPClient_Generic.hpp"     //https://github.com/khoih-prog/FTPClient_Generic
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "FTPClient_Generic.h"       //https://github.com/khoih-prog/FTPClient_Generic
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)


---
---

### HOWTO Use analogRead() with ESP32 running WiFi and/or BlueTooth (BT/BLE)

Please have a look at [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to have more detailed description and solution of the issue.

#### 1.  ESP32 has 2 ADCs, named ADC1 and ADC2

#### 2. ESP32 ADCs functions

- ADC1 controls ADC function for pins **GPIO32-GPIO39**
- ADC2 controls ADC function for pins **GPIO0, 2, 4, 12-15, 25-27**

#### 3.. ESP32 WiFi uses ADC2 for WiFi functions

Look in file [**adc_common.c**](https://github.com/espressif/esp-idf/blob/master/components/driver/adc_common.c#L61)

> In ADC2, there're two locks used for different cases:
> 1. lock shared with app and Wi-Fi:
>    ESP32:
>         When Wi-Fi using the ADC2, we assume it will never stop, so app checks the lock and returns immediately if failed.
>    ESP32S2:
>         The controller's control over the ADC is determined by the arbiter. There is no need to control by lock.
> 
> 2. lock shared between tasks:
>    when several tasks sharing the ADC2, we want to guarantee
>    all the requests will be handled.
>    Since conversions are short (about 31us), app returns the lock very soon,
>    we use a spinlock to stand there waiting to do conversions one by one.
> 
> adc2_spinlock should be acquired first, then adc2_wifi_lock or rtc_spinlock.


- In order to use ADC2 for other functions, we have to **acquire complicated firmware locks and very difficult to do**
- So, it's not advisable to use ADC2 with WiFi/BlueTooth (BT/BLE).
- Use ADC1, and pins GPIO32-GPIO39
- If somehow it's a must to use those pins serviced by ADC2 (**GPIO0, 2, 4, 12, 13, 14, 15, 25, 26 and 27**), use the **fix mentioned at the end** of [**ESP_WiFiManager Issue 39: Not able to read analog port when using the autoconnect example**](https://github.com/khoih-prog/ESP_WiFiManager/issues/39) to work with ESP32 WiFi/BlueTooth (BT/BLE).


---
---

### Configuration Notes for Ethernet

#### 1. How to select which built-in Ethernet or shield to use

The easiest way is to use 

```cpp
#define USE_ETHERNET_WRAPPER    true
```

then select **one and only one** Ethernet library to use as follows:

- Standard W5x00 Ethernet_Generic library is used by default, in the sketch, just be sure to comment out or leave these #defines to be false :

```cpp

// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

To use W5x00 Ethernet, for example using Ethernet_Generic library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      true
#define USE_ETHERNET_ESP8266      false
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```

- To use ENC28J60 Ethernet, using EthernetENC library (**NEW and Better**)

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false
#define USE_ETHERNET_ENC          true
#define USE_CUSTOM_ETHERNET       false
```

- To use ENC28J60 Ethernet, using UIPEthernet library:

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          true
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       false
```


- To use another Ethernet library
For example, EthernetLarge library

```cpp
// Only one if the following to be true
#define USE_UIP_ETHERNET          false
#define USE_ETHERNET_PORTENTA_H7  false
#define USE_NATIVE_ETHERNET       false
#define USE_QN_ETHERNET           false
#define USE_ETHERNET_GENERIC      false
#define USE_ETHERNET_ESP8266      false 
#define USE_ETHERNET_ENC          false
#define USE_CUSTOM_ETHERNET       true

//Must be placed before #include <FTPClient_Generic.h>
#include <EthernetLarge.h>
...

#include <FTPClient_Generic.h>
```

- Only for Teensy 4.1, to use NativeEthernet library

```
#if defined(__IMXRT1062__)
    // For Teensy 4.1/4.0
    #if defined(ARDUINO_TEENSY41)
      #define BOARD_TYPE      "TEENSY 4.1"
      // Use true for NativeEthernet Library, false if using other Ethernet libraries
      #define USE_NATIVE_ETHERNET     true
      #define USE_QN_ETHERNET         false
    #elif defined(ARDUINO_TEENSY40)
      #define BOARD_TYPE      "TEENSY 4.0"
    #else
      #define BOARD_TYPE      "TEENSY 4.x"
    #endif      
  #elif defined(__MK66FX1M0__)
  ....
```

- Only for Teensy 4.1, to use another Ethernet library, for example Ethernet_Generic library

```
#if defined(__IMXRT1062__)
  // For Teensy 4.1/4.0
  #if defined(ARDUINO_TEENSY41)
    #define BOARD_TYPE      "TEENSY 4.1"
    // Use true for NativeEthernet Library, false if using other Ethernet libraries
    #define USE_NATIVE_ETHERNET     false
    #define USE_QN_ETHERNET         false
  #elif defined(ARDUINO_TEENSY40)
    #define BOARD_TYPE      "TEENSY 4.0"
  #else
    #define BOARD_TYPE      "TEENSY 4.x"
  #endif      
#elif defined(__MK66FX1M0__)
  ....
  
#define USE_UIP_ETHERNET        false

// Only one if the following to be true
#define USE_ETHERNET_GENERIC    true
#define USE_ETHERNET_ESP8266    false
#define USE_ETHERNET_ENC        false
#define USE_CUSTOM_ETHERNET     false  
```

- Only for Teensy 4.1, to use QNEthernet library

```
#if ( defined(CORE_TEENSY) && defined(__IMXRT1062__) && defined(ARDUINO_TEENSY41) ) 
  // For Teensy 4.1
  #define BOARD_TYPE      "TEENSY 4.1"
  // Use true for NativeEthernet Library, false if using other Ethernet libraries
  #define USE_NATIVE_ETHERNET     false
  #define USE_QN_ETHERNET         true
#else
  #error Only Teensy 4.1 supported
#endif

#define USE_ETHERNET_WRAPPER    false

// Use true  for ENC28J60 and UIPEthernet library (https://github.com/UIPEthernet/UIPEthernet)
// Use false for W5x00 and Ethernetx library      (https://www.arduino.cc/en/Reference/Ethernet)

#define USE_UIP_ETHERNET        false
#define USE_ETHERNET_GENERIC    false
#define USE_ETHERNET_ESP8266    false 
#define USE_ETHERNET_ENC        false
#define USE_CUSTOM_ETHERNET     false

#if USE_NATIVE_ETHERNET
  #include "NativeEthernet.h"
  #warning Using NativeEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
  #define SHIELD_TYPE           "using NativeEthernet"
#elif USE_QN_ETHERNET
  #include "QNEthernet.h"
  using namespace qindesign::network;
  #warning Using QNEthernet lib for Teensy 4.1. Must also use Teensy Packages Patch or error
  #define SHIELD_TYPE           "using QNEthernet"  
#endif 
```

---

#### Important:

- The **Ethernet_Shield_W5200, EtherCard, EtherSia  libraries are not supported**. Don't use unless you know how to modify those libraries.
- Requests to support for any future custom Ethernet library will be ignored. **Use at your own risk**.

---

#### 2. How to select another CS/SS pin to use

The default CS/SS pin is GPIO4(D2) for ESP8266, GPIO22 for ESP32, 10 for all other boards.

If the default pin is not correct, the easiest way is to select the CS/SS pin (e.g. 22) to use as follows:

```cpp
// To override the default CS/SS pin. Don't use unless you know exactly which pin to use
#define USE_THIS_SS_PIN   22
```

#### 3. How to use W5x00 with ESP8266

To avoid using the default but not-working Ethernet library of ESP8266, rename the Ethernet.h/cpp to Ethernet_ESP8266.h/cpp to avoid library conflict if you're using the Arduino Ethernet library. The Ethernet_Generic, Ethernet2, Ethernet3, EthernetLarge library can be used without conflict.

These pins are tested OK with ESP8266 and W5x00

```cpp
  // For ESP8266
  // Pin                D0(GPIO16)    D1(GPIO5)    D2(GPIO4)    D3(GPIO0)    D4(GPIO2)    D8
  // Ethernet           0                 X            X            X            X        0
  // Ethernet2          X                 X            X            X            X        0
  // Ethernet3          X                 X            X            X            X        0
  // EthernetLarge      X                 X            X            X            X        0
  // Ethernet_ESP8266   0                 0            0            0            0        0
  // D2 is safe to used for Ethernet, Ethernet2, Ethernet3, EthernetLarge libs
  // Must use library patch for Ethernet, EthernetLarge libraries
  //Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (USE_THIS_SS_PIN);

```

#### 4. How to increase W5x00 TX/RX buffer

- For **Ethernet_Generic** library only,  simply use as follows to have large buffer similar to EthernetLarge library
```
#define ETHERNET_LARGE_BUFFERS
```

- For **Ethernet3** library only,  use as follows

```cpp
  // Use  MAX_SOCK_NUM = 4 for 4K, 2 for 8K, 1 for 16K RX/TX buffer
  #ifndef ETHERNET3_MAX_SOCK_NUM
    #define ETHERNET3_MAX_SOCK_NUM      4
  #endif
  
  Ethernet.setCsPin (USE_THIS_SS_PIN);
  Ethernet.init (ETHERNET3_MAX_SOCK_NUM);
```

### 5. How to adjust sendContent_P() and send_P() buffer size

sendContent_P() and send_P() buffer size is set default at 4 Kbytes, and minimum is 256 bytes. If you need to change, just add a definition, e.g.:

```cpp
#define SENDCONTENT_P_BUFFER_SZ     2048
```

Note that the buffer size must be larger than 256 bytes. See [Sending GZIP HTML ~ 120kb+ (suggested enhancement)](https://github.com/khoih-prog/FTPClient_Generic_STM32/issues/3).


### 6. How to use SPI2 for ESP32 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI2` for ESP32

```
#define USING_SPI2                          true
```

Pin to use for `SPI2`

```
MOSI:  13
MISO:  12
SCK:   14
SS:    5
```

### 7. How to use SPI1 for RP2040 using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI1` for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico) or [ArduinoCore-mbed](https://github.com/arduino/ArduinoCore-mbed)

```
#define USING_SPI2                          true
```

Pin to use for `SPI1`

```
MOSI:  15
MISO:  12
SCK:   14
SS:    13
```

### 8. How to use SPI1/SPI2 for Teensy 4.x using W5x00 and Ethernet_Generic Library

- For **Ethernet_Generic** library only, to use `SPI1/SPI2` for Teensy 4.x

```
#include <SPI.h>

  // For RPI Pico using Mbed RP2040 core
#if (USING_SPI2)
  #define USING_CUSTOM_SPI          true

  // Teensy4.1
  // SCK1: 27,  MOSI1: 26, MISO1:  1, SS1/CS1:  0 for SPI1
  // SCK2: 45,  MOSI2: 43, MISO2: 32, SS2/CS2: 44 for SPI2
  // Teensy4.0, in the back, untested
  // SCK1: 27,  MOSI1: 26, MISO1: 1, SS1/CS1: 0 for SPI1
  #define CUR_PIN_MISO              1
  #define CUR_PIN_MOSI              26
  #define CUR_PIN_SCK               27
  #define CUR_PIN_SS                0

  #define SPI_NEW_INITIALIZED       true

  // SPI1
  SPIClass SPI_New((uintptr_t)&IMXRT_LPSPI3_S, (uintptr_t)&SPIClass::spiclass_lpspi3_hardware);
  // SPI2
  //SPIClass SPI_New((uintptr_t)&IMXRT_LPSPI1_S, (uintptr_t)&SPIClass::spiclass_lpspi1_hardware);
  
  #warning Using USE_THIS_SS_PIN = CUR_PIN_SS = 38

  #if defined(USE_THIS_SS_PIN)
    #undef USE_THIS_SS_PIN
  #endif   
  #define USE_THIS_SS_PIN       CUR_PIN_SS

#endif  
```

Pin to use for `SPI1`

```
MOSI:  26
MISO:   1
SCK:   27
SS:     0
```

Pin to use for `SPI2`

```
MOSI:  43
MISO:  32
SCK:   45
SS:    44
```


---
---

### How to configure to use different WiFi Libraries

#### 1. Modify pin-to-pin connection in WiFiNINA_Generic library

Please change the pin-to-pin connection in `~/Arduino/libraries/src/WiFiNINA_Pinout_Generic.h` to match actual connection if using WiFiNINA with [`WiFiNINA_Generic library`](https://github.com/khoih-prog/WiFiNINA_Generic).

For example

```cpp
#elif ( defined(NRF52840_FEATHER) || defined(NRF52832_FEATHER) || defined(NRF52_SERIES) || defined(ARDUINO_NRF52_ADAFRUIT) || \
        defined(NRF52840_FEATHER_SENSE) || defined(NRF52840_ITSYBITSY) || defined(NRF52840_CIRCUITPLAY) || defined(NRF52840_CLUE) || \
        defined(NRF52840_METRO) || defined(NRF52840_PCA10056) || defined(PARTICLE_XENON) || defined(NINA_B302_ublox) || defined(NINA_B112_ublox) )

  #warning You have to modify pin usage accoring to actual connection for NRF528XX
  // To define pin out for WiFiNINA here

  //#define PINS_COUNT           (60u)
  //NINA
  #define NINA_GPIO0  (26u)                             //26
  #define NINA_RESETN (27u)
  #define NINA_ACK    (28u)

  #define SPIWIFI_SS       24   //PIN_SPI1_SS            //24
  #define SPIWIFI_ACK      28   //NINA_ACK               //28 
  #define SPIWIFI_RESET    27   //NINA_RESETN            //27
```

#### 2. How to select which built-in WiFi or shield to use

- To use W102-based WiFiNINA, define in the sketch:

```cpp
#define USE_WIFI_NINA         true
```

- To use built-in WiFi101 or shield:

```cpp
#define USE_WIFI_NINA         false
#define USE_WIFI101           true
```

- To use MKR1000 with built-in WiFi101:

```cpp
// Don't care false or true
#define USE_WIFI_NINA         false
```

- For boards other than MKR1000, to use another WiFi library with the standard **WiFi.h**, such as [`WiFiEspAT library`](https://github.com/jandrassy/WiFiEspAT) library

```cpp
#define USE_WIFI_NINA         false
```

- To use another WiFi library without the standard **WiFi.h**

For example, WiFi_XYZ library uses **WiFi_XYZ.h**

```cpp
#define USE_WIFI_NINA         false
#define USE_WIFI_CUSTOM       true

...
//Must be placed before #include <WiFiWebServer.h>
#include <WiFi_XYZ.h>
#include <WiFiWebServer.h>
```

#### 3. Important

- The **WiFiEsp, WiFi_Link libraries are not supported**. Don't use unless you know how to modify those libraries.
- Requests to support for any custom WiFi library will be ignored. **Use at your own risk**.

---
---

#### Usage


#### Class Constructor

```cpp
char ftp_server[] = "192.168.2.241";
char ftp_user[]   = "teensy4x";
char ftp_pass[]   = "ftp_test";

FTPClient_Generic ftp (ftp_server, ftp_user, ftp_pass, 60000);
```

---

#### Basic Operations

**Starting the FTP Client**

```cpp
ftp.OpenConnection();
```

**Change working directory**

```cpp
ftp.ChangeWorkDir("/");
```

**Create new directory**

```cpp
//Create a new Directory
ftp.InitFile(COMMAND_XFER_TYPE_BINARY);
ftp.MakeDir("myNewDir");
```

**List directory**

```cpp
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
```

---

**Upload text file using ASCII mode**

```cpp
ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
ftp.NewFile(fileName);
ftp.Write("Hi, I'm a new file");
ftp.CloseFile();
```

**Download text file using ASCII mode**

```cpp
String response = "";
ftp.InitFile(COMMAND_XFER_TYPE_ASCII);
ftp.DownloadString("helloworld.txt", response);
Serial.println("The file content is: " + response);
```

---

**Upload file using BINARY mode**

```cpp
//Dynammically alocate buffer
unsigned char * downloaded_file = (unsigned char *) malloc(fileSize);

ftp.InitFile(COMMAND_XFER_TYPE_BINARY);

//And upload the file to the new directory
ftp.NewFile( fileName );
ftp.WriteData(downloaded_file, fileSize);
ftp.CloseFile();
```

**Download file using BINARY mode**

```cpp
//Dynammically alocate buffer
unsigned char * downloaded_file = (unsigned char *) malloc(fileSize);

// And download the file
ftp.InitFile(COMMAND_XFER_TYPE_BINARY);
ftp.DownloadFile(fileName, downloaded_file, fileSize, false);
```

---
---

### Examples:

#### Ethernet Examples

 1. [FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile)
 2. [FTPClient_ListFiles](examples/Ethernet/FTPClient_ListFiles)
 3. [FTPClient_UploadImage](examples/Ethernet/FTPClient_UploadImage)
 4. [FTPClient_DownloadFile_RP2040_SPI1](examples/Ethernet/RP2040/FTPClient_DownloadFile_RP2040_SPI1)
 5. [FTPClient_DownloadFile_STM32_LAN8742A](examples/Ethernet/STM32_LAN8742A/FTPClient_DownloadFile_STM32_LAN8742A)
 6. [FTPClient_ListFiles_STM32_LAN8742A](examples/Ethernet/STM32_LAN8742A/FTPClient_ListFiles_STM32_LAN8742A)
 
#### QNEthernet Examples

 1. [FTPClient_DownloadFile](examples/QNEthernet/FTPClient_DownloadFile)
 2. [FTPClient_ListFiles](examples/QNEthernet/FTPClient_ListFiles)
 3. [FTPClient_UploadImage](examples/QNEthernet/FTPClient_UploadImage)
 
#### WiFi Examples
 
 1. [FTPClient_DownloadFile](examples/WiFi/FTPClient_DownloadFile)
 2. [FTPClient_ListFiles](examples/WiFi/FTPClient_ListFiles) 
 3. [FTPClient_UploadImage](examples/WiFi/FTPClient_UploadImage)

#### General Example
 
 1. [multiFileProject](examples/multiFileProject)
 

---
---

### Example [FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile)

#### 1. File [FTPClient_DownloadFile.ino](examples/Ethernet/FTPClient_DownloadFile/FTPClient_DownloadFile.ino)

https://github.com/khoih-prog/FTPClient_Generic/blob/a72a6cd7859491add0929ee4967dbd4c1705b73c/examples/Ethernet/FTPClient_DownloadFile/FTPClient_DownloadFile.ino#L13-L349


---

#### 2. File [defines.h](examples/Ethernet/FTPClient_DownloadFile/defines.h)

https://github.com/khoih-prog/FTPClient_Generic/blob/a72a6cd7859491add0929ee4967dbd4c1705b73c/examples/Ethernet/FTPClient_DownloadFile/defines.h#L12-L486

---
---

### Debug Terminal Output Samples

#### 1. FTPClient_DownloadFile on TEENSY 4.0 with W5x00 using Ethernet_Generic Library

The following is debug terminal output when running example [FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile) on TEENSY 4.0 with W5x00 using Ethernet_Generic Library on SPI0/SPI connecting to [`vsftpd`](https://ubuntu.com/server/docs/service-ftp) server


```
Starting FTPClient_DownloadFile on TEENSY 4.0 with W5x00 using Ethernet_Generic Library on SPI0/SPI
FTPCLIENT_GENERIC v1.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
[EWS] Board : TEENSY 4.0 , setCsPin: 10
[ETG] W5100 init, using SS_PIN_DEFAULT = 10 , new ss_pin =  10 , W5100Class::ss_pin =  10
[ETG] Chip is W5100S
[ETG] W5100::init: W5100S, SSIZE = 4096
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
Using mac index = 0
Connected! IP address: 192.168.2.97
[FTP] Connecting to:  192.168.2.112
[FTP] Command connected
[FTP] Send USER =  ftp_test
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
Creating new file helloworld.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,167,15).

[FTP] Data port:  42767
[FTP] _dataAddress:  192.168.2.112 , Data port:  42767
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,38,72).
[FTP] Data port:  9800
[FTP] _dataAddress:  192.168.2.112 , Data port:  9800
[FTP] Data connection established
[FTP] Send APPE
[FTP] Write File
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,56,103).
[FTP] Data port:  14439
[FTP] _dataAddress:  192.168.2.112 , Data port:  14439
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result:  150 Opening ASCII mode data connection for helloworld.txt (75 bytes).
timedRead timeout = 1000
The file content is: Hi, I'm a new ASCII file created @ millis = 2677
Added text @ millis = 2683
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 226 Transfer complete.
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,101,234).
[FTP] Data port:  26090
[FTP] _dataAddress:  192.168.2.112 , Data port:  26090
[FTP] Send LIST
[FTP] Result:  200 Switching to ASCII mode.
CloseConnection
[FTP] Connection closed
```

---

#### 2. FTPClient_UploadImage on Nano RP2040 Connect with WiFiNINA using WiFiNINA_Generic Library

The following is debug terminal output when running example [FTPClient_UploadImage](examples/WiFi/FTPClient_UploadImage) on Nano RP2040 Connect with WiFiNINA using WiFiNINA_Generic Library


```
Starting FTPClient_UploadImage on Nano RP2040 Connect with WiFiNINA using WiFiNINA_Generic Library
FTPCLIENT_GENERIC v1.3.0
Connecting WiFi
IP address: 192.168.2.117
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send CWD
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
Directory info: 
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Writing
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Connection closed
```


---

#### 3. FTPClient_DownloadFile on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library

The following is debug terminal output when running example [FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile) on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library


```
Starting FTPClient_DownloadFile on PORTENTA_H7_M7 with Ethernet using Portenta_Ethernet Library
FTPCLIENT_GENERIC v1.3.0
[EWS] ======== USE_PORTENTA_H7_ETHERNET ========
Using mac index = 13
Connected! IP address: 192.168.2.123
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
Creating new file helloworld.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226 File successfully transferred
[FTP] Result end
The file content is: Hi, I'm a new file
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
File size is: 18
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226-File successfully transferred
226 1 ms, 18 kbytes/s
[FTP] Result end
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MKD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send CWD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send STOR
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Writing
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Close File
CloseConnection
[FTP] Connection closed
```

---

#### 4. FTPClient_UploadImage on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library

The following is debug terminal output when running example [FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile) on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library on SPI0/SPI


```
Starting FTPClient_UploadImage on MBED RASPBERRY_PI_PICO with W5x00 using Ethernet_Generic Library on SPI0/SPI
FTPCLIENT_GENERIC v1.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
[EWS] RPIPICO setCsPin: 17
[ETG] W5100 init, using SS_PIN_DEFAULT = 17 , new ss_pin =  10 , W5100Class::ss_pin =  17
[ETG] Chip is W5100S
[ETG] W5100::init: W5100S, SSIZE = 4096
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 19
[EWS] MISO: 16
[EWS] SCK: 18
[EWS] SS: 17
[EWS] =========================
Using mac index = 3
Connected! IP address: 192.168.2.95
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send CWD
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
Directory info: 
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
Writing octocat.jpg
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Writing
[FTP] Close File
Writing hello_world.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Connection closed
```

---

#### 5. FTPClient_DownloadFile on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library

The following is debug terminal output when running example [FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile) on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library on SPI0/SPI


```
Starting FTPClient_DownloadFile on NUCLEO_L552ZE_Q with W5x00 using Ethernet_Generic Library on SPI0/SPI
FTPCLIENT_GENERIC v1.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
[EWS] Board : NUCLEO_L552ZE_Q , setCsPin: 10
[ETG] W5100 init, using SS_PIN_DEFAULT = 10 , new ss_pin =  10 , W5100Class::ss_pin =  10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 11
[EWS] MISO: 12
[EWS] SCK: 13
[EWS] SS: 10
[EWS] =========================
Using mac index = 1
Connected! IP address: 192.168.2.89
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
Creating new file helloworld.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226 File successfully transferred
[FTP] Result end
The file content is: Hi, I'm a new file
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
File size is: 18
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226 File successfully transferred
[FTP] Result end
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MKD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send CWD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send STOR
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Writing
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Close File
CloseConnection
[FTP] Connection closed
```

---


#### 6. FTPClient_DownloadFile_STM32_LAN8742A on NUCLEO_F767ZI with LAN8742A Ethernet

The following is debug terminal output when running example [FTPClient_DownloadFile_STM32_LAN8742A](examples/Ethernet/STM32_LAN8742A/FTPClient_DownloadFile_STM32_LAN8742A) on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library


```
Starting FTPClient_DownloadFile_STM32_LAN8742A on NUCLEO_F767ZI with LAN8742A Ethernet & STM32Ethernet Library
FTPCLIENT_GENERIC v1.3.0
EthernetWebServer_STM32 v1.5.0
Connected! IP address: 192.168.2.124
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
Creating new file helloworld.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226 File successfully transferred
[FTP] Result end
The file content is: Hi, I'm a new file
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
File size is: 18
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226-File successfully transferred
226 1 ms, 18 kbytes/s
[FTP] Result end
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MKD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send CWD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send STOR
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Writing
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Close File
CloseConnection
[FTP] Connection closed
```


---

#### 7. FTPClient_DownloadFile on ITSYBITSY_M4 with W5x00 using Ethernet_Generic Library

The following is debug terminal output when running example [FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile) on SAMD51 ITSYBITSY_M4 with W5x00 using Ethernet_Generic Library on SPI0/SPI


```
Starting FTPClient_DownloadFile on ITSYBITSY_M4 with W5x00 using Ethernet_Generic Library on SPI0/SPI
FTPCLIENT_GENERIC v1.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 23
[EWS] SCK: 24
[EWS] SS: 16
[EWS] =========================
[EWS] Board : ITSYBITSY_M4 , setCsPin: 10
[ETG] W5100 init, using SS_PIN_DEFAULT = 10 , new ss_pin =  10 , W5100Class::ss_pin =  10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 23
[EWS] SCK: 24
[EWS] SS: 16
[EWS] =========================
Using mac index = 1
Connected! IP address: 192.168.2.89
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
Creating new file helloworld.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226 File successfully transferred
[FTP] Result end
The file content is: Hi, I'm a new file
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
File size is: 18
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226 File successfully transferred
[FTP] Result end
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MKD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send CWD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send STOR
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Writing
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Close File
CloseConnection
[FTP] Connection closed
```

---

#### 8. FTPClient_UploadImage on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library

The following is debug terminal output when running example [FTPClient_DownloadFile](examples/Ethernet/FTPClient_DownloadFile) on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library on SPI0/SPI


```
Starting FTPClient_UploadImage on NRF52840_FEATHER with W5x00 using Ethernet_Generic Library on SPI0/SPI
FTPCLIENT_GENERIC v1.3.0
[EWS] =========== USE_ETHERNET_GENERIC ===========
[EWS] Default SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
[EWS] Board : NRF52840_FEATHER , setCsPin: 10
[ETG] W5100 init, using SS_PIN_DEFAULT = 10 , new ss_pin =  10 , W5100Class::ss_pin =  10
[ETG] Chip is W5500
[ETG] W5100::init: W5500, SSIZE = 8192
[EWS] =========================
[EWS] Currently Used SPI pinout:
[EWS] MOSI: 25
[EWS] MISO: 24
[EWS] SCK: 26
[EWS] SS: 5
[EWS] =========================
Using mac index = 1
Connected! IP address: 192.168.2.89
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send CWD
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
Directory info: 
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
Writing octocat.jpg
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Writing
[FTP] Close File
Writing hello_world.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Connection closed
```

---


#### 9. FTPClient_DownloadFile on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library

The following is debug terminal output when running example [FTPClient_DownloadFile](examples/WiFi/FTPClient_DownloadFile) on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library


```
Starting FTPClient_DownloadFile on SAMD_NANO_33_IOT with WiFiNINA using WiFiNINA_Generic Library
FTPCLIENT_GENERIC v1.3.0
Connecting WiFi
IP address: 192.168.2.118
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
Creating new file helloworld.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226 File successfully transferred
[FTP] Result end
The file content is: Hi, I'm a new file
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
File size is: 18
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226-File successfully transferred
226 1 ms, 18 kbytes/s
[FTP] Result end
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MKD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send CWD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send STOR
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Writing
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Close File
CloseConnection
[FTP] Connection closed
```


---


#### 10. FTPClient_DownloadFile on ESP32S3_DEV with ESP WiFi using WiFi Library

The following is debug terminal output when running example [FTPClient_DownloadFile](examples/WiFi/FTPClient_DownloadFile) on ESP32S3_DEV with ESP WiFi using WiFi Library


```
Starting FTPClient_DownloadFile on ESP32S3_DEV with ESP WiFi using WiFi Library
FTPCLIENT_GENERIC v1.3.0
Connecting WiFi
.........
IP address: 192.168.2.115
Max Free Heap: 270324
[FTP] Connecting to:  192.168.2.241
[FTP] Command connected
[FTP] Send USER =  teensy4x
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
Creating new file helloworld.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226 File successfully transferred
[FTP] Result end
The file content is: Hi, I'm a new file
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MLSD
[FTP] Result start
[FTP] Result:  150 Accepted data connection to port 55600
226-options: -a -l
226 18 matches total
[FTP] Result end
type=file;modify=20220429231446;size=3810; index1.htm
type=file;modify=19800101000000;size=13; foo.txt
type=file;modify=20190101003904;size=3714; index2.htm
type=file;modify=20220429225004;size=3810; index.htm
type=file;modify=20220409222458;size=10; mydatalog.txt
type=file;modify=20220313201514;size=4116; edit.htm.gz
type=file;modify=20220313201514;size=41214; canadaflag_1.png
type=file;modify=20220313201514;size=8311; canadaflag_2.png
type=file;modify=20220313201514;size=11156; canadaflag_3.jpg
type=file;modify=20190101003834;size=1150; favicon.ico
type=file;modify=20220313201514;size=1971; graphs.js.gz
type=file;modify=20220429225252;size=8311; canadaflag_2_1.png
type=file;modify=20220429225138;size=1547; esp_at_wm_lite.txt
type=file;modify=20190101002054;size=18; helloworld.txt
type=dir;modify=20190101000020;size=0; mynewdir
type=dir;modify=20190101001150;size=0; my_new_dir
type=file;modify=20190101001412;size=51695; octocat.jpg
type=file;modify=20190101001414;size=11; hello_world.txt
File size is: 18
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send RETR
[FTP] Result start
[FTP] Result:  150-Connected to port 55600
150 18 bytes to download
226-File successfully transferred
226 1 ms, 18 kbytes/s
[FTP] Result end
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (4043483328, port 55600)
[FTP] _dataAddress:  192.168.2.241 , Data port:  55600
[FTP] Data connection established
[FTP] Send MKD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send CWD
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Send STOR
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Writing
[FTP] FTP error:  521 "myNewDir" directory already exists
[FTP] Close File
CloseConnection
[FTP] Connection closed
```

---

#### 11. FTPClient_UploadImage on TEENSY 4.1 with NativeEthernet

The following is debug terminal output when running example [FTPClient_UploadImage](examples/QNEthernet/FTPClient_UploadImage) on TEENSY 4.1 with using NativeEthernet, connecting to [`vsftpd`](https://ubuntu.com/server/docs/service-ftp) server

```
Starting FTPClient_UploadImage on TEENSY 4.1 with NativeEthernet
FTPCLIENT_GENERIC v1.3.0
[EWS] ======== USE_NATIVE_ETHERNET ========
[EWS] =====================================
Using mac index = 6
Connected! IP address: 192.168.2.105
[FTP] Connecting to:  192.168.2.112
[FTP] Command connected
[FTP] Send USER =  ftp_test
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,156,132).

[FTP] Data port:  40068
[FTP] _dataAddress:  192.168.2.112 , Data port:  40068
[FTP] Data connection established
[FTP] Send LIST
[FTP] Result:  150 Here comes the directory listing.
NewDir
hello_world.txt
helloworld.txt
octocat.jpg
Writing octocat.jpg, size = 51695
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 226 Directory send OK.
227 Entering Passive Mode (192,168,2,112,27,30).
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,122,216).
[FTP] Data port:  31448
[FTP] _dataAddress:  192.168.2.112 , Data port:  31448
[FTP] Data connection established
[FTP] Send STOR
[FTP] Writing
[FTP] WriteData: datalen =  51695
[FTP] Close File
Writing hello_world.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,151,205).
[FTP] Data port:  38861
[FTP] _dataAddress:  192.168.2.112 , Data port:  38861
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Connection closed
```

---

#### 12. FTPClient_UploadImage on TEENSY 4.1 with NativeEthernet

The following is debug terminal output and directory listing after running example [FTPClient_UploadImage](examples/QNEthernet/FTPClient_UploadImage) on TEENSY 4.1 with using QNEthernet, connecting to [`vsftpd`](https://ubuntu.com/server/docs/service-ftp) server

```
Starting FTPClient_UploadImage on TEENSY 4.1 with QNEthernet
FTPCLIENT_GENERIC v1.3.0
[EWS] =========== USE_QN_ETHERNET ===========
Initialize Ethernet using static IP => IP Address = 192.168.2.222
[FTP] Connecting to:  192.168.2.112
[FTP] Command connected
[FTP] Send USER =  ftp_test
[FTP] Send PASSWORD =  ftp_test
[FTP] Send CWD
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,203,166).

[FTP] Data port:  52134
[FTP] _dataAddress:  192.168.2.112 , Data port:  52134
[FTP] Data connection established
[FTP] Send LIST
[FTP] Result:  150 Here comes the directory listing.
226 Directory send OK.
NewDir
hello_world.txt
helloworld.txt
Writing octocat.jpg, size = 51695
[FTP] Send TYPE Type I
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,215,146).
[FTP] Data port:  55186
[FTP] _dataAddress:  192.168.2.112 , Data port:  55186
[FTP] Data connection established
[FTP] Send STOR
[FTP] Writing
[FTP] WriteData: datalen =  51695
[FTP] Close File
Writing hello_world.txt
[FTP] Send TYPE Type A
[FTP] Send PASV
[FTP] outBuf = 227 Entering Passive Mode (192,168,2,112,127,205).
[FTP] Data port:  32717
[FTP] _dataAddress:  192.168.2.112 , Data port:  32717
[FTP] Data connection established
[FTP] Send STOR
[FTP] Write File
[FTP] Close File
[FTP] Connection closed
```

- Directory listing

```
pi@raspberrypi-02:/home/ftp_test $ ls -la
total 84
drwxrwxrwx 3 ftp_test ftp_test  4096 May 16 21:26 .
drwxr-xr-x 4 root     root      4096 May 14 16:55 ..
-rw-r--r-- 1 ftp_test ftp_test   220 May 14 16:55 .bash_logout
-rw-r--r-- 1 ftp_test ftp_test  3523 May 14 16:55 .bashrc
-rwxrwxrwx 1 ftp_test ftp_test    11 May 16 21:26 hello_world.txt
-rwxrwxrwx 1 ftp_test ftp_test    75 May 16 20:29 helloworld.txt
drwx------ 2 ftp_test ftp_test  4096 May 16 20:19 NewDir
-rw------- 1 ftp_test ftp_test 51695 May 16 21:26 octocat.jpg
-rw-r--r-- 1 ftp_test ftp_test   807 May 14 16:55 .profile
```

---
---

### Debug

Debug is enabled by default on Serial. Debug Level from 0 to 4. To disable, change the _ETHERNET_WEBSERVER_LOGLEVEL_ to 0

```cpp
// Use this to output debug msgs to Serial
#define DEBUG_ETHERNET_WEBSERVER_PORT       Serial

// Use this to disable all output debug msgs
// Debug Level from 0 to 4
#define _ETHERNET_WEBSERVER_LOGLEVEL_       0
#define _FTP_LOGLEVEL_                      1
```

---

## Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the board's core, applying Libraries' Patches, Packages' Patches or this library latest version.

---
---

### Issues ###

Submit issues to: [FTPClient_Generic issues](https://github.com/khoih-prog/FTPClient_Generic/issues)

---

### TO DO

1. Bug Searching and Killing
2. Support more types of boards using Ethernet / WiFi shields
3. Support more types ofFTP commands


### DONE

 1. Add support to **Arduino SAMD21 (ZERO, MKR, NANO_33_IOT, etc.)**
 2. Add support to **Adafruit SAMD21 (Itsy-Bitsy M0, Metro M0, Feather M0 Express, etc.)**.
 3. Add support to **Adafruit SAMD51 (Itsy-Bitsy M4, Metro M4, Grand Central M4, Feather M4 Express, etc.)**.
 4. Add support to **Adafruit nRF52 ( Feather nRF52832, nRF52840 Express, BlueFruit Sense, Itsy-Bitsy nRF52840 Express, Metro nRF52840 Express, NINA_B302_ublox, NINA_B112_ublox, etc.**.
 5. Add support to SAM DUE.
 6. Add support to Ethernet W5x00, using [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic) library
 7. Add support to Ethernet ENC28J60, using [`UIPEthernet`](https://github.com/UIPEthernet/UIPEthernet) library
 8. Add support to ESP32 and ESP8266 using WiFi or Ethernet
 9. Add support to Seeeduino SAMD21/SAMD51: LoRaWAN, Zero, Femto M0, XIAO M0, Wio GPS Board, Wio Terminal, Grove UI Wireless
10. Add support to [`EthernetENC`](https://github.com/jandrassy/EthernetENC)
11. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed)
12. Add support to RP2040-based boards such as RASPBERRY_PI_PICO, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico)
13. Add support to Teensy 4.1 built-in Ethernet using [`NativeEthernet`](https://github.com/vjmuzik/NativeEthernet) library. **From v1.1.0**
14. Add support to Teensy 4.1 built-in Ethernet using [`QNEthernet`](https://github.com/ssilverman/QNEthernet) library. **From v1.1.0**
15. Add support to **Portenta_H7 boards**, using [**Arduino-mbed mbed_portenta** core](https://github.com/arduino/ArduinoCore-mbed).
16. Add support to SAMD21/SAMD51 boards using [Fab_SAM_Arduino core](https://github.com/qbolsee/ArduinoCore-fab-sam)
17. Use new [**Ethernet_Generic** library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
18. Support **SPI2 for ESP32**
19. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
20. Add example [multiFileProject](examples/multiFileProject) to demo how to avoid `multiple-definitions` linker error for multiple-file project
21. Add support to SPI1, SPI2 for Teensy using W5x00 with [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)
22. Add support to custom SPI for Mbed RP2040, Portenta-H7, etc. using W5x00 with [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic)
23. Add support to all STM32F/L/H/G/WB/MP1.
24. Add support to WiFiNINA using [**WiFiNINA_Generic library**](https://github.com/khoih-prog/WiFiNINA_Generic). 
26. Add support to [`WiFi101 library`](https://www.arduino.cc/en/Reference/WiFi101)
27. Add support to new **ESP32-S2, ESP32-S3 and ESP32_C3**
28. Add support to other new FTP Servers, such as [`vsftpd`](https://ubuntu.com/server/docs/service-ftp) in Linux, Ubuntu, Rasbberry Pi, etc.
29. Auto detect server response type in **PASV** mode
30. Fix uploading issue of large files for **WiFi, QNEthernet**


---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

1. Based on and modified from the [Leonardo Bispo's ESP32_FTPClient](https://github.com/ldab/ESP32_FTPClient)


<table>
  <tr>
    <td align="center"><a href="https://github.com/ldab"><img src="https://github.com/ldab.png" width="100px;" alt="ldab"/><br /><sub><b>⭐️ Leonardo Bispo</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:
- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/FTPClient_Generic/blob/main/LICENSE)

---

## Copyright

1. Copyright (C) 2019- Leonardo Bispo
2. Copyright (C) 2022- Khoi Hoang


