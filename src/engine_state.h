#pragma once
#include <Arduino.h>

struct EngineState {
    volatile bool newTooth = false;
    volatile uint32_t lastToothTimeUs = 0;
    volatile uint32_t toothPeriodUs = 0;
    volatile uint32_t prevToothPeriodUs = 0;

    volatile bool synced = false;
    volatile uint8_t toothIndex = 0;
    volatile uint32_t toothCounter = 0;

    float camRpm = 0.0f;
    float engineRpm = 0.0f;
    float engineAngleDeg = 0.0f;

    bool coilCharging = false;
    bool sparkScheduled = false;
    uint32_t scheduledChargeStartUs = 0;
    uint32_t scheduledSparkUs = 0;
    uint32_t dwellUs = 0;

    bool engineRunning = false;
};

extern EngineState engine;