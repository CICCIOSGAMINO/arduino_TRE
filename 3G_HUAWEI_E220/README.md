3G - HUAWEI E220
================

###Intro 
The Huawei E220 is a Huawei HSDPA access device (modem) manufactured by Huawei and notable for using the USB interface (USB modem), the device is used for wireless Internet access using 3.5G, 3G, or 2G mobile telephony networks. It supports UMTS (including HSDPA), EDGE, GPRS and GSM.

E220 works well with Linux, as support for it was added in Linux kernel 2.6.20 (2007-02-04[2]), but there are workarounds for distributions with older kernels. The card is also supported by Vodafone Mobile Connect Card driver for Linux, and it is possible to monitor the signal strength through other Linux applications.

### Attach the Device 
Attach the device,

### Check the USB Modem 

    lsusb 
    
    >> Bus 001 Device 005: ID 12d1:1003 Huawei Technologies Co., Ltd. E220 HSDPA Modem / E230/E270/E870 HSDPA/HSUPA Modem
    
Modem Huawaei E220 ha codice 12d1:1003, you can check in the file ... TODO ... if the 



less /etc/wvdial.conf 

less /etc/ppp/peers/wvdial  ??? 

per lanciare il interfaccia ppp0 wvdial E220

### Check the ppp0 
Check the interface ppp0 just setted on Huawei E220 modem with the ifconfig command: 
    
    ifconfig

    ppp0    Link encap:Point-to-Point Protocol  
            inet addr:10.124.8.42  P-t-P:10.64.64.64 Mask:255.255.255.255
            UP POINTOPOINT RUNNING NOARP MULTICAST  MTU:1500  Metric:1
            RX packets:11 errors:0 dropped:0 overruns:0 frame:0
            TX packets:12 errors:0 dropped:0 overruns:0 carrier:0
            collisions:0 txqueuelen:3 
            RX bytes:242 (242.0 B)  TX bytes:341 (341.0 B)
            
The ppp0 interface work, Point to Point protocol activated with the IP address 
### DNS
Check if the DNS server address are setted: 

    /etc/resolv.conf
    
    nameserver 212.29.129.3
    nameserver 8.8.8.8
          
### Ping     
Ping from the ppp0 interface to check if the interface (driver + config) works: 

    ping -I ppp0 12.36.21.2
    
    
### Check the situation from Remote 
We have a natting problem on the 3G propetary network to back communication with the board, try the sim for the internet of things. 

### USB hot plug temporary fix (only in Arduino TRE beta)
We are now working on a fix for the USB hot plug issue, but it’s not active by default because we are investigating on an issue: if a device is quickly plugged/unplagged or if a connected device reenumerates (e.g. when programming an external Arduino Leonardo), the USB port or the entire board get unstable. 

How to enable the fix Open a shell terminal, login as root  and run the following commands: 

    mv /etc/init.d/boot_scripts.sh /root/USBTemporaryFix/boot_scripts.sh.BAK 
    mv /boot/uImage /root/USBTemporaryFix/uImage.BAK 
    cp /root/USBTemporaryFix/boot_scripts.sh /etc/init.d/boot_scripts.sh 
    cp /root/USBTemporaryFix/uImage /boot/uImage 
    chmod a+x /etc/init.d/boot_scripts.sh 
    poweroff 
    
When the board is powerd on again the fix is active. How to disable the fix. Open a shell terminal, login as root  and run the following commands:

    mv /root/USBTemporaryFix/boot_scripts.sh.BAK /etc/init.d/boot_scripts.sh  
    mv /root/USBTemporaryFix/uImage.BAK /boot/uImage 
    chmod a+x /etc/init.d/boot_scripts.sh 
    poweroff 
    
When the board is powerd on again the fix is not active anymore.
