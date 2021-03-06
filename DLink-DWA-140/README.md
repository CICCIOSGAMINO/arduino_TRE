Wify - DLink DWA-140
====================

 ![DLink DWA-140][2]

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


### System


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
        

Ok, the interface is mapped, now it's time to up the interface and check the network params : 
          
    
    ifconfig wlan0 up       // up the interface wlan0 more power than ifup wlan0
    ip addr show            // show interfaces details 
    
    5: wlan0: <NO-CARRIER,BROADCAST,MULTICAST,UP> mtu 1500 qdisc mq state DOWN qlen 1000
    link/ether 1c:af:f7:66:c9:e0 brd ff:ff:ff:ff:ff:ff
    
    
### config 


It's time to config the wlan0 interface with the network details to connect, if WPA network is active a wpa_supplicant 
setting is request(in the following section) : 

    iwlist wlan0 scanning 
    
    wlan0     Scan completed :
          Cell 01 - Address: B8:A3:88:A2:88:88
                    Channel:13
                    Frequency:2.472 GHz (Channel 13)
                    Quality=67/70  Signal level=-43 dBm  
                    Encryption key:off
                    ESSID:"MY-NET"
                    Bit Rates:1 Mb/s; 2 Mb/s; 5.5 Mb/s; 11 Mb/s; 9 Mb/s
                              18 Mb/s; 36 Mb/s; 54 Mb/s
                    Bit Rates:6 Mb/s; 12 Mb/s; 24 Mb/s; 48 Mb/s
                    Mode:Master
                    
Other useful command to run on the wireless card to check the function mode for working with them is, the 
iwlist command -> Get more detailed wireless information from a wireless interface
: 

    $ iwlist 
    
    Usage: iwlist [interface] scanning [essid NNN] [last]
              [interface] frequency 
              [interface] channel 
              [interface] bitrate 
              [interface] rate 
              [interface] encryption 
              [interface] keys 
              [interface] power 
              [interface] txpower 
              [interface] retry 
              [interface] ap 
              [interface] accesspoints 
              [interface] peers 
              [interface] event 
              [interface] auth 
              [interface] wpakeys 
              [interface] genie 
              [interface] modulation


Now edit **/etc/network/interfaces**. The required configuration is much dependent on your particular setup. See the following example to get an idea of how it works : 

Simple for a free "FREE-NET" net, with no passw and dhcp active : 

    # SETTING - NET 
    auto wlan0
    iface wlan0 inet dhcp
        wireless-essid FREE-NET
        wireless-mode managed
        
    ifconfig wlan0 up        // more low level than ifup 
    
or 

    ifdown wlan0
    ifup wlan0 
    

Check the wlan0 network details : 

    ip addr show 
    
    4: wlan0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc mq state UP qlen 1000
    link/ether 1c:af:f7:66:c9:e0 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.106/24 brd 192.168.0.255 scope global wlan0
    inet6 fe80::1eaf:f7ff:fe66:c9e0/64 scope link 
       valid_lft forever preferred_lft forever
       
Seems to be all good, the network wlan0 get the rigth address from the gateway ! 

    
    
### utility


    /etc/init.d/networking restart              // restart all the net-interfaces (deprecated)
    ifconfig wlan0 up                           // up the interface wlan0  more low level than ifup 
    ifup wlan0                                  // up the wlan0 
    ifdown wlan0                                // down the wlan0
    

### DNS


Check if the DNS server address are setted/resolved by the interface : 

    /etc/resolv.conf
    
    nameserver 212.29.129.3
    nameserver 8.8.8.8
          
### Ping     
Ping from the ppp0 interface to check if the interface (driver + config) works: 

    ping -I wlan0 12.36.21.2
    
    PING www.google.com (173.194.70.106) from 10.86.19.73 wlan0: 56(84) bytes of data.
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=2 ttl=45 time=1632 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=1 ttl=45 time=2634 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=3 ttl=45 time=642 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=4 ttl=45 time=162 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=5 ttl=45 time=161 ms
    64 bytes from fa-in-f106.1e100.net (173.194.70.106): icmp_req=6 ttl=45 time=161 ms
    
If ping operation on wlan0 interface goes ok your DLink dongle is working ! 

    
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


### Conclusion 
At the end is a good wify dongle to use with the debian system like the Arduino TRE, 100% with all the function active with no problems ! 

### more stuff 
Check the official Debian Wify [guide][1]

[1]: https://wiki.debian.org/WiFi/HowToUse
[2]: http://www.dlink.com/-/media/Images/Products/DWA/140/DWA%20140%20Left.png
