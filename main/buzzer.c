#include "include/buzzer.h"

void buzzer_init() {
    gpio_pad_select_gpio(GPIO_BUZZER);
    gpio_set_direction(GPIO_BUZZER, GPIO_MODE_OUTPUT);

    gpio_set_level(GPIO_BUZZER, 0);
}

void buzzer_buzz(int length_ms) {
    gpio_set_level(GPIO_BUZZER, 1);
    vTaskDelay(length_ms / portTICK_PERIOD_MS);
    gpio_set_level(GPIO_BUZZER, 0);
}