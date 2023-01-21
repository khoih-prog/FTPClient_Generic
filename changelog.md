## FTPClient_Generic Library

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


* [Changelog](#changelog)
  * [Releases v1.6.0](#releases-v160)
  * [Releases v1.5.0](#releases-v150)
  * [Releases v1.4.0](#releases-v140)
  * [Releases v1.3.0](#releases-v130)
  * [Releases v1.2.1](#releases-v121)
  * [Releases v1.2.0](#releases-v120)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.0](#releases-v100)

---
---

## Changelog

#### Releases v1.6.0

1. Add support to WIZNet `W6100` using [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) library

#### Releases v1.5.0

1. Add support to `RP2040W` with `CYW43439` WiFi using `arduino-pico` core

#### Releases v1.4.0

1. Add support to `ESP32/ESP8266` using Ethernet `W5x00` or `ENC28J60` with [`Ethernet_Generic`](https://github.com/khoih-prog/Ethernet_Generic) or [`EthernetENC`](https://github.com/jandrassy/EthernetENC) library
2. Add astyle using `allman` style. Restyle the library
3. Update `Packages' Patches`

#### Releases v1.3.0

1. Fix uploading issue of large files for WiFi, QNEthernet

#### Releases v1.2.1

1. Auto detect server response type in PASV mode

#### Releases v1.2.0

1. Add support to other new FTP Servers, such as [`vsftpd`](https://ubuntu.com/server/docs/service-ftp) in Linux, Ubuntu, Rasbberry Pi, etc.
2. Fix bug
3. Update examples


#### Releases v1.1.0

1. Add support to Teensy 4.1 using QNEthernet or NativeEthernet
2. Add examples for QNEthernet and NativeEthernet

#### Releases v1.0.0

1. Initial porting and coding to support many more boards, using WiFi or Ethernet


