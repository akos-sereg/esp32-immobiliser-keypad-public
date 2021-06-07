#ifndef __buzzer_h_included__
#define __buzzer_h_included__

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"

#define GPIO_BUZZER 12

extern void buzzer_init();
extern void buzzer_buzz(int length_ms);

#endif