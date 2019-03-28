#include "motor.h"

uint8_t current_dir = 0;

void motor_init() {
    pinMode(DC1_PIN, OUTPUT);
    pinMode(DC2_PIN, OUTPUT);
}

void motor_change_dir() {
    current_dir = !current_dir;
}

void motor_loop() {
    if(current_dir) {
        digitalWrite(DC1_PIN, LOW);
        digitalWrite(DC2_PIN, motor_speed);
    } else {
        digitalWrite(DC2_PIN, LOW);
        digitalWrite(DC1_PIN, motor_speed);
    }
}

void motor_stop() {
    digitalWrite(DC1_PIN, HIGH);
    digitalWrite(DC2_PIN, HIGH);
}