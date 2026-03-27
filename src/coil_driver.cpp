#include <Arduino.h>

#include "coil_driver.h"
#include "config.h"

static const uint8_t COIL_PINS[COIL_COUNT] = {
    PIN_COIL_1,
    PIN_COIL_2,
    PIN_COIL_3,
    PIN_COIL_4,
    PIN_COIL_5,
    PIN_COIL_6
};

static bool s_coilState[COIL_COUNT] = {false, false, false, false, false, false};

static inline bool validCoil(uint8_t coilIndex) {
    return (coilIndex < COIL_COUNT);
}

void coilInit() {
    for (uint8_t i = 0; i < COIL_COUNT; i++) {
        pinMode(COIL_PINS[i], OUTPUT);
        digitalWrite(COIL_PINS[i], COIL_INACTIVE_STATE);
        s_coilState[i] = false;
    }

    pinMode(PIN_SYNC_LED, OUTPUT);
    digitalWrite(PIN_SYNC_LED, LOW);
}

void coilOn(uint8_t coilIndex) {
    if (!validCoil(coilIndex)) {
        return;
    }

    digitalWrite(COIL_PINS[coilIndex], COIL_ACTIVE_STATE);
    s_coilState[coilIndex] = true;
}

void coilOff(uint8_t coilIndex) {
    if (!validCoil(coilIndex)) {
        return;
    }

    digitalWrite(COIL_PINS[coilIndex], COIL_INACTIVE_STATE);
    s_coilState[coilIndex] = false;
}

void coilAllOff() {
    for (uint8_t i = 0; i < COIL_COUNT; i++) {
        digitalWrite(COIL_PINS[i], COIL_INACTIVE_STATE);
        s_coilState[i] = false;
    }
}

bool coilIsOn(uint8_t coilIndex) {
    if (!validCoil(coilIndex)) {
        return false;
    }

    return s_coilState[coilIndex];
}