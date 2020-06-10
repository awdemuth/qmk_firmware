
#pragma once

#include "config_common.h"

/*
#define MATRIX_ROWS 8
#define MATRIX_COLS 8
*/
#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x0000
#define DEVICE_VER 0x0001
#define MANUFACTURER Okke
#define PRODUCT Capsense test board
#define DESCRIPTION awesome capsense

/* key matrix size */
/* Rows are doubled up */
#define MATRIX_ROWS 1
#define MATRIX_COLS 1

#define CAPSENSE_PIN_SEND B2
#define CAPSENSE_PIN_RECEIVE B6
#define CAPSENSE_DEBUG

// wiring
#define MATRIX_ROW_PINS \
    { B3 }
#define MATRIX_COL_PINS \
    { B1 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define DEBUG_MATRIX_SCAN_RATE

/* ps2 mouse */
#ifdef PS2_USE_BUSYWAIT
#    define PS2_CLOCK_PORT PORTD
#    define PS2_CLOCK_PIN PIND
#    define PS2_CLOCK_DDR DDRD
#    define PS2_CLOCK_BIT 3
#    define PS2_DATA_PORT PORTD
#    define PS2_DATA_PIN PIND
#    define PS2_DATA_DDR DDRD
#    define PS2_DATA_BIT 2
#endif


#ifdef PS2_USE_INT
#define PS2_CLOCK_PORT  PORTD
#define PS2_CLOCK_PIN   PIND
#define PS2_CLOCK_DDR   DDRD
#define PS2_CLOCK_BIT   3
#define PS2_DATA_PORT   PORTD
#define PS2_DATA_PIN    PIND
#define PS2_DATA_DDR    DDRD
#define PS2_DATA_BIT    2

#define PS2_INT_INIT()  do {    \
    EICRA |= ((1<<ISC30) |      \
              (0<<ISC31));      \
} while (0)
#define PS2_INT_ON()  do {      \
    EIMSK |= (1<<INT3);         \
} while (0)
#define PS2_INT_OFF() do {      \
    EIMSK &= ~(1<<INT3);        \
} while (0)
#define PS2_INT_VECT   INT3_vect
#endif
