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

You need to be confortable with the Bridge functionality because all the communications pass through them, so in the next chapters we'll try to go depth in these functions ! For all the official documentation about the bridge on the Arduino Yun (pretty the same for the Arduino TRE) here the [link][2]. 

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
    >> dropbear   4652   root    5u  inet   5652      0t0  TCP 19 ..1:47890 (ESTABLISHED)
    >> python    11888   root    4u  inet  13162      0t0  TCP localhost:6571 (LISTEN)
    >> python    11888   root    5u  inet  13163      0t0  TCP localhost:5700 (LISTEN)
    
    netstat -tulpn
    >> Active Internet connections (only servers)
    >> Proto Recv-Q Send-Q Local Address           Foreign Address   State       PID/Program name    
    >> tcp        0      0 127.0.0.1:5700          0.0.0.0:*         LISTEN      11888/python
    >> tcp        0      0 127.0.0.1:6571          0.0.0.0:*         LISTEN      11888/python
    >> tcp        0      0 0.0.0.0:80              0.0.0.0:*         LISTEN      1328/uhttpd
    >> tcp        0      0 0.0.0.0:53              0.0.0.0:*         LISTEN      1360/dnsmasq
    >> tcp        0      0 0.0.0.0:22              0.0.0.0:*         LISTEN      1321/dropbear
    >> tcp        0      0 0.0.0.0:443             0.0.0.0:*         LISTEN      1328/uhttpd
    >> netstat: /proc/net/tcp6: No such file or directory
    >> udp        0      0 0.0.0.0:53              0.0.0.0:*                     1360/dnsmasq
    >> udp        0      0 0.0.0.0:5353            0.0.0.0:*                     1366/avahi-daemon:
    
as you can see, after the sketch launche the bridge, the python listening on port 6571 and 5700 ! So now we can go to view what kind of data are in back and forward on the serial wrapped into the Bridge libraries. 





### Read the Serial 
Can be useful check the data on the Serial communication between the two processor, on the Arduino TRE like on the Arduino Yun, the two cores are connected through Serial, now we'll show how communicate through serial (important is the baud rate to set, on start-up in linux and in the c++ code on the 32u4 processor through the serial library) : 

**Sketch (send data on serial1) on Arduino Yun ** 
    
    /* Simple Skecth for send the active time in sec */ 
    long linuxBaud = 250000;

    void setup() {
      
      Serial1.begin(linuxBaud);
    
    }
    
    void loop() {
      
      Serial1.println("Active (millis):" + String(millis()/1000));
      delay(1000);
    
    }
    
**Sketch (send data on serial1) on Arduino TRE** 
    
    /* Simple Skecth for send the active time in sec */ 
    long linuxBaud = 115200;

    void setup() {
      
      Serial1.begin(linuxBaud);
    
    }
    
    void loop() {
      
      Serial1.println("Active (millis):" + String(millis()/1000));
      delay(1000);
    
    }
    
    
**Linux (read data from serial1) Arduino Yun**

    sudo cat /dev/ttyATH0 
    >> Active (sec):1
       Active (sec):2
       Active (sec):3
       Active (sec):4
       ... 
      
**Linux (read data from serial1) Arduino TRE**

    sudo cat /dev/ttyO0    
    >> Active (sec):1
       Active (sec):2
       Active (sec):3
       Active (sec):4
       ... 
       
       
Be careful with print to much data on the **Serial1** is the same port has created for laod the sketch on the 32u4 Atmel processor, so if you print to much data on the **Serial1** you get an error when you'll try to load a new sketch, to go around click the rest 32u4 button (on the right of RJ45 socket) and immediately load the new sketch ! For a very good example following the official arduino doc [here][3]. 

### Use Node.js and serialport 
serialport is a very power Node.js module to read and write from serial port, so like all others Node.js project init it and install the right dependencies : 

    cd serialtest 
    init npm 
    npm install --save serialport 
    touch app.js 
    
    // app.js 
    var SerialPort = require('serialport').SerialPort
    var s = new SerialPort('/dev/ttyO0', {baudrate:115200});

    // manage the events
    s.on('open', function(){
        console.log('Connection to /dev/ttyO0 Opened ');

        s.on('data', function(data){
                console.log('Ddt Received : ' + data);
        });
    });
    
**We've tested the ArduinoTRE serial port with different baud rate, but we've noticed that the best value to avoid problems is 115200 bits/sec ! And yes of course consider no error control algoritms are active in all those case you are going to read the bits direct from the serial port ! ** 


### Use the Bridge 
Now it's time to use the Bridge, we'll show there a simple script that use the Bridge Python libraries such as bridge.py, mailbox.py, process.py, tcp.py ... in the folder **/usr/lib/python2.7/bridge ** : 

    /*
        Simple Bridge + Mailbox Test 
    */
    #include <Bridge.h>
    
    int led_status = 13;
    int btn = 3;
    unsigned long count = 0L;
    
    void setup() {
        
        // fire the run-bridge script on Linux side 
        Bridge.begin();
        delay(1000);
        
        // init the COUNT 
        Bridge.put("COUNT", String(0));
        
    }
    
    void loop() {
        
        if (digitalRead(btn) == HIGH){
            count = count + 1;
            digitalWrite(led_status, HIGH);
            Bridge.put("COUNT",String(count));
            delay(1000);
        }else{
            digitalWrite(led_status, LOW);
        }
    }

This sketch active the Bridge, and the JSONServer on the GNU/Linux side, so for see the variable (key,value) has setted from the sketch we have, we can query the JSON service active on the port 5700 : 

    lsof -i | grep 5700 
    >> python    4889       root    5u  IPv4  38959      0t0  TCP localhost:5700 (LISTEN)
    
Ok the service is active, to read data from the JSON server with the Arduino Yun as easy as type : 

    curl http://localhost/data/get/COUNT 
    
With the Arduino TRE, we can read throuth the socket TCP active on TCP 5700, no HTTP services have bound !! 



[2]:https://blog.arduino.cc/2013/09/05/hands-on-the-arduino-yuns-bridge/
[3]:https://www.arduino.cc/en/Tutorial/YunSerialTerminal
