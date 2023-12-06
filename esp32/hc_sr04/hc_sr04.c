#include "hc_sr04.h"
#include "esp_timer.h"
#include "esp_log.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "ssd1306.h"

// Ultrasonic sensor 1
#define TRIG_GPIO_1 18
#define ECHO_GPIO_1 19
// Ultrasonic sensor 2
#define TRIG_GPIO_2 25
#define ECHO_GPIO_2 26

// Globals or module-level variables:
hc_sr04_t sensor_1 = { .trig_pin = TRIG_GPIO_1, .echo_pin = ECHO_GPIO_1 };
hc_sr04_t sensor_2 = { .trig_pin = TRIG_GPIO_2, .echo_pin = ECHO_GPIO_2 };

void hc_sr04_init(void) {
    // Initialize sensor_1
    gpio_set_direction(sensor_1.trig_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(sensor_1.echo_pin, GPIO_MODE_INPUT);
    gpio_set_level(sensor_1.trig_pin, 0);

    // Initialize sensor_2
    gpio_set_direction(sensor_2.trig_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(sensor_2.echo_pin, GPIO_MODE_INPUT);
    gpio_set_level(sensor_2.trig_pin, 0);
}

float hc_sr04_get_distance(hc_sr04_t *sensor) {
    gpio_set_level(sensor->trig_pin, 0);
    ets_delay_us(2);
    gpio_set_level(sensor->trig_pin, 1);
    ets_delay_us(10);
    gpio_set_level(sensor->trig_pin, 0);

    while (gpio_get_level(sensor->echo_pin) == 0);
    uint32_t start_time = esp_timer_get_time();
    while (gpio_get_level(sensor->echo_pin) == 1);
    uint32_t end_time = esp_timer_get_time();

    return (end_time - start_time) * 0.0343 / 2;
}

void check_distance(char *outputStr, size_t bufferSize) {
    SensorDistances distances;

    distances.distance_1 = hc_sr04_get_distance(&sensor_1);
    distances.distance_2 = hc_sr04_get_distance(&sensor_2);

    snprintf(outputStr, bufferSize, "%.2f,%.2f", distances.distance_1, distances.distance_2);
}
