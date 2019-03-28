#include "lidar_info.h"

uint8_t lidar_status = 0; // 0 -> OFF, 1 -> ON
uint8_t lidar_detected = 0; // 0 -> NOT DETECTED, 1 -> DETECTED

uint8_t lidar_set_status(uint8_t status) {
    lidar_status = status;
}
uint8_t lidar_get_status() {
    return lidar_status;
}

uint8_t lidar_set_detected(uint8_t status) {
    lidar_detected = status;
}
uint8_t lidar_get_detected() {
    return lidar_detected;
}