Test the Sitara GPIO pins 
=========================

### Intro 
Testing the Sitara Pins, the pins on the Arduino TRE headers have limited current source and sink capability, so special 
care should be taken when external components are connected to the board. The following notes apply specifically to the header pins connected to the Sitara processor (lower current capability, 3.3V logic), but the same considerations are valid also for the pins connected to the AVR processor (higher current capability, 5V logic). 

### Sitara pins details

+ RGB LED The Red, Green and Blue LEDs are accessible as digital pins as 97, 98 and 99.
+ SD LED The Yellow LED (status of the SD card) is accessible as digital pin number 96.
+ PWM: Pins 100 to 103 Provide 8-bit PWM output with the analogWrite() function. The resolution of the PWM can
be changed with the analogWriteResolution() function.
+ Digital I/O: Pins 104 to 127 Each of the 23 digital pins on the Arduino TRE can be used as an input or output, using
pinMode(), digitalWrite(), and digitalRead() functions. They operate at 3.3 Volts. Each pin can provide (source) a current of 6 mA, or accept (sink) a current of 6 mA.
+ Serial: RX and TX connected to the wireless module socket
+ Serial1: RX1 and TX1
+ Serial2: RX2 and TX2
+ TWI1: SDA1 and SCL1
+ TWI2: SDA2 and SCL2 connected to the wireless module socket
+ SPI1: MOSI1, MISO1, SCK1 and SS1
+ CAN BUS: CANH, CANL, CAN5 and CGND
+ LVDS: CLK+, CLK-, Y0+, Y0-, Y1+, Y1-, Y2+ and Y2-
+ LRST: Stiara reset line (short to GND to reset the processor)
+ BAT
+ BTS
+ BSNS
+ ONOFF

### Pin Mapping (Sitara)

| Pin Name    | Mapped Pin Name  |
|-------------|------------------|
| GPIO1\_21   |  96 (YELLOW\_LED)|
| GPIO1\_22   |  97 (RED\_LED)   |
| GPIO1\_24   |  98 (GREEN\_LED) |
| GPIO1\_23   |  99 (BLU\_LED    |
| GPIO0\_22   |  100 (PWM)       | 
| GPIO0\_23   |  101 (PWM)       |
| GPIO1\_18   |  102 (PWM)       |
| GPIO1\_19   |  103 (PWM)       |
| GPIO1\_0    |  104             |   
| GPIO1\_1    |  105             |         
| GPIO1\_2    |  106             |                     
| GPIO1\_3    |  107             |                  
| GPIO1\_4    |  108             |                
| GPIO1\_5    |  109             |            
| GPIO1\_6    |  110             |  
| GPIO1\_7    |  111             |    
| GPIO2\_0    |  112             |   
| GPIO2\_4    |  113             |    
| GPIO2\_3    |  114             |     
| GPIO2\_2    |  115             |  
| GPIO0\_26   |  116             |  
| GPIO3\_18   |  117             |
| GPIO3\_19   |  118             |   
| GPIO3\_20   |  119             | 
| GPIO1\_30   |  120             |  
| GPIO1\_31   |  121             |   
| GPIO1\_12   |  122             |
| GPIO1\_13   |  123             |
| GPIO1\_14   |  124             |        
| GPIO1\_15   |  125             |       
| GPIO0\_19   |  126             |
| GPIO0\_20   |  127             |
----------------------------------


