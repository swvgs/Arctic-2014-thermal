#include "emulator.h"
#include <time.h>
#include <stdio.h>

unsigned long millis() {
  return ((unsigned long)time(NULL)) * 1000;
}

float mlx9600() {
  return 42.0;
}

float analogRead(int tempPin) {
  return 4.2;
}

int digitalRead(int pin) {
  return 1;
}


int main(int argc, char **argv) {
  extern void loop();

  int idx = 0;
  for(;idx < 42;idx++)
    loop();
  return 1;
}
