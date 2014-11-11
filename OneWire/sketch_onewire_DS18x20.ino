/* One Wire - Example to Use 

   We made the experiments with a Seeed Studio SEN08011P Temp Sensor
   the chip inside this sensor is the widely adopted DS18B20 product
   by Maxim/Dallas! 
   
   Keep in Mind : The ds.search(addr) works like an iterator, if a 
       device is found the address is put in the byte addr[8] var 
       but the next time the method is call without the reset_search()
       the ds.search(addr) search for next device! 
       
   See the README.md file for a brief reference to the functions of 
   the OneWire library. 
   
   Author : Canali Marco 
   Date : 11/11/2014

*/ 

// -------------------------- Library ---------------------------
// on pin 7 (a 4.7k resistor necessary if not Seeed Studio)
#include <OneWire.h>

// ---------------------------- Init ----------------------------
byte addr[8];
byte data[12];

int type_s = 0;
int i = 0;

OneWire ds(7);

// --------------------------- getChip --------------------------
void getChip(byte a[8]){
   // the first ROM byte indicates which chip
  switch (a[0]) {
    case 0x10:
      Serial.println("Chip : DS18S20");  // or old DS1820
      type_s = 1;
      break;
    case 0x28:
      Serial.println("Chip : DS18B20");
      type_s = 0;
      break;
    case 0x22:
      Serial.println("Chip : DS1822");
      type_s = 0;
      break;
    default:
      Serial.println("Device is not a DS18x20 family device.");

  } 
}

// -------------------------- printAddr() ------------------------
void printAddr(byte ad[8]){
    Serial.print("Addr : ");
    for(i = 0; i < 8; i++){
        
        Serial.print(ad[i], HEX);
        Serial.print(" ");
    }
    Serial.println("");
}

// -------------------------- readData() ------------------------
void readData(){
   // start conversion, with parasite power on at the end
   ds.write(0x44, 1);
   // maybe 750ms is enough, maybe not
   delay(1000); 

   // reset the 1-wire bus. needed before communicating with any device
   ds.reset();
   // select a device based on its address. After a reset, this is needed 
   // to choose which device you will use, and then all communication will 
   // be with that device, until another reset
   ds.select(addr);
   
   // read the Scratchpad 
   ds.write(0xBE);  
   
   Serial.print("Data : ");
   // read the 9 bytes of the Scratchpad (12 bytes with other models)
   for ( i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
      Serial.print(data[i], HEX);
      Serial.print(" ");
  }
  Serial.println("");

}

// ------------------------- printCRC() ------------------------
void printCRC(byte dta[12]){
    Serial.print("CRC  : ");
    Serial.print(OneWire::crc8(data, 8), HEX);
    Serial.println();
}

// -------------------------- getTemp() -------------------------
// convert : 16bit signed integer -> should be stored in init16_t
float getTemp(){
    int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
   return (float)raw / 16.0; 
} 

// ------------------------- printTemp() ------------------------
void printTemp(){
    Serial.print("Temp : ");
    Serial.println(getTemp());
}

// --------------------------- SetUp ----------------------------
void setup() {
  // start the serial comm 
  Serial.begin(9600);

}

// ---------------------------- Loop ----------------------------
void loop(void) { 
  
  // Search next device, addr is an 8 byte array. device is found 1
  if(!ds.search(addr)){
      Serial.println("NO Address");
      ds.reset_search();
      delay(250);
  }else{
      Serial.println(" ");
      // print the Chip type 
      getChip(addr);
      printAddr(addr);
      readData();
      printCRC(data);
      printTemp();
      
      // reset the addr 
      ds.reset_search();
      delay(250);
  }
  
  delay(5000);
}
