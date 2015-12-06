Johnny-Five
===========
[TOC]

## Intro 
Johnny-Five is the original JavaScript Robotics programming framework. Released by Bocoup in 2012, Johnny-Five is 
maintained by a community of passionate software developers and hardware engineers. Over 75 developers have made 
contributions towards building a robust, extensible and composable ecosystem. To get more info about the awesome 
project Johnny5 go to the official [page][1]

### Install on ArduinoTRE
To install Johnny-Five on the board, first check the Node.js and npm version : 

  node --version 
  > v0.10.25
  npm --version
  > 1.3.24 
  
Are good version to work with the robotic framework, if you have not installed Node.js or npm you cannot install and use 
Johnny-Five framework ! Now it's time to install the Node.js module on the host computer and the Firmata sketch and libraries
on the Atmel processor : 

  npm init 
  npm install --save johnny-five 
  
  // app.js 
  










[1]:http://johnny-five.io/
