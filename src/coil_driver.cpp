#include <Arduino.h>
#include "coil_driver.h"
#include "config.h"

static bool s_coilState = false;

void coilInit() {
    pinMode(PIN_COIL_OUT, OUTPUT);
    digitalWrite(PIN_COIL_OUT, LOW);

    pinMode(PIN_SYNC_LED, OUTPUT);
    digitalWrite(PIN_SYNC_LED, LOW);

    s_coilState = false;
}

void coilOn() {
    digitalWrite(PIN_COIL_OUT, HIGH);
    s_coilState = true;
}

void coilOff() {
    digitalWrite(PIN_COIL_OUT, LOW);
    s_coilState = false;
}

bool coilIsOn() {
    return s_coilState;
}