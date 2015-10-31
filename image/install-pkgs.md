Install/Manage Pkg
==================
[TOC]

## Intro 
For some projects maybe you need to in stall other packages onboard the Debian OS, you need to 
manage the packets manager technology, in this case, Arduino Tre (arduinotre-debian-2014-12-01-2222-8gb.img.xz) 
mount a Debian 

### Info 
To get all the info you need about the hardware, system, etc you can install inxi tool and have all the information 
you need with a simple command : 

    echo 'deb http://ppa.launchpad.net/unit193/inxi/ubuntu trusty main' > /etc/apt/sources.list
    sudo apt-get install inxi 
    
    inxi -Fx
    
    >> System:    Host: TRE Kernel: 3.8.13+ armv7l (32 bit gcc: 4.7.2) Console: tty 0
       Distro: Debian GNU/Linux 7 default username:password is [arduinotre:tre]
       Machine:   No /sys/class/dmi; using dmidecode: dmidecode is not installed.
       CPU:       Single core ARMv7 rev 2 (v7l) (-UP-) (ARM)bmips: 297 speed: 300 MHz
       Graphics:  Card: Failed to Detect Video Card!
       Display Server: X.org 1.12.4 driver: N/A tty size: 118x19 Advanced Data: N/A out of X
       Audio:     Card DA830 EVM driver: DA830_EVM Sound: ALSA v: k3.8.13+
       Network:   Card: Failed to Detect Network Card!
       Partition: ID-1: / size: 6.7G used: 2.2G (34%) fs: ext4 dev: /dev/root
       Sensors:   System Temperatures: cpu: 57.0C mobo: N/A Fan Speeds (in rpm): cpu: N/A
       Info:      Processes: 110 Uptime: 2:26 Memory: 117.9/498.4MB Init: SysVinit runlevel: 2 Gcc sys: 4.6.3
       Client: Shell (bash 4.2.371) inxi: 2.2.28 
       
### Install 
To install packages you need to use the apt (Advance Package Tool), for more info check the official debian 
documentation, here a simple example : 

      sudo apt-get update 
      sudo apt-get install inxi 
      sudo apt-get purge inxi 
