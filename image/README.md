How to install new .img
=======================

### Intro 
This guide you througth the main steps to install a new image for your Arduino TRE board, 
sometimes importants update are delivered with the new images, check it out ! 

### Download 
You can find the images (.img.xz) files in the arduino_tre_images repository on my profile :

+ [arduinotre-debian-0.0.10.img.xz][1] md5sum 9f8c40204e7d99d9970a07973ea9279a

### Check md5sum 
In terms of integrity, an MD5 hash comparison detects changes in files that would cause errors. The possibility of changes (errors) is proportional to the size of the file; the possibility of errors increase as the file becomes larger. It is a very good idea to run an MD5 hash comparison check when you have a file like an operating system install CD that has to be 100% correct. 

To get the md5sum of the image file : 

	$ md5sum arduinotre-debian-0.0.10.img.xz 
	9f8c40204e7d99d9970a07973ea9279a
	
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

Now you are ready to use the Arduino TRE with the new image 0.0.10 ! 

### USB Fix 
If you use an Arduino TRE beta board remember to fix the USB problem with the USB_fix, reported in this repo : 

	https://github.com/CICCIOSGAMINO/arduino_TRE/tree/master/USB_Fix
	
	
### Last Things 
Before start with the sketchs, some little operation to make sure all is on the right way, update the systems 
packages, and the packages from the Arduino packages manager  : 

	http://localhost/update 
	
In beta version the default locale is US and the keypad with the us layout, to change to italian keyboard : 

	$ apt-get install console-data keyboard-configuration
	$ dpkg-reconfigure console-data
	$ dpkg-reconfigure keyboard-configuration
	$ service keyboard-setup restart
	
To apply new settings, restarting the keyboard-setup service should suffice, otherwise you can try to restart kernel input system via udev:

	$ udevadm trigger --subsystem-match=input --action=change


	
### Link 
[1]:https://www.dropbox.com/s/8qib17tuas9b1fl/arduinotre-debian-0.0.10.img.xz?dl=0
