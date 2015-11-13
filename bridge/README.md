Bridge 
======
[TOC]

## Intro 
the bridge is the heart of the communication between the Sitara Core and the ATmega32u4 chip, the library  
is written in python language for the Sitara side and C++ for the ATmel side. The python source can be reach in the Arduino TRE in the folder : 

    /usr/lib/python2.7/bridge
    
And the C++ Bridge library can be found in the Arduino IDE libraries folder. Ok this works for the Arduino Yun 
for example, the Yun load the code from the IDE : 

    <Arduin IDE>/libraries/Bridge/src 
    
The same for the Arduino TRE, you can find the C++ Bridge library in the folder : 

    TODO 
    
### Schema 
Here the schema how it works the Bridge between the two core of Arduino TRE, the schema is copied from the 
Arduino Yun schema : 

![Bridge Schema](https://www.arduino.cc/en/uploads/Main/BridgeInShort.png)
    
Before start go deep in the Bridge library we can check is the the bridge process is up, the process is activate 
at the system boot. 

### Bridge Library 
The bridge library on both the seide of the board (Sitara and Atmel) offers the following interfaces : 

+ Process : Can launch process on the Linux processor (eg shell scripts) and read their outputs
+ Console : Replace the Serial communication library, as i can telnet to the console to interact to sketch over the network, or dedug the sketch output
+ FileIO : Interface to Linux file system, used to read/write file on SD and other storage in the file system
+ HTTPClient : creates an HTTP Client on Linux 
+ Mailbox : is a sessionless interface to a volatile key/value store.
+ YunClient : emulates a TCP connection to an arbitrary host/port via the bridge.
+ YunServer : Arduino-based HTTP server

![Bridge detailed schema](https://www.arduino.cc/en/uploads/Main/BridgeInShort.png)

