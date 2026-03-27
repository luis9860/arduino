#include <Arduino.h>
#include "input_capture.h"
#include "config.h"
#include "engine_state.h"

static void isrCKP() {
    const uint32_t now = micros();
    const uint32_t period = now - engine.lastToothTimeUs;

    // Ignora primer pulso inválido
    if (engine.lastToothTimeUs == 0) {
        engine.lastToothTimeUs = now;
        return;
    }

    // Filtro mínimo contra ruido/rebote
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
    pinMode(PIN_CKP_IN, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIN_CKP_IN), isrCKP, RISING);
}

void inputCaptureTask() {
    // Reservado para filtros avanzados, estadística o captura por hardware más adelante
}