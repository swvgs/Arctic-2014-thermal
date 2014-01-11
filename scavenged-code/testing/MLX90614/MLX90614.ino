#include <i2cmaster.h>


void setup()  {
  
  Serial.begin(9600);
  Serial.println("Enable Thermal Sensor...");
  i2c_init(); //Initialise the i2c bus
  PORTC = (1 << PORTC4) | (1 << PORTC5);//enable pullups

  Serial.println("ver 12_01_2013");
  Serial.println("mark,time,ir,ambiant,ms");

}

void loop() { 

  unsigned long currentMillis = millis();
  float celcius = mlx9600();

  Serial.print(",");
  Serial.println(celcius);


}


