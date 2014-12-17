#!/usr/bin/env bash

mv /etc/init.d/boot_scripts.sh /root/USBTemporaryFix/boot_scripts.sh.BAK
mv /boot/uImage /root/USBTemporaryFix/uImage.BAK
cp /root/USBTemporaryFix/boot_scripts.sh /etc/init.d/boot_scripts.sh
cp /root/USBTemporaryFix/uImage /boot/uImage
chmod a+x /etc/init.d/boot_scripts.sh
poweroff
