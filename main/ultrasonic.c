#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "hc_sr04.h"

// Ultrasonic sensor 1
#define TRIG_GPIO_1 4
#define ECHO_GPIO_1 5
// Ultrasonic sensor 2
#define TRIG_GPIO_2 21
#define ECHO_GPIO_2 22
// Bin threshold in cm
#define DISTANCE_THRESHOLD 10.0


static const char *TAG = "HC-SR04";

void check_distance(void *params) {
    hc_sr04_t sensor_1 = { .trig_pin = TRIG_GPIO_1, .echo_pin = ECHO_GPIO_1 };
    hc_sr04_t sensor_2 = { .trig_pin = TRIG_GPIO_2, .echo_pin = ECHO_GPIO_2 };

    hc_sr04_init(&sensor_1);
    hc_sr04_init(&sensor_2);

    while (1) {
        float distance_1 = hc_sr04_get_distance(&sensor_1);
        if (distance_1 < DISTANCE_THRESHOLD) {
            ESP_LOGI(TAG, "Sensor 1 - Distance: %f cm - FULL!", distance_1);
        } else {
            ESP_LOGI(TAG, "Sensor 1 - Distance: %f cm", distance_1);
        }

        float distance_2 = hc_sr04_get_distance(&sensor_2);
        if (distance_2 < DISTANCE_THRESHOLD) {
            ESP_LOGI(TAG, "Sensor 2 - Distance: %f cm - FULL!", distance_2);
        } else {
            ESP_LOGI(TAG, "Sensor 2 - Distance: %f cm", distance_2);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main(void) {
    xTaskCreate(check_distance, "check_distance", 4096, NULL, 5, NULL);
}
