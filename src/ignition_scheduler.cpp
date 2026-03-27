#include <Arduino.h>
#include "ignition_scheduler.h"
#include "engine_state.h"
#include "decoder_gm7x.h"
#include "engine_math.h"
#include "coil_driver.h"
#include "config.h"

static void scheduleFixedSpark(uint32_t nowUs) {
    if (!ENABLE_FIXED_SPARK_TEST) {
        engine.sparkScheduled = false;
        return;
    }

    if (engine.engineRpm <= 0.0f || !engine.synced) {
        engine.sparkScheduled = false;
        return;
    }

    const float currentAngle = engine.engineAngleDeg;

    // Ejemplo: chispa fija 10° antes del PMS del final del ciclo
    float targetAngle = normalizeAngle720(720.0f - FIXED_SPARK_ADVANCE_DEG);

    float deltaDeg = targetAngle - currentAngle;
    if (deltaDeg < 0.0f) {
        deltaDeg += 720.0f;
    }

    uint32_t delayToSparkUs = degreesToMicroseconds(deltaDeg, engine.engineRpm);
    uint32_t dwellUs = DEFAULT_DWELL_US;

    if (dwellUs > MAX_DWELL_US) {
        dwellUs = MAX_DWELL_US;
    }

    if (delayToSparkUs <= dwellUs + 50UL) {
        delayToSparkUs += degreesToMicroseconds(ENGINE_TOOTH_ANGLE_DEG, engine.engineRpm);
    }

    engine.scheduledSparkUs = nowUs + delayToSparkUs;
    engine.scheduledChargeStartUs = engine.scheduledSparkUs - dwellUs;
    engine.dwellUs = dwellUs;
    engine.sparkScheduled = true;
}

void ignitionSchedulerInit() {
    engine.sparkScheduled = false;
    engine.scheduledChargeStartUs = 0;
    engine.scheduledSparkUs = 0;
    engine.dwellUs = 0;
}

void ignitionSchedulerTask() {
    uint32_t period = 0;
    uint32_t prevPeriod = 0;
    bool hasNewTooth = false;

    noInterrupts();
    if (engine.newTooth) {
        engine.newTooth = false;
        period = engine.toothPeriodUs;
        prevPeriod = engine.prevToothPeriodUs;
        hasNewTooth = true;
    }
    interrupts();

    if (hasNewTooth) {
        decoderGM7XProcessTooth(period, prevPeriod);

        engine.camRpm = calcCamRPMFromToothPeriod(period, CAM_TOOTH_ANGLE_DEG);
        engine.engineRpm = camRPMToEngineRPM(engine.camRpm);
        engine.engineAngleDeg = calcEngineAngleDegFromCamTooth(engine.toothIndex, ENGINE_TOOTH_ANGLE_DEG);
        engine.engineRunning = (engine.engineRpm > 0.0f);

        digitalWrite(PIN_SYNC_LED, engine.synced ? HIGH : LOW);

        scheduleFixedSpark(micros());
    }

    const uint32_t nowUs = micros();

    if (engine.sparkScheduled) {
        if (!engine.coilCharging && nowUs >= engine.scheduledChargeStartUs) {
            coilOn();
            engine.coilCharging = true;
        }

        if (engine.coilCharging && nowUs >= engine.scheduledSparkUs) {
            coilOff();
            engine.coilCharging = false;
            engine.sparkScheduled = false;
            engine.scheduledChargeStartUs = 0;
            engine.scheduledSparkUs = 0;
            engine.dwellUs = 0;
        }
    }
}