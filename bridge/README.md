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
    


### Bridge Library 
The bridge library on both the seide of the board (Sitara and Atmel) offers the following interfaces : 

+ Process : Can launch process on the Linux processor (eg shell scripts) and read their outputs
+ Console : Replace the Serial communication library, as i can telnet to the console to interact to sketch over the network, or dedug the sketch output
+ FileIO : Interface to Linux file system, used to read/write file on SD and other storage in the file system
+ HTTPClient : creates an HTTP Client on Linux 
+ Mailbox : is a sessionless interface to a volatile key/value store.
+ YunClient : emulates a TCP connection to an arbitrary host/port via the bridge.
+ YunServer : Arduino-based HTTP server

![Bridge detailed schema](http://googledrive.com/host/0B81i049MUE-9fjV6WkIxQXNQZWRLYzdqSWl2RkJ6MjZPMFJCNGVYVzlLT1lGRkxQTGJmSjQ/schema/arduino-bridge.png)

You need to be confortable with the Bridge functionality because all the communications pass through them, so in the next chapters we'll try to go depth in these functions ! 

### Bridge Active
As soon as your Arduino sketch uses one of the Bridge classes, the board (Atmel 32u4) invokes run-bridge (/usr/bin) via serial on the Linux side. Console also uses bridge, as do FileIO, Mailbox etc. So **run-bridge** is a shell script which invokes python bridge.py from /usr/lib/python2.7/bridge. 

Check the process active on the TCP port : 

    lsof -i 
    >> dropbear   1321   root    3u  inet   1922      0t0  TCP *:ssh (LISTEN)
    >> uhttpd     1328   root    4u  inet   1941      0t0  TCP *:www (LISTEN)
    >> uhttpd     1328   root    5u  inet   1943      0t0  TCP *:https (LISTEN)
    >> dnsmasq    1360 nobody    4u  inet   2010      0t0  UDP *:domain 
    >> dnsmasq    1360 nobody    5u  inet   2011      0t0  TCP *:domain (LISTEN)
    >> avahi-dae  1366 nobody   12u  inet   2055      0t0  UDP *:mdns 
    >> dropbear   4652   root    5u  inet   5652      0t0  TCP 192.168.1.108:ssh->192.168.1.101:47890 (ESTABLISHED)
    >> python    11888   root    4u  inet  13162      0t0  TCP localhost:6571 (LISTEN)
    >> python    11888   root    5u  inet  13163      0t0  TCP localhost:5700 (LISTEN)
    
as you can see, after the sketch launche the bridge, the python listening on port 6571 and 5700 ! So now we can go to view what kind of data are in back and forward on the serial ! 





### Mailbox FileIO
For example, FileIO instructs bridge to create a file by sending an Fx command, where x is the mode with which to open the file (r, w, a). Command g performs a write() via the bridge, s does a seek(2), f a close(2), etc. The Mailbox class also uses bridge with different commands (m is readMessage(), M is writeMessage(), J is writeJSON()).

Be that as it may, the following small sketch (Arduino side) sends a bit of data to Linino (the OpenWRT/Linux portion of the board) every 200ms:

