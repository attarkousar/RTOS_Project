#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

// Define the GPIO pin for the LED
#define LED_GPIO GPIO_NUM_2

// Task to blink the LED
void blink_led_task(void *pvParameter) {
    // Configure the GPIO for the LED
    //gpio_pad_select_gpio(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while (1) {
        // Turn the LED on
        gpio_set_level(LED_GPIO, 1);
        printf("LED On\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for 1 second

        // Turn the LED off
        gpio_set_level(LED_GPIO, 0);
        printf("LED Off\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for 1 second
    }
}

void app_main(void) {
    // Create the LED blink task
    xTaskCreate(blink_led_task, "blink_led_task", 1024, NULL, 5, NULL);
}

