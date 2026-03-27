#pragma once
#include <Arduino.h>

// =========================
// Serial
// =========================
constexpr uint32_t SERIAL_BAUD = 115200UL;

// =========================
// Pines
// =========================
constexpr uint8_t PIN_CKP_IN   = 2;   // Aquí realmente será tu señal CAM limpia
constexpr uint8_t PIN_COIL_OUT = 9;
constexpr uint8_t PIN_SYNC_LED = 13;

// =========================
// Decoder GM7X en CAM
// =========================
constexpr uint8_t GM7X_LOGICAL_TEETH_PER_CAM_REV = 6;

// Ángulo mecánico del árbol por diente
constexpr float CAM_TOOTH_ANGLE_DEG = 360.0f / GM7X_LOGICAL_TEETH_PER_CAM_REV;   // 60° CAM

// Ángulo equivalente del motor por diente
constexpr float ENGINE_TOOTH_ANGLE_DEG = 720.0f / GM7X_LOGICAL_TEETH_PER_CAM_REV; // 120° motor

// =========================
// Filtros y seguridad
// =========================
constexpr uint32_t MIN_VALID_TOOTH_PERIOD_US = 200UL;
constexpr uint32_t ENGINE_STOP_TIMEOUT_US    = 500000UL;
constexpr uint32_t MAX_REASONABLE_TOOTH_US   = 300000UL;

// =========================
// Encendido de prueba
// =========================
constexpr bool ENABLE_FIXED_SPARK_TEST = true;
constexpr float FIXED_SPARK_ADVANCE_DEG = 10.0f;
constexpr uint32_t DEFAULT_DWELL_US = 2000UL;
constexpr uint32_t MAX_DWELL_US     = 4000UL;

// =========================
// Debug
// =========================
constexpr uint32_t DEBUG_PRINT_INTERVAL_MS = 200UL;