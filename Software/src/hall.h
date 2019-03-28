#ifndef HALL_H
#define HALL_H

#include <Arduino.h>

// at CAN chip
#define HALL_1_PIN 3
#define HALL_2_PIN 2


uint8_t hall_1_get_state();
uint8_t hall_2_get_state();
void hall_1_change();
void hall_2_change();
void hall_setup();
#endif