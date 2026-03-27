#include <Arduino.h>
#include "safety.h"
#include "engine_state.h"
#include "coil_driver.h"
#include "config.h"

void safetyInit() {
    // reservado para futuras protecciones
}

void safetyTask() {
    const uint32_t nowUs = micros();

    if (engine.lastToothTimeUs == 0) {
        return;
    }

    // Pérdida de señal / motor detenido
    if ((nowUs - engine.lastToothTimeUs) > ENGINE_STOP_TIMEOUT_US) {
        engine.camRpm = 0.0f;
        engine.engineRpm = 0.0f;
        engine.engineRunning = false;
        engine.synced = false;
        engine.toothIndex = 0;
        engine.sparkScheduled = false;
        engine.scheduledChargeStartUs = 0;
        engine.scheduledSparkUs = 0;
        engine.dwellUs = 0;

        if (engine.coilCharging || coilIsOn()) {
            coilOff();
            engine.coilCharging = false;
        }
    }
}