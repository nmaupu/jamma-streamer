#include "btns/buttonDetector.h"

ButtonDetector::ButtonDetector(uint8_t pload_pin, uint8_t enable_pin, uint8_t data_pin, uint8_t clock_pin) {
    this->pload_pin = pload_pin;
    this->enable_pin = enable_pin;
    this->data_pin = data_pin;
    this->clock_pin = clock_pin;
    callbackIndex = 0;

    pinMode(pload_pin, OUTPUT);
    pinMode(enable_pin, OUTPUT);
    pinMode(data_pin, INPUT);
    pinMode(clock_pin, OUTPUT);

    digitalWrite(pload_pin, HIGH);
    digitalWrite(enable_pin, HIGH);
}

ButtonDetector::~ButtonDetector() {}

bool ButtonDetector::addButtonEventListener(buttonEventCallback callback) {
    if (callbackIndex >= MAX_NB_OF_CALLBACKS || callback == NULL) return false;
    callbacks[callbackIndex++] = callback;
    return true;
}

void ButtonDetector::loadRegisters() {
    digitalWrite(pload_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(pload_pin, HIGH);
    delayMicroseconds(5);
}

void ButtonDetector::readRegisters() {
    previousBtns = currentBtns;

    digitalWrite(clock_pin, HIGH);  // this is needed !
    digitalWrite(enable_pin, LOW);

    // iterate over all daisy chained shift registers
    for (int8_t i = (NB_SHIFT_REGS-1); i >= 0; --i) {
        currentBtns.values[i] = shiftIn(data_pin, clock_pin, MSBFIRST);
    }

    digitalWrite(enable_pin, HIGH);

    // verify changes with a XOR between previous and new values
    uint32_t x = previousBtns.states ^ currentBtns.states;
    ButtonEvent evt;
    if (x != 0 && callbackIndex > 0) {
        for(uint8_t i=0; i<NB_BUTTONS; i++) {
#ifndef EXTENDED_JAMMA
            // Ignoring those extended buttons
            if (i == BTN_1P_4 || i == BTN_1P_5 || i == BTN_2P_4 ||
                i == BTN_2P_5) {
                continue;
            }
#endif
            // Calling callback func for each change detected
            if((x & BTN_MASK(buttons[i])) > 0){
                evt.setButton(buttons[i]);
                evt.setStatus(BTN_IS_PRESSED(currentBtns.states, buttons[i])
                                  ? PRESSED
                                  : RELEASED);
                // Calling all callbacks
                for(uint8_t i=0; i<callbackIndex; i++) {
                    callbacks[i](&evt);
                }
            }
        }
    }
}

const ButtonsState* ButtonDetector::getButtonsState() { return &currentBtns; }
const ButtonsState* ButtonDetector::getButtonsPreviousState() { return &previousBtns; }

#ifdef DEBUG_BUTTONS
void ButtonDetector::printSerial() {
    for (int8_t i = (NB_SHIFT_REGS * 8 - 1); i >= 0; --i) {
        Serial.print(bitRead(currentBtns.states, i));
        if (i % 8 == 0) {
            Serial.print(" ");
        }
    }
    Serial.println("");
    Serial.flush();
}
#endif  // DEBUG_BUTTONS
