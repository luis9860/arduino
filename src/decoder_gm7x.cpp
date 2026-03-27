#include <Arduino.h>
#include "decoder_gm7x.h"
#include "engine_state.h"
#include "config.h"

void decoderGM7XInit() {
    engine.synced = false;
    engine.toothIndex = 0;
}

void decoderGM7XProcessTooth(uint32_t currentPeriodUs, uint32_t previousPeriodUs) {
    if (currentPeriodUs == 0 || currentPeriodUs > MAX_REASONABLE_TOOTH_US) {
        engine.synced = false;
        engine.toothIndex = 0;
        return;
    }

    if (!engine.synced) {
        engine.synced = true;
        engine.toothIndex = 0;
        return;
    }

    engine.toothIndex++;
    if (engine.toothIndex >= GM7X_LOGICAL_TEETH_PER_CAM_REV) {
        engine.toothIndex = 0;
    }

    (void)previousPeriodUs;
}