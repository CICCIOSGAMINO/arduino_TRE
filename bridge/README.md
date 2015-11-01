Bridge 
======
[TOC]

## Intro 
the bridge is the heart of the communication between the Sitara Core and the ATmega32u4 chip, the librari 
is written in python language and can be reach in the Arduino TRE in the folder : 

    /usr/lib/python2.7/bridge
    
Before start go deep in the Bridge library we can check is the the bridge process is up, the process is activate 
at the system boot. 

    
    
[    0.219761] Serial: 8250/16550 driver, 4 ports, IRQ sharing enabled
[    0.222452] 44e09000.serial: ttyO0 at MMIO 0x44e09000 (irq = 88) is a OMAP UART0
[    0.223354] 48022000.serial: ttyO1 at MMIO 0x48022000 (irq = 89) is a OMAP UART1
[    0.224205] 48024000.serial: ttyO2 at MMIO 0x48024000 (irq = 90) is a OMAP UART2
[    0.225133] 481a8000.serial: ttyO4 at MMIO 0x481a8000 (irq = 61) is a OMAP UART4
