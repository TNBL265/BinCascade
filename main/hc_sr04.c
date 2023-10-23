#include "hc_sr04.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void hc_sr04_init(hc_sr04_t *sensor) {
    gpio_set_direction(sensor->trig_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(sensor->echo_pin, GPIO_MODE_INPUT);
    gpio_set_level(sensor->trig_pin, 0);
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
