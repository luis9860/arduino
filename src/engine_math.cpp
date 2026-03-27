#include "engine_math.h"

float calcCamRPMFromToothPeriod(uint32_t toothPeriodUs, float camToothAngleDeg) {
    if (toothPeriodUs == 0 || camToothAngleDeg <= 0.0f) {
        return 0.0f;
    }

    const float teethPerCamRev = 360.0f / camToothAngleDeg;
    const float camRevPeriodUs = toothPeriodUs * teethPerCamRev;

    if (camRevPeriodUs <= 0.0f) {
        return 0.0f;
    }

    return 60000000.0f / camRevPeriodUs;
}

float camRPMToEngineRPM(float camRpm) {
    return camRpm * 2.0f;
}

float calcEngineAngleDegFromCamTooth(uint8_t toothIndex, float engineToothAngleDeg) {
    return toothIndex * engineToothAngleDeg;
}

uint32_t degreesToMicroseconds(float degrees, float engineRpm) {
    if (engineRpm <= 0.0f) {
        return 0;
    }

    const float usPerEngineRev = 60000000.0f / engineRpm;
    const float usPerDeg = usPerEngineRev / 360.0f;
    const float result = degrees * usPerDeg;

    if (result <= 0.0f) {
        return 0;
    }

    return static_cast<uint32_t>(result);
}

float normalizeAngle720(float angleDeg) {
    while (angleDeg < 0.0f) {
        angleDeg += 720.0f;
    }

    while (angleDeg >= 720.0f) {
        angleDeg -= 720.0f;
    }

    return angleDeg;
}