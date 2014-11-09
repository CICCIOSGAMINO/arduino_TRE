OneWire - Arduino Tre 
=====================
[TOC]

## Intro
The main idea is that all the library can be used for the Arduino UNO can be used for the Arduino TRE too, 
for all the main library is right, one of them is the OneWire library. For the Official Arduino 
reference to the material go [here][1].

OneWire lets you access 1-wire devices made by Maxim/Dallas, such as temperature
sensors and ibutton secure memory. For temperature sensors, the DallasTemperature
library can be used with this library :

Download the [library][2]

### Hardware Requirements
OneWire requires a single 4.7K pullup resistor, connected between the pin and +5
volts. Then just connect each 1-wire device to the pin and ground. Some 1-wire
devices can also connect to power, or get their power from the signal wire.
Please refer to the specifications for the 1-wire devices you are using

## Install the Library 
To install the library on the Arduino Tre download the Library and copy the unzip folder in the 
user library (the path that you set in the IDE for the user's sketch and the libraries) after 
that try to restart the IDE and check if the examples of the new library are present in the 
examples folder of the IDE, if you can find the example all work and now you are able to 
use the library in the sketchs. 

### Basic Usage
Here the simple functions you can use with the OneWire library :

    OneWire myWire(pin)
    
Create the OneWire object, using a specific pin. Even though you can connect
many 1 wire devices to the same pin, if you have a large number, smaller groups
each on their own pin can help isolate wiring problems. You can create multiple
OneWire objects, one for each pin :

    myWire.search(addrArray)

Search for the next device. The addrArray is an 8 byte array. If a device is found,
addrArray is filled with the device's address and true is returned. If no more
devices are found, false is returned.

    myWire.reset_search()

Begin a new search. The next use of search will begin at the first device.

    myWire.reset()

Reset the 1-wire bus. Usually this is needed before communicating with any device.

    myWire.select(addrArray)

Select a device based on its address. After a reset, this is needed to choose
which device you will use, and then all communication will be with that device,
until another reset.

    myWire.skip()

Skip the device selection. This only works if you have a single device, but you
can avoid searching and use this to immediatly access your device.

    myWire.write(num);

Write a byte.

    myWire.write(num, 1);

Write a byte, and leave power applied to the 1 wire bus.

    myWire.read()

Read a byte.

    myWire.crc8(dataArray, length)

Compute a CRC check on an array of data.

### Powering OneWire devices
The chip can be powered two ways. One (the "parasitic" option) means that only 
two wires need go to the chip. The other may, in some cases, give more reliable 
operation (parasitic often works well), as an extra wire carrying the power for 
the chip is involved. 

For getting started, especially if your chip is within 20 feet of your Arduino, 
the parasitic option is probably fine. The code below works for either option, 
anyway.

#### Parasite power mode
When operating in parasite power mode, only two wires are required: one data wire, 
and ground. At the master, a 4.7k pull-up resistor must be connected to the 1-wire 
bus. When the line is in a "high" state, the device pulls current to charge an 
internal capacitor.

This current is usually very small, but may go as high as 1.5 mA when doing a 
temperature conversion or writing EEPROM. When a slave device is performing one 
these operations, the bus master must keep the bus pulled high to provide power 
until the operation completes; 

**a delay of 750ms is required for a DS18S20 temperature conversion. The master 
can't do anything during this time, like issuing commands to other devices, or 
polling for the slave's operation to be completed**. 

To support this, the OneWire library makes it possible to have the bus held high 
after the data is written.

#### Normal (external supply) mode
With an external supply, three wires are required: the bus wire, ground, and power. 
The 4.7k pull-up resistor is still required on the bus wire. As the bus is free 
for data transfer, the microcontroller can continually poll the state of a device 
doing a conversion. This way, a conversion request can finish as soon as the device 
reports being done, as opposed to having to wait 750ms in "parasite" power mode.

Note on resistors:
For larger networks, you can try smaller resistors.
The ATmega328/168 datasheet indicates starting at 1k6 and a number of users have 
found smaller to work better on larger networks.

### Addressing a OneWire device
Each 1-Wire device contains a unique 64-bit (8byte) 'rom' code, consisting of an 8-bit 
family code, a 48-bit serial number, and an 8-bit CRC. The CRC is used to verify 
the integrity of the data. 

For example, the sample code, below, checks if the device being addressed is a 
DS18S20 temperature sensor by checking for its family code, 0x10. To use the 
sample code with the newer DS18B20 sensor, you'd check for a family code of 0x28, 
instead, and for the DS1822 you'd check for 0x22.

**Before sending a command to a slave device, the master must first select that 
device using its rom code. Alternatively, you can address a command to all slave 
devices by issuing a 'skip rom' command (0x, instead. This is only safe if you 
are sure there is only one slave device on the MicroLAN**. 

for commands that don't elicit a response from the slave devices - data collision 
will occur if data is requested from more than one slave.

Please see the DS18S20 or DS18B20 datasheets for more detailed information.

### Reading a OneWire device
Reading a 1Wire device requires multiple steps. The details are device-dependent, in that devices are capable of reporting different measurables. The popular DS18B20, for example, reads and reports temperature, while a DS2438 reads voltage, current, and temperature.

The two main steps of a read process are:

#### Conversion
A command is issued to the device to perform an internal conversion operation. With a DS18B20, this is the Ox44 byte command. In the OneWire library, this is issued as ds.write(0x44), where ds is an instance of the OneWire class. 

After this command is issued, the device reads the internal ADC,and when this process is complete, it copies the data into the Scratchpad registers. This length of this conversion process varies depending on the resolution and is listed in the device datasheet. a DS18B20 takes from 94 (9-bit resolution) to 750ms (12-bit resolution) to convert temperature (c.f. DS18B20 Datasheet). While the conversion is taking place, the device may be polled, e.g. using in the ds.read() command in OneWire, to see if it has successfully performed a conversion.

#### Read Scratchpad
Once the data has been converted, it is copied into the Scratchpad memory,where it may be read. Note that the Scratchpad may be read at any time without a conversion command to recall the most previous reading, as well as the resolution of the device and other device-dependent configuration options.

### Asynchronous vs. Synchronous read/write
The majority of existing code for 1Wire devices, particularly that written for Arduino, uses a very basic "Convert, Wait, Read" algorithm, even for multiple devices. This creates several problems:

#### Program timing for other functions
Arguably the biggest problem with using the above methodology is that unless threading measures are undertaken, the device must sit (hang) and wait for the conversion to take place if a hardcoded wait time is included. This presents a serious problem if other timed processes exist, and even if they don't -- many programs wait for user input, process data, and perform many other functions that cannot be put on hold for the time necessary for a temperature conversion process. As noted above and below, a 12-bit conversion process for a DS18B20 can take as long as 750ms. There is simply no reason to use this method except laziness. One can issue a conversion command and return later to pick up the measurement with a Read Scratchpad command.

#### Scaling for Poll Speed with multiple devices
Another major problem with the "Convert, Wait, Read" method is that it scales very poorly, and for no good reason. All conversion commands can be issued in series (or simultaneously, by issuing a Skip ROM and then Convert command), and the result can then be read back in succession. See discussion [here][4].

#### Adjustment of wait time to required conversion time
This factor is really just an artifact of inefficient coding for 1Wire read processes. Typically, at best code is written with the maximum required conversion time listed in the data sheet, and often with a GENEROUS overhead on top of this. In the example below, for example, 1000ms is given, while the datasheet lists 750ms as the maximum conversion time, and typical conversion takes please is 625ms or less. Furthermore, the value should be adjusted for the resolution that is currently being polled. A 9-bit conversion, for example, will take 94ms or less, and waiting for 1000ms simply doesn't make sense. As noted above, the most efficient way to poll is the use a read time slot to poll the device. In this fashion one can know exactly when the result is ready and pick it up immediately.

For discussion and code examples on this topic, please go [here].


[1]:http://playground.arduino.cc/Learning/OneWire
[2]:http://www.pjrc.com/teensy/arduino_libraries/OneWire.zip
[3]:http://www.cupidcontrols.com/2014/10/moteino-arduino-and-1wire-optimize-your-read-for-speed/
[4]:http://interfaceinnovations.org/onewireoptimization.html
