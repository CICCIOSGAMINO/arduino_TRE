How to install new .img
=======================

### Intro 
This guide you througth the main steps to install a new image for your Arduino TRE board, 
sometimes importants update are delivered with the new images, check it out ! 
Use the last image is the right thing, the improvment is very fast on it during the betatesting, so the review 
on the different images are valid only for the different version deliver publicy. 

Last release is the arduinotre-debian-2014-12-01-2222-8gb.img.xz  03/12/2014 

### Download 
You can find the images (.img.xz) files in the arduino_tre_images repository on my profile :

+ [arduinotre-debian-0.0.10.img.xz][1]  |  md5sum:9f8c40204e7d99d9970a07973ea9279a
+ [arduinotre-debian-2014-12-01-2222-8gb.img.xz][2]  |  md5sum:52d8d63cf8e1f0e569af672e7535805d

### Check md5sum 
In terms of integrity, an MD5 hash comparison detects changes in files that would cause errors. The possibility of changes (errors) is proportional to the size of the file; the possibility of errors increase as the file becomes larger. It is a very good idea to run an MD5 hash comparison check when you have a file like an operating system install CD that has to be 100% correct. 

To get the md5sum of the image file : 

	$ md5sum arduinotre-debian-0.0.10.img.xz 
	9f8c40204e7d99d9970a07973ea9279a
	
	$ md5sum arduinotre-debian-2014-12-01-2222-8gb.img.xz
	52d8d63cf8e1f0e569af672e7535805d
	
If the code that you give from the command is the same of the code give you from a trusted authority you have 
the right file, and are you ready to install the new image. 

Check in the folder with the image for see the md5sum for every version, but i'm not the trusted authority 
check on the official Arduino website for compare the codes! 


### Extract 
xz is the best compression method for the Linux .img (Kernel ecc ) to exctract : 

    	$ unxz arduinotre-debian-0.0.10.img.xz 

### Find the SD
After that you need to find the microSD where the image of the Arduino TRE is host, the common name for this kind of storage in Linux environment is sdb* , when you find it umount(if mounted) : 

  	$ lsblk 
  	$ ls -la /dev/sdb* 
  	....
  		sdb       8:16   1   7,3G  0 disk 
  	├─sdb1    8:17   1    96M  0 part / ../Board_Boot
  	├─sdb2    8:18   1    96M  0 part /../Arduino_TRE
  	└─sdb3    8:19   1   6,9G  0 part /../Debian
  	sr0      11:0    1  1024M  0 rom  
	
	$ umount /dev/sdb*  
	  
### Load on microSD
Now you can load the image on the microSD on  **/dev/sdb**  with the use of the dd command : 

	 $ sudo dd if=arduinotre-debian-0.0.10.img of=/dev/sdb bs=4M conv=fsync

Now you are ready to use the Arduino TRE with the new image ! 

### ssh Login 
The default details for login in the image arduinotre-debian-0.0.10.img.xz is without passw : 

	ssh root@192.168.7.2 
	
for the image md5sum arduinotre-debian-2014-12-01-2222-8gb.img.xz first of all set the user password 
in the IDE connect through browser at 192.168.7.2 if connected by USB cable or at the Network address 
if connected by LAN, set the password example "BOOMTRE" when you are done you can connect through ssh:

	ssh arduinotre@19.168.7.2 
	> password: BOOMTRE 
	
The root access is disable for security reason, but you can connect to with arduinotre user and sudos
your commands ! 

### USB Fix 
If you use an Arduino TRE beta board remember to fix the USB problem with the USB_fix, reported in this repo : 

	https://github.com/CICCIOSGAMINO/arduino_TRE/tree/master/USB_Fix
	
	
### Last Things 
Before start with the sketchs, some little operation to make sure all is on the right way. 

#### Update 
Update the systems packages, and the packages from the Arduino packages manager  : 

	http://localhost/update 
	
I'm not sure, but seems that the beta version 0.0.10 do not like this operation !! 

#### Timezone 
If you want set the timezone, run this command from ssh or LXterminal in Arduino TRE environment : 

	dpkg reconfigure tzdata
	
#### Date 
Set the right date, this is the easy option : 

	date --set "Sat Oct  25 14:03:50 CEST 2014"
	
#### Set the Keyboard 
If you need to set the kwyboard on your default layout : 

	$ apt-get install console-data keyboard-configuration
	$ dpkg-reconfigure console-data
	$ dpkg-reconfigure keyboard-configuration
	$ service keyboard-setup restart
	
To apply new settings, restarting the keyboard-setup service should suffice, otherwise you can try to restart kernel input system via udev:

	$ udevadm trigger --subsystem-match=input --action=change
	
### Link 
[1]:https://www.dropbox.com/s/8qib17tuas9b1fl/arduinotre-debian-0.0.10.img.xz?dl=0
[2]:https://www.dropbox.com/s/kc2w6bd2ku0jdh6/tre-debian-2014-12-01-2222-8gb.img.xz?dl=0
