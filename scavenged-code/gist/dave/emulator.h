#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdarg.h>

#define HIGH 1

unsigned long millis();
float mlx9600();
float analogRead(int pin);
int digitalRead(int pin);

#endif
