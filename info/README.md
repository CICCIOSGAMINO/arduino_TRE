Info
====
[TOC]

## Intro 
Some useful information about the system (OS + WebIDE) Debian + Arduino. We are talking 
here about all information you can reach in the Debian OS through a SSH connection : 

    ssh arduinotre@192.168.7.2
    
    arduinotre@TRE:~$

### Version 
The version refer to the Arduino TRE version and can be reach through the : 

    cat /etc/arduino_version 
    >> 0.0.12

For the WebIDE we can reach the same information by read the webide/package.json : 

    head /var/webide/package.json 
    
Or the complete information you can find in a node package.json, with the node project dependancies and 
so on with the cat command : 

    cat /var/webide/package.json 
    
So you easily understand that all the WebIDE project is hosted in the folder **/var/webide/ 

### Packages 
To see all the packages that power the Arduino environment on the Arduino TRE board : 

    dpkg-query -l | grep arduino 
    >> ii  arduino-betatest                      0.0.12-1                           armhf        Arduino Tre beta test
    ii  arduino-bridge                        1.5.1-1                            armhf        Arduino Bridge
    ii  arduino-corelibs                      1.5.8-2                            armhf        Arduino core libraries
    ii  arduino-examples                      1.5.8-1                            armhf        Arduino examples
    ii  arduino-platform-avr                  1.5.8-2                            armhf        Arduino AVR core
    ii  arduino-platform-sam                  1.5.8-1                            armhf        Arduino SAM core
    ii  arduino-platform-sitara               0.0.3-3                            armhf        Arduino Sitara core
    ii  arduino-process-talkie                0.0.3-1                            armhf        Arduino Process Talkie
    ii  arduino-sketchcompiler                0.0.2-1                            armhf        Arduino sketch compiler and uploader
    ii  arduino-tools-avr-armv7l              4.3.2-4                            armhf        Arduino AVR toolchain
    ii  arduino-tools-sitara-armv7l           0.0.2-4                            armhf        Arduino Sitara toolchain
    ii  arduino-webide                        0.0.34-1                           armhf        Arduino Web IDE
    ii  nginx                                 1.4.5-2arduino                     armhf        small, powerful, scalable web/proxy server
    
