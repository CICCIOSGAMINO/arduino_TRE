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

    
    
[    0.219761] Serial: 8250/16550 driver, 4 ports, IRQ sharing enabled
[    0.222452] 44e09000.serial: ttyO0 at MMIO 0x44e09000 (irq = 88) is a OMAP UART0
[    0.223354] 48022000.serial: ttyO1 at MMIO 0x48022000 (irq = 89) is a OMAP UART1
[    0.224205] 48024000.serial: ttyO2 at MMIO 0x48024000 (irq = 90) is a OMAP UART2
[    0.225133] 481a8000.serial: ttyO4 at MMIO 0x481a8000 (irq = 61) is a OMAP UART4
