#pragma once
#include <Arduino.h>

float calcCamRPMFromToothPeriod(uint32_t toothPeriodUs, float camToothAngleDeg);
float camRPMToEngineRPM(float camRpm);
float calcEngineAngleDegFromCamTooth(uint8_t toothIndex, float engineToothAngleDeg);
uint32_t degreesToMicroseconds(float degrees, float engineRpm);
float normalizeAngle720(float angleDeg);