#include <i2cmaster.h>

void setup() {

  Serial.begin(9600);           //start up that serial port, I can go up to 115200, but would like to stay below that probably

  pinMode(hallPin, INPUT);    
  pinMode(tempPin, INPUT);    

  i2c_init();                                 //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);      //enable pullups
  Serial.println("Up and running");

}

