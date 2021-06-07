#ifndef __keypad_h_included__
#define __keypad_h_included__

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"
#include <string.h>

#define GPIO_KEYPAD_ROW_1   33
#define GPIO_KEYPAD_ROW_2   25
#define GPIO_KEYPAD_ROW_3   26
#define GPIO_KEYPAD_ROW_4   23
#define GPIO_KEYPAD_COL_1   34
#define GPIO_KEYPAD_COL_2   35
#define GPIO_KEYPAD_COL_3   36

extern void keypad_init();
extern void keypad_start_scan();

#endif
