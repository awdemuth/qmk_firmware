
#pragma once

#include "quantum.h"

#include "config_common.h"
#ifndef CAPSENSE_PIN_SEND
#    define CAPSENSE_PIN_SEND B2
#endif
#ifndef CAPSENSE_PIN_RECEIVE
#    define CAPSENSE_PIN_RECEIVE B6
#endif
#ifndef CAPSENSE_THRESHOLD
#    define CAPSENSE_THRESHOLD 60
#endif
#ifndef CAPSENSE_SAMPLES
#    define CAPSENSE_SAMPLES 3
#endif
#ifndef CAPSENSE_MAX_ITERATIONS
#    define CAPSENSE_MAX_ITERATIONS 310 * 2000L  // approx 2s on 16mhz
#endif

void capsense_init(void);
void capsense_read(void);
long capsense_read_one_cycle(void);

void capsense_update_kb(int8_t index, bool clockwise);
void capsense_update_user(int8_t index, bool clockwise);

// int           error;
// unsigned long leastTotal;
// unsigned int  loopTimingFactor;
// unsigned long sense_max_iterations;
// unsigned long CS_AutocaL_Millis;
// unsigned long lastCal;
