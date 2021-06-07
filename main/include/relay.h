#ifndef __relay_h_included__
#define __relay_h_included__

#include "driver/gpio.h"

#define GPIO_RELAY  16

extern void relay_init();
extern void relay_switch(int state);

#endif