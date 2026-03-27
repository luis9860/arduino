#include <Arduino.h>
#include "serial_debug.h"
#include "engine_state.h"
#include "coil_driver.h"
#include "config.h"

void debugInit() {
}

void debugTask() {
    static uint32_t lastPrintMs = 0;
    const uint32_t nowMs = millis();

    if ((nowMs - lastPrintMs) < DEBUG_PRINT_INTERVAL_MS) {
        return;
    }

    lastPrintMs = nowMs;

    Serial.print("CAM_RPM=");
    Serial.print(engine.camRpm, 1);

    Serial.print(" | ENG_RPM=");
    Serial.print(engine.engineRpm, 1);

    Serial.print(" | Sync=");
    Serial.print(engine.synced ? "YES" : "NO");

    Serial.print(" | Tooth=");
    Serial.print(engine.toothIndex);

    Serial.print(" | EngAngle=");
    Serial.print(engine.engineAngleDeg, 1);

    Serial.print(" | PeriodUs=");
    Serial.print(engine.toothPeriodUs);

    Serial.print(" | Coil=");
    Serial.print(coilIsOn() ? "ON" : "OFF");

    Serial.print(" | Charging=");
    Serial.print(engine.coilCharging ? "YES" : "NO");

    Serial.print(" | SparkScheduled=");
    Serial.print(engine.sparkScheduled ? "YES" : "NO");

    Serial.print(" | ChargeAt=");
    Serial.print(engine.scheduledChargeStartUs);

    Serial.print(" | SparkAt=");
    Serial.println(engine.scheduledSparkUs);
}