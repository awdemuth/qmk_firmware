#include "capsense.h"
#include <print.h>

// recalibrate_ms = 20000 * 1000; // set timeout really high so

// uint32_t calibration_value = 0x0FFFFFFFL;   // input large value for autocalibrate begin
// uint32_t lastCal = timer_read();         // set millis for start

void capsense_init(void) {
    // set up pins
    print("test");
    setPinOutput(CAPSENSE_PIN_SEND);    // sendpin to OUTPUT
    setPinInput(CAPSENSE_PIN_RECEIVE);  // receivePin to INPUT
    writePinLow(CAPSENSE_PIN_SEND);

    // calibrate
    // uint32_t total = 0;
    // for (uint8_t i = 0; i < samples; i++) {    // loop for samples parameter - simple lowpass filter
    //     uint32_t cycle_lenght = SenseOneCycle()
    // 	if (cycle_length < 0)  return -2;   // variable over timeout
    //     total = total + cycle_length
    // }

    // calibrate if time is greater than recalibrate_ms and new value differs less than 10% from previous value
    // this is an attempt to keep from calibrating when the sensor is seeing a "touched" signal

    // if ( (timer_elapsed32(lastCal) > recalibrate_ms) && abs(total  - calibration_value) < (int)(.10 * (float)leastTotal) ) {
    //     leastTotal = 0x0FFFFFFFL;          // reset for "autocalibrate"
    //     lastCal = timer_read();
    // }
    // // routine to subtract baseline (non-sensed capacitance) from sensor return
    // if (total < leastTotal) leastTotal = total;                 // set floor value to subtract from sensed value
    // return(total - leastTotal);
}

void capsense_read(void) {
    print("test");
    uint32_t total = 0;
    for (int i = 0; i < CAPSENSE_SAMPLES; i++) {  // loop for samples parameter - simple lowpass filter
        long cycle = capsense_read_one_cycle();
        if (cycle < 0) {
            return;
            // return cycle;  // error
        }
        total = total + cycle;
    }
    uprintf("capsense read", total);
    // return total;
}

long capsense_read_one_cycle(void) {
    long sense_iterations = 0;
    setPinInput(CAPSENSE_PIN_RECEIVE);
    writePinHigh(CAPSENSE_PIN_SEND);

    // while receive pin is LOW AND total is less than timeout
    while (!readPin(CAPSENSE_PIN_RECEIVE) && (sense_iterations < SENSE_MAX_ITERATIONS)) {
        sense_iterations++;
    }

    // set receive pin HIGH briefly to charge up fully
    setPinOutput(CAPSENSE_PIN_RECEIVE);
    writePinHigh(CAPSENSE_PIN_RECEIVE);  // receive pin is now HIGH AND OUTPUT
    setPinInput(CAPSENSE_PIN_RECEIVE);   // receivePin to INPUT (pullup is off)
    writePinLow(CAPSENSE_PIN_SEND);      // sendPin LOW

    // while receive pin is HIGH  AND total is less than timeout
    while (readPin(CAPSENSE_PIN_RECEIVE) && (sense_iterations < SENSE_MAX_ITERATIONS)) {
        sense_iterations++;
    }

    // set receive pin LOW briefly to discharge fully and prepare for next cycle
    writePinLow(CAPSENSE_PIN_RECEIVE);  // turn off input pullup
    setPinOutput(CAPSENSE_PIN_RECEIVE);
    writePinLow(CAPSENSE_PIN_RECEIVE);  // receive pin is now LOW and OUTPUT
                                        // todo: wait until cap has discharged?

    if (sense_iterations >= SENSE_MAX_ITERATIONS) {
        return -1;
    }

    return sense_iterations;
}

// int  led   = 12;
// long time  = 0;
// int  state = HIGH;

// boolean shine;
// boolean previous = false;

// int debounce = 200;

// CapacitiveSensor cs = CapacitiveSensor(4, 2);

// void setup() {
//     cs.set_CS_AutocaL_Millis(0xFFFFFFFF);
//     pinMode(led, OUTPUT);
// }

// void loop() {
//     long total = cs.capacitiveSensor(30);

//     shine = (total > 60);

//     // to toggle the state of state
//     if ((millis() - time) > debounce) {
//         if (shine)
//             state = HIGH;
//         else
//             state = LOW;

//         time = millis();
//     }
//     digitalWrite(led, state);
//     previous = shine;

//     Serial.println(millis() - time);
//     delay(10);
// }
