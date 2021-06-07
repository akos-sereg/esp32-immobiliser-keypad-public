#ifndef __leds_h_included__
#define __leds_h_included__

#include "driver/gpio.h"

#define GPIO_LEDS_RED       17
#define GPIO_LEDS_GREEN     22

extern void leds_init();
extern void leds_set(int red, int green);

#endif