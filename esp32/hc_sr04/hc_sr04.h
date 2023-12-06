#ifndef HC_SR04_H
#define HC_SR04_H

#include "driver/gpio.h"

typedef struct {
    gpio_num_t trig_pin;
    gpio_num_t echo_pin;
} hc_sr04_t;

typedef struct {
    float distance_1;
    float distance_2;
} SensorDistances;

void hc_sr04_init(void);
float hc_sr04_get_distance(hc_sr04_t *sensor);
void check_distance(char *outputStr, size_t bufferSize);

#endif // HC_SR04_H
