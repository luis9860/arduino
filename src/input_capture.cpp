#include <Arduino.h>

#include "input_capture.h"
#include "config.h"
#include "engine_state.h"

static void isrCAM() {
    const uint32_t now = micros();
    const uint32_t period = now - engine.lastToothTimeUs;

    // Primer pulso: solo inicializa referencia temporal
    if (engine.lastToothTimeUs == 0) {
        engine.lastToothTimeUs = now;
        return;
    }

    // Filtro mínimo contra ruido
    if (period < MIN_VALID_TOOTH_PERIOD_US) {
        return;
    }

    engine.prevToothPeriodUs = engine.toothPeriodUs;
    engine.toothPeriodUs = period;
    engine.lastToothTimeUs = now;
    engine.newTooth = true;
    engine.toothCounter++;
}

void inputCaptureInit() {
    pinMode(PIN_CAM_IN, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN_CAM_IN), isrCAM, RISING);
}

void inputCaptureTask() {
    // Reservado para filtros avanzados o captura por timer más adelante
}