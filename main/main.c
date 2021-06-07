#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/gpio.h"
#include "include/main.h"
#include "include/keypad.h"
#include "include/buzzer.h"
#include "include/leds.h"
#include "include/relay.h"

int access_granted = 0;

void main_loop()
{
    long access_granted_elapsed = 0;
    int cnt = 0;
    int cnt2 = 0;
    // gpio_set_direction(18, GPIO_MODE_OUTPUT);

    int tick_interval_ms = 1000;
    // relay_switch(1);
    while (1)
    {
        if (access_granted) {
            access_granted_elapsed += tick_interval_ms;
        }

        if (access_granted_elapsed > ACCESS_GRANTED_TIMEFRAME_MS) {
            access_granted_elapsed = 0;
            access_granted = 0;
            leds_set(1, 0);
            relay_switch(0);
        }


        vTaskDelay(tick_interval_ms / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    keypad_init();
    keypad_start_scan();
    buzzer_init();
    relay_init();
    leds_init();
    leds_set(1, 0);

    main_loop();
}

