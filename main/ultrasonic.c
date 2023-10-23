#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TRIG_GPIO 4
#define ECHO_GPIO 5

static const char *TAG = "HC-SR04";

void check_distance(void *params) {
    gpio_set_direction(TRIG_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_GPIO, GPIO_MODE_INPUT);

    gpio_set_level(TRIG_GPIO, 0);
    vTaskDelay(10 / portTICK_PERIOD_MS);

    while (1) {
        // Send trigger pulse
        gpio_set_level(TRIG_GPIO, 1);
        ets_delay_us(10);
        gpio_set_level(TRIG_GPIO, 0);

        // Wait for echo
        while (gpio_get_level(ECHO_GPIO) == 0);

        uint32_t start_time = esp_timer_get_time();
        while (gpio_get_level(ECHO_GPIO) == 1);
        uint32_t end_time = esp_timer_get_time();

        // Calculate distance
        float distance = (end_time - start_time) * 0.0343 / 2;
        ESP_LOGI(TAG, "Distance: %f cm", distance);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void) {
    xTaskCreate(check_distance, "check_distance", 2048, NULL, 5, NULL);
}
