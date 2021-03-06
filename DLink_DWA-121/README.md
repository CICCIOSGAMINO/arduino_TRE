DLink DWA-121 Wireless N 150 Pico USB
=====================================

### PROBLEM TO FIX (Arduino TRE Beta), discontinued working !! 

![DLink DWA-121 N150][3]

### Intro 

Simple DLink Wireless dongle to get the wireless N 150 connectivity to Arduino TRE board, to set the wireless connection you can use the
serial(usb0 interface) and the ethernet(eth0 interface) ports. 

Connect to a high-speed wireless network with the D-Link® Wireless N 150 Pico USB Adapter (DWA-121). The DWA-121 uses Wireless N 150 technology,
which provides increased speed and range over the Wireless G, giving you a faster, more reliable wireless connection. Wireless N 150 is an excellent
solution for everyday activities such as transferring files, browsing the Internet, and downloading multimedia.

### Connect the Dongle 

First of all connect the Wify dongle in one of the USB ports (no matter which one) and check is the USB driver for the Wify dongle is loaded (a lot of drivers are present right now in debian environment):

    lsusb
    dmesg -c 
    dmesg
  
If info like that are received the wify dongle's driver is loaded right : 

    Bus 001 Device 002: ID 0424:2514 Standard Microsystems Corp. USB 2.0 Hub
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    Bus 002 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    **Bus 001 Device 003: ID 2001:3308 D-Link Corp. DWA-121 802.11n Wireless N 150 Pico Adapter [Realtek RTL8188CUS]**
  
Non-free drivers and firmware are produced by companies refusing or unable to cooperate with the free software community. With non-free drivers and firmware support is often unavailable or severely strained. For instance features are often left out, bugs go unfixed, and what support does exist from the manufacture is fleeting.

> By encouraging good social practices the community is able to support end-users. Complex installation procedures are no longer required and support continues long after a product has been discontinued.

> currently there are only a few modern wifi chipsets readily available that work with free software systems. For USB wifi devices this list includes the Realtek RTL8187B chipset (802.11G) and the Atheros AR9170 chipset (802.11N). For Mini PCIe all cards with an Atheros chipset are supported.

> Wifi has always been a problem for free software users. USB Wifi cards are becoming less free. With the older 802.11G standard many USB wifi cards had free drivers and did not require non-free firmware. With 802.11N there is only one chipset on the market from Atheros which is completely free.

### Config

Continuing on, a WiFi interface is an Ethernet interface which also provides WiFi-specific configuration parameters. These parameters are controlled using the **iwconfig** program.

    iwconfig 
    wlan0     IEEE 802.11bgn  ESSID:off/any  Mode:Managed  Access Point: Not-Associated   Tx-Power=0 dBm  Retry  long limit:7   RTS thr=2347 B   Fragment thr:off Encryption key:off Power Management:on
    lo        no wireless extensions
    eth0      no wireless extensions
    usb0      no wireless extensions
    can0      no wireless extensions
  
  
At first you have the wlan0 interface available, now you need to configure the wify params to get access to the wify network. Wireless network interface configuration can be performed using a connection manager (such as NetworkManager) or through Debian's **/etc/network/interfaces** file with a special purpose utility (such as wpa_supplicant). 

Start with some base command to keep in mind to manage the network interfaces, to restart / stop all the network 
services : 

    sudo /etc/init.d/networking restart   // restart the net interface
    sudo /etc/init.d/networking start
    sudo /etc/init.d/networking stop
    
to restart / stop only one interface at time : 

    sudo ifup wlan0 
    sudo ifdown eth0 
    
or : 

    sudo ifconfig wlan0 up 
    sudo ifconfig eth0 down 
    
Scan the network available by wlan0 interface : 

    iwlist wlan0 scan  
    
Set the /etc/network/interfaces : 

    auto wlan0
    iface wlan0 inet dhcp
        wpa-ssid mynetworkname
        wpa-psk mysecretpassphrase
    
Uo the interface wlan0 

    ifconfig wlan0 up       // up the interface more low level than ifup 
    ifconfig wlan0 down     // down the interface more low levelt than ifdown 
    
On the Debian environment is better use these commands than the ifup / ifdown command ! 

### DNS
Check if the DNS server address are setted/resolved by the interface : 

    /etc/resolv.conf
    
    nameserver 212.29.129.3
    nameserver 8.8.8.8
    
### Config with wpa_supplicant
If the network is protected by a WPA-PSK and WPA2-PSK you need to use the **wpasupplicant** package in order to get access to a WPA/WPA2 network : 

    apt-get install wpasupplicant 
    
Now you are ready to connect to a secured network, first step ->  Use the WPA passphrase to calculate the correct WPA PSK hash for your SSID by altering the following example : 

    wpa_passphrase myssid my_secret_passphrase >> /etc/wpa_supplicant/wpa_supplicant.conf
    
If you don't put the passphrase on the command line, it will be prompted for. The above command gives the output:
    
    network={
	    ssid="TP-MyNet"
	    #psk="WIPASSW"
	    psk=525eeca3c20ea31a57df9341ed57176e2701e1747e775dcf7e2592771fe424a1
    }

The second step is to run wpa_supplicant with the new configuration file : 

    $ sudo wpa_supplicant -B -D wext -i wlan0 -c /etc/wpa_supplicant/wpa_supplicant.conf
    
-B means run wpa_supplicant in the background.
-D specifies the wireless driver. wext is the generic driver.
-c specifies the path for the configuration file.

Use the iw command to verify that you are indeed connected to the SSID.

TODO

  



### Info

You can collects more info at the debian wifi [resource][1] & [HowToUse][2]

**Lot of PROBLEMS in the Arduino Tre Beta with the default wify dongle** sometimes working sometimes don't !! 

[1]: https://wiki.debian.org/WiFi
[2]: https://wiki.debian.org/WiFi/HowToUse
[3]: http://www.dlink.com/-/media/Images/Products/DWA/121/DWA%20121%20Left.png
