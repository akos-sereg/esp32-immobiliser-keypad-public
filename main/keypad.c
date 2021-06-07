#include "include/keypad.h"
#include "include/buzzer.h"
#include "include/main.h"
#include "include/leds.h"
#include "include/relay.h"

char last_chars[5];
int last_chars_size = 0;

void keypad_init() {
    printf("Initializing keypad\n");

    // scanning rows (write)
    gpio_set_direction(GPIO_KEYPAD_ROW_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_KEYPAD_ROW_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_KEYPAD_ROW_3, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_KEYPAD_ROW_4, GPIO_MODE_OUTPUT);

    // scanning columns (read)
    gpio_set_direction(GPIO_KEYPAD_COL_1, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_KEYPAD_COL_2, GPIO_MODE_INPUT);
    gpio_set_direction(GPIO_KEYPAD_COL_3, GPIO_MODE_INPUT);

    // reset all rows to null state
    gpio_set_level(GPIO_KEYPAD_ROW_1, 0);
    gpio_set_level(GPIO_KEYPAD_ROW_2, 0);
    gpio_set_level(GPIO_KEYPAD_ROW_3, 0);
    gpio_set_level(GPIO_KEYPAD_ROW_4, 0);

    // init keypad output
    last_chars[0] = '\0';
    last_chars[1] = '\0';
    last_chars[2] = '\0';
    last_chars[3] = '\0';
    last_chars[4] = '\0';
}

void last_chars_append(char pressed_char) {
    if (last_chars_size < 5) {
        last_chars[last_chars_size] = pressed_char;
        last_chars_size++;
    } else {
        last_chars[0] = last_chars[1];
        last_chars[1] = last_chars[2];
        last_chars[2] = last_chars[3];
        last_chars[3] = last_chars[4];
        last_chars[4] = pressed_char;
    }
}

void keypad_scanning_task(void* arg) {
    int tick_interval_ms_local = 50;
    char last_pressed = NULL;
    char pressed = NULL;
    int beep_done = 0;

    while(1)
    {
      pressed = NULL;

      gpio_set_level(GPIO_KEYPAD_ROW_1, 1); //r1
      // vTaskDelay(tick_check_ms / portTICK_PERIOD_MS);
      if(gpio_get_level(GPIO_KEYPAD_COL_1) == 1){ pressed = '1'; }
      else if(gpio_get_level(GPIO_KEYPAD_COL_2) == 1){ pressed = '2'; }
      else if(gpio_get_level(GPIO_KEYPAD_COL_3) == 1){ pressed = '3'; }
      gpio_set_level(GPIO_KEYPAD_ROW_1, 0); //r1

      gpio_set_level(GPIO_KEYPAD_ROW_2, 1); //r2
      // vTaskDelay(tick_check_ms / portTICK_PERIOD_MS);
      if(gpio_get_level(GPIO_KEYPAD_COL_1) == 1){ pressed = '4'; }
      else if(gpio_get_level(GPIO_KEYPAD_COL_2) == 1){ pressed = '5'; }
      else if(gpio_get_level(GPIO_KEYPAD_COL_3) == 1){ pressed = '6'; }
      gpio_set_level(GPIO_KEYPAD_ROW_2, 0); //r2

      gpio_set_level(GPIO_KEYPAD_ROW_3, 1); //r3
      // vTaskDelay(tick_check_ms / portTICK_PERIOD_MS);
      if(gpio_get_level(GPIO_KEYPAD_COL_1) == 1){ pressed = '7'; }
      else if(gpio_get_level(GPIO_KEYPAD_COL_2) == 1){ pressed = '8'; }
      else if(gpio_get_level(GPIO_KEYPAD_COL_3) == 1){ pressed = '9'; }
      gpio_set_level(GPIO_KEYPAD_ROW_3, 0); //r3

      gpio_set_level(GPIO_KEYPAD_ROW_4, 1); //r4
      // vTaskDelay(tick_check_ms / portTICK_PERIOD_MS);
      if(gpio_get_level(GPIO_KEYPAD_COL_1) == 1){ pressed = '*'; }
      else if(gpio_get_level(GPIO_KEYPAD_COL_2) == 1){ pressed = '0'; }
      else if(gpio_get_level(GPIO_KEYPAD_COL_3) == 1){ pressed = '#'; }
      gpio_set_level(GPIO_KEYPAD_ROW_4, 0); //r4

      if (pressed != NULL) {
        last_pressed = pressed;

        if (!beep_done) {
            buzzer_buzz(50);
            beep_done = 1;
        }
      }

      if (pressed == NULL && last_pressed != NULL) {
        // report last pressed key
        last_chars_append(last_pressed);
        printf("Last bytes: %s\n", last_chars);
        last_pressed = NULL;
        beep_done = 0;

        if (strncmp(last_chars, KEYPAD_PIN_CODE, 5) == 0) {
            printf("-> Access Granted");
            leds_set(0, 1);
            relay_switch(1);
            access_granted = 1;
        }
      }
      vTaskDelay(tick_interval_ms_local / portTICK_PERIOD_MS);
    }
}

void keypad_start_scan() {
    printf("Start scanning keypad\n");
    xTaskCreate(keypad_scanning_task, "keypad_scanning_task", (2048), NULL, 5, NULL);
}