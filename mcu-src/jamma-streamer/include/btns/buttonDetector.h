#ifndef __BUTTON_DETECTOR__
#define __BUTTON_DETECTOR__

#include <Arduino.h>

#include "btns/buttonEvent.h"

#define NB_SHIFT_REGS 3
#define MAX_NB_OF_CALLBACKS 3

union ButtonsState {
    uint32_t states;
    byte values[4];
};

typedef void (*buttonEventCallback)(ButtonEvent*);

class ButtonDetector {
   private:
    ButtonsState currentBtns;
    ButtonsState previousBtns;
    uint8_t pload_pin;
    uint8_t enable_pin;
    uint8_t data_pin;
    uint8_t clock_pin;
    buttonEventCallback callbacks[MAX_NB_OF_CALLBACKS];
    uint8_t callbackIndex;

   public:
    ButtonDetector(uint8_t pload_pin, uint8_t enable_pin, uint8_t data_pin,
                   uint8_t clock_pin);
    ~ButtonDetector();
    // Add a callback called when event occurs on a button
    bool addButtonEventListener(buttonEventCallback);
    // Load registers with the current buttons' value
    void loadRegisters();
    // Read registers and store values, call callback function when buttons'
    // state change
    void readRegisters();
    // Get current buttons' state
    const ButtonsState* getButtonsState();
    // Get previous buttons' state
    const ButtonsState* getButtonsPreviousState();
#ifdef DEBUG_BUTTONS
     void printSerial();
#endif  // DEBUG_BUTTONS
};

#endif  // __BUTTON_DETECTOR__
