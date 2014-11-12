GSM
===
[TOC]

## Intro 
The Arduino GSM Shield connects your Arduino to the internet using the GPRS wireless network. Just plug this module onto your Arduino board, plug in a SIM card from an operator offering GPRS coverage and follow a few simple instructions to start controlling your world through the internet. You can also make/receive voice calls (you will need an external speaker and microphone circuit) and send/receive SMS messages.

![GSM Shield](http://arduino.cc/en/uploads/Main/ArduinoGSMShield_Front.jpg)

For the official Arduino documentations go [here][1]. 

### On Tre 
To use this shield on Arduino Tre (beta), download the library (this library have some minor update, due to use on the Arduino Tre and Yun) : 

Download [Library][2]

### Install the Library 
To install the library copy the unzip context in the Arduino user libraries folder and restart the IDE, or the board in case of Arduino Tre : 

    /home/Arduino/libraries 
    
### Power requirements
It is recommended that the board be powered with an external power supply that can provide between 700mA and 1000mA. **Powering an Arduino and the GSM shield from a USB connection is not recommended, as USB cannot provide the required current for when the modem is in heavy use**.
The modem can pull up to 2A of current at peak usage, which can occur during data transmission. This current is provided through the large orange capacitor on the board's surface.
On board indicators

The shield contains a number of status LEDs:

+ On: shows the Shield gets power.
+ Status: turns on to when the modem is powered and data is being transferred to/from the GSM/GPRS network.
+ Net: blinks when the modem is communicating with the radio network.


[1]:http://arduino.cc/en/Main/ArduinoGSMShield
[2]:https://www.dropbox.com/s/hi4vs5nrfzjf9cm/GSM3.zip?dl=0
