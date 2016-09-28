# Install the DDNS no-ip service on Debian

## Install noip2
Follow this simple steps to install noip2, If you do not have privileges on the machine you are on, you may add the “sudo” command in front of steps (5 and 6).

    cd /usr/local/src
    sudo wget http://www.no-ip.com/client/linux/noip-duc-linux.tar.gz
    sudo tar xzf noip-duc-linux.tar.gz
    cd no-ip-2.1.9
    sudo make
    sudo make install
    
## Configure the client 
As root again (or with sudo) issue the below command:

    /usr/local/bin/noip2 -C
    
You will then be prompted for your username and password for No-IP, as well as which hostnames you wish to update.  Be careful, one of the questions is “Do you wish to update ALL hosts”.  If answered incorrectly this could affect hostnames in your account that are pointing at other locations.

## Launch 
Now that the client is installed and configured, you just need to launch it.  Simply issue this final command to launch the client in the background:

    /usr/local/bin/noip2
    
Read the README file in the no-ip-2.1.9 folder for instructions on how to make the client run at startup. This varies depending on what Linux distribution you are running.

## init.d Script
Create a init.d script in the folder **/etc/init.d/noip2**, the file is noip2 in this DDNS folder 

## Then make it executable

    chmod a+x /etc/init.d/noip2

## run

    update-rc.d noip2 defaults 
