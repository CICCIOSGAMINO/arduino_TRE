/* 
  simple serial app for serial communication in Node.js 
  Packages : readline, serialport 
  
  node app.js /dev/ttyUSB0 9600  (default are /dev/ttyACM0 9600)

*/ 


// used for read from console line at line 
var readline = require('readline');
// serialport package 
var serialport = require('serialport');
var SerialPort = serialport.SerialPort;

// serial connection options for Arduino Tre 
opts = {baudrate : 9600, 
        databits : 8, 
        parity : 'none', 
        stopbits : 1, 
        flowcontrol : false,  
        parser: serialport.parsers.readline("\n")
      };
        
// true open right now or false -> .open(function(err))
var sp = new SerialPort(process.argv[2] || '/dev/ttyACM0', opts,true);

var rl =readline.createInterface({
	input: process.stdin,
	output: process.stdout
});


// waith for the connection to do 
sp.on('open', function(){
	console.log('Connection Open ... ');

	rl.on('line', function(line){
		sp.write(line + '\r');
	});

	sp.on('data', function(data){
		console.log(data);
	});

}); 
