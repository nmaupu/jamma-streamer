#ifndef __BUTTON_DETECTOR__
#define __BUTTON_DETECTOR__

#include "arduino.h"

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
     void loadRegisters();
     void readRegisters();
     const ButtonsState* getButtonsState();
     const ButtonsState* getButtonsPreviousState();
#ifdef DEBUG_BUTTONS
     void printSerial();
#endif  // DEBUG_BUTTONS
};

#endif  // __BUTTON_DETECTOR__
