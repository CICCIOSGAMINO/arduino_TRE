Wify - DLink DWA-140
====================

### Intro 

The D-Link® RangeBooster N® USB Adapter (DWA-140) is a Wireless N compliant adapter for your desktop or notebook PC.
It delivers up to 12x faster speeds1and 4x farther range1 than an previous-generation network while staying backward
compatible with Wireless G networks. Once connected, you can share a high-speed Internet connection, photos, files,
music, printers, and more.

The DWA-140 is powered by RangeBooster N technology to provide superb wireless performance in the home or office.
Connect to a RangeBooster N Router (DIR-628) and experience smooth Internet phone calls (VoIP), responsive network
gaming, secure Web surfing, faster file transfers, enhanced audio streaming, and greater wireless coverage in larger
homes and offices1. The DWA-140 supports WPA™ and WPA2™ encryption and includes a Wi-Fi Protected Setup™ (WPS) Push
Button to easily connect to a wireless network.


### System on Test

All the scripts are tested with : 

+ Arduino TRE beta testing version (T00000023)
+ Samsung microSD 8GB
+ Linux xx-K56CM 3.13.0-32-generic #57-Ubuntu SMP Tue Jul 15 03:51:08 UTC 2014 x86_64 x86_64 x86_64 GNU/Linux
+ Wify Dongle DLink DWA-140


### Attach the Device 

Plug-in the device and start to check how the Debian system probe it, check if errors raised  : 

    dmesg -c 
    dmesg 


### Check the Dongle

With all the USB active connect the 3G modem trougth USB hub, and if the USB modem is listed in the system USB device : 

    lsusb 
    
    >> Bus 001 Device 003: ID 07d1:3c0a D-Link System DWA-140 RangeBooster N Adapter(rev.B2) [Ralink RT3072]
    

    
**Arduino TRE mount a Debian GNU/Linux distro and do not need to manually install the Huawei modem drivers, a lot of drivers are native implemented** 

### Check the Interface 

First of all check if the interfce is retrived (wlan0 or somethings else) if the interface is finded the driver and the device are mapped, after that you can up the interface : 

    iwconfig            // get the wify interfaces 
    
    wlan0     IEEE 802.11bgn  ESSID:off/any  
        Mode:Managed  Access Point: Not-Associated   Tx-Power=20 dBm   
        Retry  long limit:7   RTS thr:off   Fragment thr:off
        Encryption key:off
        Power Management:on
          
    
    ifconfig wlan0 up       // up the interface wlan0


### DNS
Check if the DNS server address are setted/resolved by the interface : 

    /etc/resolv.conf
    
    nameserver 212.29.129.3
    nameserver 8.8.8.8
          
### Ping     
Ping from the ppp0 interface to check if the interface (driver + config) works: 

    ping -I ppp0 12.36.21.2
    
    PING www.google.com (173.194.70.106) from 10.86.19.73 ppp0: 56(84) bytes of data.
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=2 ttl=45 time=1632 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=1 ttl=45 time=2634 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=3 ttl=45 time=642 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=4 ttl=45 time=162 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=5 ttl=45 time=161 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=6 ttl=45 time=161 ms
    
If ping operation on ppp0 interface goes ok your Huawei modem is working ! 

    
### Check the situation from Remote 
We have a natting problem on the 3G propetary network to reach the device from outside the 3G network back communication with the board, try the sim for the internet of things. 

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


### more stuff 
Check the official Debian E220 [guide][1]

[1]: https://wiki.debian.org/Huawei/E220
