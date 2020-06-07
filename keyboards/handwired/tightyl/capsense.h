
#pragma once

#include "quantum.h"

void capsense_init(void);
void capsense_read(void);

void capsense_update_kb(int8_t index, bool clockwise);
void capsense_update_user(int8_t index, bool clockwise);

int           error;
unsigned long leastTotal;
unsigned int  loopTimingFactor;
unsigned long sense_max_iterations;
unsigned long CS_AutocaL_Millis;
unsigned long lastCal;
