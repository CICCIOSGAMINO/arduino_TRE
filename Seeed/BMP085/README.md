(NOT WORKING - IN TESTING )

Grove Barometer Sensor - Model:SEN05291P
Intro

This Grove - Barometer Sensor features a Bosch BMP085 high-accuracy chip to detect barometric pressure and temperature. It can widely measure pressure ranging from 300hPa to 1100hPa, AKA +9000m to -500m above sea level, with a super high accuracy of 0.03hPa(0.25m) in ultra-high resolution mode.The chip only accepts 1.8V to 3.6V input voltage. However, with outer circuit added, this module becomes compatible with 3.3V and 5V. Therefore, it can be used on Arduino/Seeeduino or Seeeduino Stalker without modification.It is designed to be connected directly to a micro-controller via the I2C bus.

Arduino TRE path :

Here some path for find the right things in just a second on the Arduino TRE board :

sketch ( /home/tre/Arduino )
user's libraries ( /home/tre/Arduino/libraries )
example ( /usr/src/arduino/examples )
hardware (/usr/src/arduino/hardware )
libraries (/usr/src/arduino/libraries )
Is a better choice hold the user's and arduino's libraries in differet folder.

Import the library on board

To import the library on the Arduino TRE board, you can use the IDE (not working so good in beta testing) or load the libary in the user library path (/home/tre/Arduino/libraries ).

These are the link to use/import the library for the DHT Temperature Umidity sensor of Seeed Studio system Grove Pro.

Barometer Sensor Wiky
Barometer Sensor github
Barometer Sensor github-lib
Clone the libary in /home/tre/Arduino/libraries directory to have libary in right place :

git clone github-lib

One more thing we need to do before start to use our libraries, change the file permission of the files of the library (on /libraries folder) :

chown -R tre.arduino        // or the actual user 
ls -l                       // check the permission 
Now if no errors are raised you can view your library in the Web IDE menu in > Libraries on the left of the window. And you can use the library in the Arduino sketch !
