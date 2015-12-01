Node.js
=======
[TOC]

## Intro 
At the time of this writing Arduino TRE is based on Debian Wheezy, which comes with the stable but outdated GCC 4.6 as the 
default C and C++ compiler. If you want to write modern C++ code you are stuck with a partial implementation of the C++11 
standard as you want install performant programs like Node.js > 4.0 ! So we'll try to install g++-4.9 and 

### Install g++-4.9 & g++-4.9 
To install the latest Node.js version you need a compiler such as g++-4.9 and gcc-4.9. Fortunately we can found these packages 
the Debian's Jessi relase so : 

  sudo apt-get update
  sudo apt-get upgrade
  
Next, open /etc/apt/sources.list in your favorite text editor and replace wheezy with jessie in the first 2 rows:

    sudo vim /etc/apt/sources.list
  
Update your package list:

    sudo apt-get update
  
and, finally, install GCC 4.9

    sudo apt-get install gcc-4.9 g++-4.9
    
Last step is to revert back from Jessie to Wheezy, open /etc/apt/sources.list and replace jessie with wheezy, after that do an update of your package list:

    sudo vim /etc/apt/sources.list
    sudo apt-get update
    
The above procedure will keep GCC 4.6 as the default C and C++ compiler for any package that depends on it, if you want to compile a program with GCC 4.9 you will have to use gcc-4.9 and g++-4.9 when invoking the compilers.

Let’s try to compile and run a C++14 code that uses a generalized lambda expression : 

    
