#include "capsense.h"
#include "timer.h"
#include "print.h"

bool capsense_active = 0;
uint32_t capsense_debounce_timer = 0;
uint32_t capsense_calibration = 0;

__attribute__((weak)) void capsense_update_user(bool active) {}

__attribute__((weak)) void capsense_update_kb(bool active) { capsense_update_user(active); }

void capsense_init(void) {
    // set up pins to sense up cycle
    setPinOutput(CAPSENSE_PIN_SEND);
    setPinInput(CAPSENSE_PIN_RECEIVE);
    writePinLow(CAPSENSE_PIN_SEND);

    // calibrate
    capsense_read_raw(); // throw out first reading, we have to prime the cycle
    capsense_calibration = capsense_read_raw();
}

void capsense_read(void) {
    uint32_t read = capsense_read_raw();
    if(read < 0) {
        //error
        return;
    }
    int32_t diff = read - capsense_calibration;
    if(diff > CAPSENSE_THRESHOLD) {
        if(capsense_active) {
            //reset debounce timer for 'inactive' state change
            capsense_debounce_timer = 0;
            return;
        }
        if(capsense_debounce_timer == 0) {
            //set debounce timer for 'active' state change
            capsense_debounce_timer = timer_read32();
            return;
        }
        if(timer_elapsed32(capsense_debounce_timer) < CAPSENSE_DEBOUNCE) {
            //wait a little longer
            return;
        }
        capsense_active = true;
        capsense_update_kb(capsense_active);
#ifdef CAPSENSE_DEBUG
        dprint("on: ");
        dprintf("sensed %u ", read);
        dprintf("calibration %u ", capsense_calibration);
        dprintf("diff %d ", diff);
        dprintf("threshold %u \n", CAPSENSE_THRESHOLD);
#endif
    } else {
        if(!capsense_active) {
            //reset debounce timer for 'active' state change
            capsense_debounce_timer = 0;
            return;
        }
        if(capsense_debounce_timer == 0) {
            //set debounce timer for 'inactive' state change
            capsense_debounce_timer = timer_read32();
            return;
        }
        if(timer_elapsed32(capsense_debounce_timer) < CAPSENSE_DEBOUNCE) {
            //wait a little longer
            return;
        }
        capsense_active = false;
        capsense_update_kb(capsense_active);
#ifdef CAPSENSE_DEBUG
        dprint("off: ");
        dprintf("sensed %u ", read);
        dprintf("calibration %u ", capsense_calibration);
        dprintf("diff %d ", diff);
        dprintf("threshold %u \n", CAPSENSE_THRESHOLD);
#endif
    }
}

uint32_t capsense_read_raw(void) {
    uint32_t total = 0;
    for (int i = 0; i < CAPSENSE_SAMPLES; i++) {  // loop for samples parameter - simple lowpass filter
        long cycle = capsense_read_one_cycle();
        if (cycle < 0) {
            return cycle;
        }
        total = total + cycle;
    }
    return total;
}

uint32_t capsense_read_one_cycle(void) {
    uint32_t sense_iterations_up = 0;
    uint32_t sense_iterations_down = 0;

    setPinInput(CAPSENSE_PIN_RECEIVE);
    writePinHigh(CAPSENSE_PIN_SEND);

    // while receive pin is LOW AND total is less than timeout
    while (!readPin(CAPSENSE_PIN_RECEIVE) && (sense_iterations_up < CAPSENSE_MAX_ITERATIONS)) {
        sense_iterations_up++;
    }

    // set receive pin HIGH briefly to charge up
    setPinOutput(CAPSENSE_PIN_RECEIVE);
    writePinHigh(CAPSENSE_PIN_RECEIVE);  // receive pin is now HIGH AND OUTPUT
    setPinInput(CAPSENSE_PIN_RECEIVE);   // receivePin to INPUT (pullup is off)
    writePinLow(CAPSENSE_PIN_SEND);      // sendPin LOW

    // while receive pin is HIGH  AND total is less than timeout
    while (readPin(CAPSENSE_PIN_RECEIVE) && (sense_iterations_down < CAPSENSE_MAX_ITERATIONS)) {
        sense_iterations_down++;
    }

    // set receive pin LOW to discharge and prepare for next cycle
    writePinLow(CAPSENSE_PIN_RECEIVE);  // turn off input pullup
    setPinOutput(CAPSENSE_PIN_RECEIVE);
    writePinLow(CAPSENSE_PIN_RECEIVE);  // receive pin is now LOW and OUTPUT

#ifdef CAPSENSE_DEBUG
    dprintf("capsense up %u ", sense_iterations_up);
    dprintf("capsense down %u\n", sense_iterations_down);
#endif

    if((sense_iterations_up >= CAPSENSE_MAX_ITERATIONS) || (sense_iterations_down >= CAPSENSE_MAX_ITERATIONS)) {
        // out of bounds value read, loose cable?
        return -1;
    }
    return sense_iterations_up + sense_iterations_down;
}
