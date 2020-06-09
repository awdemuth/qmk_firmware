#pragma once

#include "quantum.h"
#include "config_common.h"
#include "config.h"

#ifndef CAPSENSE_PIN_SEND
#    error "CAPSENSE_PIN_SEND must be set when using capsense"
#endif
#ifndef CAPSENSE_PIN_RECEIVE
#    error "CAPSENSE_PIN_RECEIVE must be set when using capsense"
#endif
#ifndef CAPSENSE_THRESHOLD
#    define CAPSENSE_THRESHOLD 30
#endif
#ifndef CAPSENSE_SAMPLES
#    define CAPSENSE_SAMPLES 3
#endif
#ifndef CAPSENSE_MAX_ITERATIONS
#    define CAPSENSE_MAX_ITERATIONS 500
#endif
#ifndef CAPSENSE_DEBOUNCE
#    define CAPSENSE_DEBOUNCE 30  // millis
#endif

void     capsense_init(void);
void     capsense_read(void);
uint32_t capsense_read_raw(void);
uint32_t capsense_read_one_cycle(void);

void capsense_update_kb(bool active);
void capsense_update_user(bool active);
