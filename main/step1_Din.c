#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BUTTON_PIN GPIO_NUM_23 // Define the button GPIO pin number

volatile bool button_pressed = false; // Flag to check button press

// Interrupt Service Routine (ISR) for button press
void IRAM_ATTR button_isr_handler(void* arg) {
    button_pressed = true; // Set flag to indicate button was pressed
}

void app_main() {
    // Configure the button pin as input
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_POSEDGE;       // Interrupt on rising edge
    io_conf.pin_bit_mask = (1ULL << BUTTON_PIN); // Set bit mask for the pin
    io_conf.mode = GPIO_MODE_INPUT;              // Set as input mode
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;    // Disable internal pull-up
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;// Disable internal pull-down
    gpio_config(&io_conf);

    // Install GPIO ISR service
    gpio_install_isr_service(0);                 // Default ISR flags
    // Attach ISR handler for specific pin
    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, NULL);

    while (1) {
     
        if (button_pressed) {
            printf("Button pressed!\n"); // Print message
            button_pressed = false;      // Reset flag

            // Add any other button press handling code here
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Add a short delay to avoid busy-waiting
    }
}