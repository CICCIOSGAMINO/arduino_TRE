3G - HUAWEI E303
================

###Intro 

The Huawei E303 is a Huawei HSDPA access device (modem) manufactured by Huawei and notable for using the USB interface (USB modem), the device is used for wireless Internet access using 3.5G, 3G, or 2G mobile telephony networks. It supports UMTS (including HSDPA), EDGE, GPRS and GSM.

E303 works well with Linux, as support for it was added in Linux kernel 2.6.20 (2007-02-04[2]), but there are workarounds for distributions with older kernels. The card is also supported by Vodafone Mobile Connect Card driver for Linux, and it is possible to monitor the signal strength through other Linux applications!

### System on Test
All the scripts are tested with : 

+ Arduino TRE beta testing version (T00000023)
+ Samsung microSD 8GB
+ Linux xx-K56CM 3.13.0-32-generic #57-Ubuntu SMP Tue Jul 15 03:51:08 UTC 2014 x86_64 x86_64 x86_64 GNU/Linux
+ Huawei E303 3G modem (3 Sim Card)


### Attach the Device 
Attach the device, before to attach the 3G modem and use it, test the USB hub before, on the beta testing board you need to fix some issue 
before use all the USB without problems (not in Arduino TRE production board).


### Check the USB Modem 
With all the USB active connect the 3G modem trougth USB hub, and if the USB modem is listed in the system USB device : 

    lsusb 
    
    >> Bus 001 Device 005: ID 12d1:1003 Huawei Technologies Co., Ltd. E220 HSDPA Modem / E230/E270/E870 HSDPA/HSUPA Modem
    
    ls /dev/ttyUSB* 
    
    >> get all serial devices attached to USB 
    
    /dev/ttyUSB0  /dev/ttyUSB1
    
The device is recognized, the name and the corresponded drivers match our device. If the drivers don't match the device go deep in the installation drivers process, You can use modconf to load usbserial drivers with card vendor & id as arguments. 

    
**Arduino TRE mount a Debian GNU/Linux distro and do not need to manually install the Huawei modem drivers, a lot of drivers are native implemented** 

### wvdial 
WvDial is a utility that helps in making modem-based connections to the Internet that is included in some important Linux distributions.
WvDial is a Point-to-Point Protocol dialer: it dials a modem and starts pppd in order to connect to the Internet.

When WvDial starts, it first loads its configuration from /etc/wvdial.conf and ~/.wvdialrc, which contain basic information about the modem port, speed, and init string, along with information about your ISP, such as the phone number, your user name, and your password. 


    less /etc/wvdial.conf               // and set the params 
    
    [Dialer E220]
    Modem = /dev/ttyUSB0
    Baud = 3000000
    Init1 = at+cgdcont=1,"ip","tre.it"
    Carrier Check = yes
    Dial Command = ATDT
    Phone = *99#
    Username = a
    Password = a
    Stupid Mode = yes
    Auto Reconnect = yes


    less /etc/ppp/peers/wvdial          // other params 
    
Now that the wvdial 'Dial E220' is setted on ppp0 interface, launch the interface : 

    wvdial E220                 // launch the E220 interface on ppp0 

### Check the ppp0 
Check the interface ppp0 just setted on Huawei E220 modem with the ifconfig command: 
    
    ip addr show 
    
    or 
    
    ifconfig

    eth0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UP qlen 1000
    link/ether 1c:ba:8c:a2:e8:e3 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.107/24 brd 192.168.0.255 scope global eth0
    inet6 fe80::1eba:8cff:fea2:e8e3/64 scope link 
    valid_lft forever preferred_lft forever

    ppp0: <POINTOPOINT,MULTICAST,NOARP,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast state UNKNOWN qlen 3
    link/ppp 
    inet 10.86.19.73 peer 10.64.64.64/32 scope global ppp0
    
The ppp0 interface is up with these details show us, This contains more information. It shows all our addresses, and to which cards they belong. ’inet’ stands for Internet (IPv4). There are lots of other address families, but these don’t concern us right now.

Let’s examine eth0 somewhat closer. It says that it is related to the inet address ’192.168.0.107/24’. What does this mean? The /24 stands for the number of bits that are in the Network Address. There are 32 bits, so we have 8 bits left that are part of our network. The first 24 bits of 192.168.0.107 correspond to 192.168.0.0, our Network Address, and our netmask is 255.255.255.0.

With ppp0, the same concept goes, though the numbers are different. Its address is 10.86.19.73,
without a subnet mask. This means that we have a point-to-point connection and that every address, with
the exception of 10.86.19.73, is remote. There is more information, however. It tells us that on the
other side of the link there is, yet again, only one address, 10.64.64.64. The /32 tells us that there are no
’network bits’.

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
