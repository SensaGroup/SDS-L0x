#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define DC1_PIN A1
#define DC2_PIN A0

#define motor_speed HIGH

void motor_init();
void motor_change_dir();
void motor_loop();
void motor_stop();

#endif