How to install new .img
=======================

### Intro 
This guide you througth the main steps to install a new image for your Arduino TRE board, 
sometimes importants update are delivered with the new images, check it out ! 

### Download 

### Check md5sum 

### Extract 
xz is the best compression method for the Linux .img (Kernel ecc ) to exctract : 

    unxz arduinotre-debian-0.0.10.img.xz 

### Find the SD
After that you need to find the microSD where the image of the Arduino TRE is host, the common name for this kind of storage in Linux environment is sdb* , when you find it umount(if mounted) : 

  	lsblk 
  	ls -la /dev/sdb* 
  	....
  		sdb       8:16   1   7,3G  0 disk 
  	├─sdb1    8:17   1    96M  0 part / ../Board_Boot
  	├─sdb2    8:18   1    96M  0 part /../Arduino_TRE
  	└─sdb3    8:19   1   6,9G  0 part /../Debian
  	sr0      11:0    1  1024M  0 rom  
	
	  umount /dev/sdb*  
	  
### Load on microSD

after that you can load the image on the **sdb**  with the use of the dd command : 

	 sudo dd if=arduinotre-debian-0.0.10.img of=/dev/sdb bs=4M conv=fsync

