#ifndef __BUTTON_DETECTOR__
#define __BUTTON_DETECTOR__

#include <Arduino.h>
#include "btns/buttonEvent.h"

#define NB_SHIFT_REGS 3

union ButtonsState {
    uint32_t states;
    byte values[4];
};

class ButtonDetector {
    private:
     ButtonsState currentBtns;
     ButtonsState previousBtns;
     uint8_t pload_pin;
     uint8_t enable_pin;
     uint8_t data_pin;
     uint8_t clock_pin;

    public:
     ButtonDetector(uint8_t pload_pin, uint8_t enable_pin, uint8_t data_pin, uint8_t clock_pin);
     // Load registers with the current buttons' value
     void loadRegisters();
     // Read registers and store values, call callback function when buttons' state change
     void readRegisters(void (*callback)(ButtonEvent));
     // Get current buttons' state
     const ButtonsState* getButtonsState();
     // Get previous buttons' state
     const ButtonsState* getButtonsPreviousState();
#ifdef DEBUG_BUTTONS
     void printSerial();
#endif  // DEBUG_BUTTONS
};

#endif  // __BUTTON_DETECTOR__
