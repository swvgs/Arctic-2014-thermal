#include <OneWire.h>
unsigned long waituntil = 0;
long looppause = 5000; //time to delaybetween loops in miliseconds, 30000 = 30seconds
long sensorpause = 500; //time to delaybetween sensor readings in miliseconds, 1000 = 1second. Needs to be grater than ~300 to be useful.
                        //the code takes about 280 seconds to run through EACH sensor, so this delays between sensor readings so that there is an 
                        //even interval between each time the sensor is polled. 
                        //Keep in mind, if you have 8 sensors the total time to read will be 8 times this delay

//This is a decliaration of the unique ID's for each sensor. This will make it easier to identify which sensor is which when you look at the data.
char* sensor[11] = {"01", "02", "03", "04", "05", "06", "07", "08", "11", "10", "09"};
char* unique[11] = {"28651a6340071", "28e58b49300f0", "2853c2493005f", "282ac3493009c", "2869d6340071", "2871563400b3", "2872916340014", "2894de634009", "28e5b204008e", "2873a804004c", "286fca0400f8"};


// DS18S20 Temperature chip i/o
 OneWire ds(5);  // device is hooked up on pin 5

void setup(void) {
   // initialize inputps/outputs
   // start serial port
   Serial.begin(9600);
   delay(3000); //this delay gives the MC time to boot up, however it makes the first 3 readings time wrong. not sure what to do about that. It tries to make up for missed readings or something.
   Serial.println();
   Serial.println("sensor ID, time, temperature");
   
}

void loop(void) {

  if (millis() >= waituntil) {
    byte i;
    byte present = 0;
    byte data[12];
    byte addr[8];
    String id;

    if ( !ds.search(addr)) {
        Serial.print("No more addresses.\n");
        ds.reset_search();
        waituntil += looppause;
        return;
    }

//    for( i = 0; i < 8; i++) {
//        Serial.println(addr[i], HEX);
//    }

    for ( i = 0; i < 8; i++) {
      id = id + String(addr[i],HEX);
    }
//    Serial.print(id);
//    Serial.print(", ");
    for (i = 0; i < 11; i++) {
      if (id == String(unique[i])) { 
        Serial.print(sensor[i]);
      }
    }


    if ( OneWire::crc8( addr, 7) != addr[7]) {
        Serial.print("CRC is not valid!\n");
        return;
    }

    ds.reset();
    ds.select(addr);
    ds.write(0x44,1);         // start conversion, with parasite power on at the end

    delay(100);     // maybe 750ms is enough, maybe not
    // we might do a ds.depower() here, but the reset will take care of it.

    present = ds.reset();
    ds.select(addr);    
    ds.write(0xBE);         // Read Scratchpad

    for ( i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
    }
   
    byte MSB = data[1];
    byte LSB = data[0];

    float tempRead = ((MSB << 8) | LSB); //using two's compliment
    float TemperatureSum = tempRead / 16;
   
    Serial.print(", ");
    Serial.print(millis());
    Serial.print(", ");
    Serial.print(TemperatureSum);
    Serial.print(", ");
    
    waituntil += sensorpause; //add time to the hold thingie
  }
}
