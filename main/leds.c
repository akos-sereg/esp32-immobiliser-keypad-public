#include "include/leds.h"

void leds_init() {
    gpio_set_direction(GPIO_LEDS_RED, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LEDS_GREEN, GPIO_MODE_OUTPUT);
}

void leds_set(int red, int green) {
    gpio_set_level(GPIO_LEDS_RED, red);
    gpio_set_level(GPIO_LEDS_GREEN, green);
}