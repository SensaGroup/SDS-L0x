#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <Adafruit_VL53L0X.h>

#define sensor_upper_range 400
#define sensor_lower_range 200

bool sensor_init();
bool sensor_detect();

#endif