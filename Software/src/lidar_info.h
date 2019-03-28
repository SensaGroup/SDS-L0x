#ifndef LIDAR_INFO_H
#define LIDAR_INFO_H

#include <Arduino.h>

uint8_t lidar_set_status(uint8_t status);
uint8_t lidar_get_status();

uint8_t lidar_set_detected(uint8_t status);
uint8_t lidar_get_detected();

#endif