#include <Arduino.h>

#include "ignition_scheduler.h"
#include "engine_state.h"
#include "decoder_gm7x.h"
#include "engine_math.h"
#include "coil_driver.h"
#include "config.h"

static void clearSchedule() {
    engine.sparkScheduled = false;
    engine.scheduledCoilIndex = 0;
    engine.scheduledChargeStartUs = 0;
    engine.scheduledSparkUs = 0;
    engine.dwellUs = 0;
}

static void scheduleFixedSpark(uint32_t nowUs) {
    if (!ENABLE_FIXED_SPARK_TEST) {
        clearSchedule();
        return;
    }
if (engine.engineRpm <= 0.0f || !engine.synced || engine.toothIndex == TOOTH_INDEX_NOT_READY) {
    clearSchedule();
    return;
}

    // Mapa simple:
    // cada toothIndex representa un cilindro / canal secuencial.
    const uint8_t coilIndex = engine.toothIndex;

    if (coilIndex >= COIL_COUNT) {
        clearSchedule();
        return;
    }

    // Ángulo actual al inicio del sector
    const float currentAngle = engine.engineAngleDeg;

    // Dispara dentro del sector actual, cerca del final del diente lógico.
    // Ejemplo: en un sector de 120°, chispa fija a 10° antes del final.
    const float targetAngle = normalizeAngle720(
        currentAngle + ENGINE_TOOTH_ANGLE_DEG - FIXED_SPARK_ADVANCE_DEG
    );

    float deltaDeg = targetAngle - currentAngle;
    if (deltaDeg < 0.0f) {
        deltaDeg += 720.0f;
    }

    uint32_t delayToSparkUs = degreesToMicroseconds(deltaDeg, engine.engineRpm);

    uint32_t dwellUs = DEFAULT_DWELL_US;
    if (dwellUs > MAX_DWELL_US) {
        dwellUs = MAX_DWELL_US;
    }

    // Asegura margen mínimo
    if (delayToSparkUs <= (dwellUs + 50UL)) {
        delayToSparkUs += degreesToMicroseconds(ENGINE_TOOTH_ANGLE_DEG, engine.engineRpm);
    }

    engine.scheduledCoilIndex = coilIndex;
    engine.scheduledSparkUs = nowUs + delayToSparkUs;
    engine.scheduledChargeStartUs = engine.scheduledSparkUs - dwellUs;
    engine.dwellUs = dwellUs;
    engine.sparkScheduled = true;
}

void ignitionSchedulerInit() {
    engine.coilCharging = false;
    clearSchedule();
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

        engine.camRpm =
            calcCamRPMFromToothPeriod(period, CAM_TOOTH_ANGLE_DEG);

        engine.engineRpm =
            camRPMToEngineRPM(engine.camRpm);

if (engine.toothIndex != TOOTH_INDEX_NOT_READY) {
    engine.engineAngleDeg =
        calcEngineAngleDegFromCamTooth(engine.toothIndex, ENGINE_TOOTH_ANGLE_DEG);
}

        engine.engineRunning = (engine.engineRpm > 0.0f);

        digitalWrite(PIN_SYNC_LED, engine.synced ? HIGH : LOW);

        // Si justo llegó un nuevo tooth y aún quedó una bobina cargando por error,
        // apágala antes de reprogramar.
        if (engine.coilCharging) {
            coilOff(engine.scheduledCoilIndex);
            engine.coilCharging = false;
        }

        scheduleFixedSpark(micros());
    }

    const uint32_t nowUs = micros();

    if (engine.sparkScheduled) {
        if (!engine.coilCharging && nowUs >= engine.scheduledChargeStartUs) {
            coilOn(engine.scheduledCoilIndex);
            engine.coilCharging = true;
        }

        if (engine.coilCharging && nowUs >= engine.scheduledSparkUs) {
            coilOff(engine.scheduledCoilIndex);
            engine.coilCharging = false;
            clearSchedule();
        }
    }
}