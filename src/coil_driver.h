#pragma once

#include <Arduino.h>

void coilInit();
void coilOn(uint8_t coilIndex);
void coilOff(uint8_t coilIndex);
void coilAllOff();
bool coilIsOn(uint8_t coilIndex);