GPIO
==== 

## Intro 
GPIO mean "General Purpose Input/Output" and is a special pin present in some chip that can be set as input or output and used to move a signal high or low (in output mode) or to get the signal current status (in input mode). Usually these pin are directly managed by kernel modules but there are an easy way to manage these pins also from user space.

Standard Linux kernel have inside a special interface allow to access to GPIO pins. Once executed kernel menuconfig you can easily verify is this interface is active in your kernel and, in case, enable them. The kernel tree path is the following:

    /sys/class/gpio/

Basically if you want to work with a particular GPIO you must first to reserve it, set the input/output direction and start managing it. Once you reserved the GPIO and finished to use you need to free it for allow other modules or process to use them. This rule is valid in both cases you want to use GPIO from kernel level or user level.

### Manage GPIO cmd or script 

From the user level side this "operation" for reserve the GPIO is called "export" the GPIO. For make this export operation you simply need to echo the GPIO number you are interested to a special path as follow (change XX with the GPIO number you need):

echo XX > /sys/class/gpio/export

If operation successful (the possible case of operation failed is explained below) a new "folder" will show up in the GPIO interface path as example below:

/sys/class/gpio/gpioXX/
