#include <Arduino.h>
#include "app.h"
#include "config.h"
#include "coil_driver.h"
#include "input_capture.h"
#include "decoder_gm7x.h"
#include "ignition_scheduler.h"
#include "safety.h"
#include "serial_debug.h"

void appSetup() {
    Serial.begin(SERIAL_BAUD);

    coilInit();
    inputCaptureInit();
    decoderGM7XInit();
    ignitionSchedulerInit();
    safetyInit();
    debugInit();
}

void appLoop() {
    inputCaptureTask();
    ignitionSchedulerTask();
    safetyTask();
    debugTask();
}
