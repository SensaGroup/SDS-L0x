#include "hall.h"

uint8_t hall_1_state = 0;
uint8_t hall_2_state = 0;

uint8_t hall_1_get_state() {
    return hall_1_state;
}

uint8_t hall_2_get_state() {
    return hall_2_state;
}

void hall_1_change() {
    hall_1_state = !hall_1_state;
}

void hall_2_change() {
    hall_2_state = !hall_2_state;
}

void hall_setup() {
    pinMode(HALL_1_PIN, INPUT_PULLUP);
    pinMode(HALL_2_PIN, INPUT_PULLUP);

    hall_1_state = digitalRead(HALL_1_PIN);
    hall_2_state = digitalRead(HALL_2_PIN);

    attachInterrupt(digitalPinToInterrupt(HALL_1_PIN), hall_1_change, CHANGE);
    attachInterrupt(digitalPinToInterrupt(HALL_2_PIN), hall_2_change, CHANGE);
}