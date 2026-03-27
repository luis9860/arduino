#pragma once

#include <Arduino.h>
    static const uint8_t TOOTH_INDEX_NOT_READY = 0xFF;

struct EngineState {
    volatile bool newTooth = false;
    volatile uint32_t lastToothTimeUs = 0;
    volatile uint32_t toothPeriodUs = 0;
    volatile uint32_t prevToothPeriodUs = 0;

    volatile bool synced = false;
    volatile uint8_t toothIndex = 0;      // 0..5
    volatile uint32_t toothCounter = 0;

    float camRpm = 0.0f;
    float engineRpm = 0.0f;
    float engineAngleDeg = 0.0f;

    bool engineRunning = false;

    bool coilCharging = false;
    bool sparkScheduled = false;
    uint8_t scheduledCoilIndex = 0;

    uint32_t scheduledChargeStartUs = 0;
    uint32_t scheduledSparkUs = 0;
    uint32_t dwellUs = 0;
};

extern EngineState engine;