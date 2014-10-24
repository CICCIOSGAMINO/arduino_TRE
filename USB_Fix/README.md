USB hot plug temporary fix
==========================

### Intro (only in beta)
We are now working on a fix for the USB hot plug issue, but it’s not active by default because we
are investigating on an issue: if a device is quickly plugged/unplagged or if a connected device
reenumerates (e.g. when programming an external Arduino Leonardo), the USB port or the entire
board get unstable.


### How to enable the fix
Open a shell terminal, login as rootand run the following commands:

    mv /etc/init.d/boot_scripts.sh /root/USBTemporaryFix/boot_scripts.sh.BAK
    mv /boot/uImage /root/USBTemporaryFix/uImage.BAK
    cp /root/USBTemporaryFix/boot_scripts.sh /etc/init.d/boot_scripts.sh
    cp /root/USBTemporaryFix/uImage /boot/uImage
    chmod a+x /etc/init.d/boot_scripts.sh
    poweroff
    
When the board is powerd on again the fix is active.

### How to disable the fix
Open a shell terminal, login as rootand run the following commands:

    mv /root/USBTemporaryFix/boot_scripts.sh.BAK /etc/init.d/boot_scripts.sh
    mv /root/USBTemporaryFix/uImage.BAK /boot/uImage
    chmod a+x /etc/init.d/boot_scripts.sh
    poweroff
    
When the board is powerd on again the fix is not active anymore.
