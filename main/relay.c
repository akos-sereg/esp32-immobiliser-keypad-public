#include "include/relay.h"

void relay_init() {
    gpio_pad_select_gpio(GPIO_RELAY);
    gpio_set_direction(GPIO_RELAY, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_RELAY, 0);
}

void relay_switch(int state) {
    gpio_set_level(GPIO_RELAY, state);
}