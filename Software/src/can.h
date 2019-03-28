#ifndef CAN_H
#define CAN_H

#include <Arduino.h>
#include <mcp_can.h>
#include <SPI.h>

#define CAN_LIDAR_ID  0x55
#define GLAVNA_CAN_ID 0x10

bool can_init(int baud);
void can_test();
#endif