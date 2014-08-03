Grove Temperature & Umidity Sensor- DHT 
==========================================

### Intro 

Go pro in temperature and relative humidity measuremnt applications with this Grove gadget. This is a powerful
sister version of our Grove - Temperature and Humidity Sensor. It has more complete and accurate performance than
the basic version. The detecting range of this sensor is 5% RH - 99% RH, and -40°C - 80°C. And its accuracy
satisfyingly reaches up to 2% RH and 0.5°C. A professional choice for applications that have relatively strict
requirements.

### Arduino TRE path : 

Here some path for find the right things in just a second on the Arduino TRE board  : 

+ sketch ( /home/tre/Arduino ) 
+ user's libraries ( /home/tre/Arduino/libraries )
+ example ( /usr/src/arduino/examples )
+ hardware (/usr/src/arduino/hardware )
+ libraries (/usr/src/arduino/libraries ) 

Is a better choice hold the user's and arduino's libraries in differet folder. 

### Import the library on board

To import the library on the Arduino TRE board, you can use the IDE (not working so good in beta testing) or load the 
libary in the user library path (/home/tre/Arduino/libraries ). 

These are the link to use/import the library for the DHT Temperature Umidity sensor of Seeed Studio system Grove Pro. 

+ DHT Sensor [Wiky][1]
+ DHT Sensor [github][2]
+ DHT Sensor [github-lib][3]


Clone the libary in /home/tre/Arduino/libraries directory to have libary in right place :

  git clone [github-lib][3] 
  
One more thing we need to do before start to use our libraries, change the file permission of the files of the library (on /libraries folder) : 

    chown -R tre.arduino        // or the actual user 
    ls -l                       // check the permission 
    
Now if no errors are raised you can view your library in the Web IDE menu in > Libraries on the left of the window. And 
you can use the library in the Arduino sketch. 






[1]: http://www.seeedstudio.com/wiki/Grove_-_Temperature_and_Humidity_Sensor
[2]: https://github.com/CICCIOSGAMINO/Grove_Temperature_And_Humidity_Sensor
[3]: https://github.com/CICCIOSGAMINO/Grove_Temperature_And_Humidity_Sensor.git


