#include "chip_stuff.h"

#ifdef EMULATE
#include "emulator.h"
#include "strings.h"
#include <stdio.h>
#else
#include <i2cmaster.h> // this is going beyond psudocode, but if we end up getting this workable, then it needs to be here?
#endif


//other vars
unsigned long currentMillis;   //for time keeping
size_t position = 0;             //position in the array?
unsigned long dataTime[arrSize];   //time array


//Hall vars
int hallState = 0;

//TMP36 vars (ambient temperature)
float voltage;          //for the analog read
float ambTemp[arrSize];      //ambient temperature array that has 30 values 
float degreesC;         //variable that has the current temperature in it

//MLX90614-ACC vars (IR temperature)
float celcius;          //store temperature
float irTemp[arrSize];       //IR temperature array that has 30 values

float getVoltage(int pin) {
  return (analogRead(pin) * 5.0 / 1024.0);  //converts 0-1023 to a 0-5V number
}

void loop() {

  currentMillis = millis();
  celcius = mlx9600();
  voltage = getVoltage(tempPin);
  degreesC = (voltage - 0.5) * 100.0;  //Linear voltage sensor


  ambTemp[position % arrSize] = degreesC;
  irTemp[position % arrSize] = celcius;
  dataTime[position % arrSize] = currentMillis;
  position++;

  hallState = digitalRead(hallPin);

  if (hallState == HIGH) {
    size_t idx = 0;
    for(;idx < arrSize;idx++)
      printf("%ld,", dataTime[idx]);
    printf(",");
    for(idx = 0;idx < arrSize;idx++)
      printf("%f,",irTemp[idx]);
    for(idx = 0;idx < arrSize-1;idx++)
      printf("%f",ambTemp[idx]);
    printf("%f\n", ambTemp[idx]);
  }

}


