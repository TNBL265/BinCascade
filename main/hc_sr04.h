#ifndef HC_SR04_H
#define HC_SR04_H

#include "driver/gpio.h"

typedef struct {
    gpio_num_t trig_pin;
    gpio_num_t echo_pin;
} hc_sr04_t;

void hc_sr04_init(hc_sr04_t *sensor);
float hc_sr04_get_distance(hc_sr04_t *sensor);

#endif // HC_SR04_H
