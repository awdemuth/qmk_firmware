#pragma once

#ifdef OLED_DRIVER_ENABLE
#    define OLED_DISPLAY_128X64
#endif

// EC11K encoders have a different resolution than other EC11 encoders.
// When using the default resolution of 4, if you notice your encoder skipping
// every other tick, lower the resolution to 2.
#define ENCODER_RESOLUTION 4

// make mod taps for home row feasible
// https://beta.docs.qmk.fm/features/feature_advanced_keycodes#permissive-hold
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 200
#define TAPPING_FORCE_HOLD

// Allows to use either side as the master. Look at the documentation for info:
// https://docs.qmk.fm/#/config_options?id=setting-handedness
#define EE_HANDS

// Allows media codes to properly register in macros and rotary encoder code
#define TAP_CODE_DELAY 10
