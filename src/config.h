

#pragma once

#include <Arduino.h>

// =========================
// Serial
// =========================
constexpr uint32_t SERIAL_BAUD = 115200UL;

// =========================
// Pines
// =========================
// Tu señal CAM real entra por INT2 en Mega2560
constexpr uint8_t PIN_CAM_IN = 19;
constexpr uint8_t PIN_SYNC_LED = 13;

// Salidas de bobina según tu hardware
constexpr uint8_t PIN_COIL_1 = 40;
constexpr uint8_t PIN_COIL_2 = 38;
constexpr uint8_t PIN_COIL_3 = 52;
constexpr uint8_t PIN_COIL_4 = 48;
constexpr uint8_t PIN_COIL_5 = 36;
constexpr uint8_t PIN_COIL_6 = 34;
constexpr uint8_t PIN_COIL_7 = 46; // placeholder / futuro uso

constexpr uint8_t COIL_COUNT = 6;

// =========================
// Decoder GM7X en CAM
// =========================
// 6 dientes lógicos útiles por vuelta de árbol
constexpr uint8_t GM7X_LOGICAL_TEETH_PER_CAM_REV = 6;

// Ángulo mecánico del árbol por diente
constexpr float CAM_TOOTH_ANGLE_DEG =
    360.0f / GM7X_LOGICAL_TEETH_PER_CAM_REV; // 60° CAM

// Ángulo equivalente del motor por diente
constexpr float ENGINE_TOOTH_ANGLE_DEG =
    720.0f / GM7X_LOGICAL_TEETH_PER_CAM_REV; // 120° motor

// Detección del diente/gap de referencia
constexpr float GM7X_SYNC_GAP_RATIO = 1.5f;

// =========================
// Filtros y seguridad
// =========================
constexpr uint32_t MIN_VALID_TOOTH_PERIOD_US = 200UL;
constexpr uint32_t ENGINE_STOP_TIMEOUT_US = 500000UL;
constexpr uint32_t MAX_REASONABLE_TOOTH_US = 300000UL;

// =========================
// Encendido fijo de prueba
// =========================
constexpr bool ENABLE_FIXED_SPARK_TEST = true;
constexpr float FIXED_SPARK_ADVANCE_DEG = 10.0f;

constexpr uint32_t DEFAULT_DWELL_US = 2000UL;
constexpr uint32_t MAX_DWELL_US = 4000UL;

// =========================
// Polaridad de salida
// =========================
// Ajusta si tu driver externo necesita nivel invertido
constexpr bool COIL_ACTIVE_STATE = HIGH;
constexpr bool COIL_INACTIVE_STATE = LOW;

// =========================
// Debug
// =========================
constexpr uint32_t DEBUG_PRINT_INTERVAL_MS = 200UL;