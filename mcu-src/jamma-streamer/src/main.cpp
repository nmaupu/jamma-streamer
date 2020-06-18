#include "btns/buttonDetector.h"
#include "btns/buttons.h"

#define PLOAD PD4
#define ENABLE PD5
#define DATA PD6
#define CLOCK PD7

#ifndef REFRESH_DELAY
#define REFRESH_DELAY 1000
#endif

#ifndef SERIAL_SPEED
#define SERIAL SPEED 19600
#endif

void displayButtonsChange(uint32_t, uint32_t);

ButtonDetector *detector;
const ButtonsState *st;
const ButtonsState *prev_st;

void setup() {
    Serial.begin(SERIAL_SPEED);
    Serial.print("Init...");
    detector = new ButtonDetector(PLOAD, ENABLE, DATA, CLOCK);
    Serial.println("Done.");
}

void loop() {
    detector->loadRegisters();
    detector->readRegisters();
#ifdef DEBUG_BUTTONS
    detector->printSerial();
#endif
    st = detector->getButtonsState();
    prev_st = detector->getButtonsPreviousState();

    // if XOR is zero -> no change between 2 loops
    if (((st->states)^(prev_st->states)) != 0 ){
        displayButtonsChange(prev_st->states, st->states);
    }

#if REFRESH_DELAY > 0
    delay(REFRESH_DELAY);
#endif
}

void displayButtonsChange(uint32_t prev, uint32_t cur) {
// get only changes with a XOR between previous and current states
#define XOR (prev ^ cur)

    // Check all buttons
    for (uint8_t i = 0; i < NB_BUTTONS; i++) {
#ifndef EXTENDED_JAMMA
        // Ignoring those extended buttons
        if (i == BTN_1P_4 || i == BTN_1P_5 || i == BTN_2P_4 || i == BTN_2P_5) {
            continue;
        }
#endif
        if ((XOR & BTN_MASK(buttons[i])) > 0) {
            Serial.print("Button ");
            Serial.print(buttonsName[buttons[i]]);
            Serial.print(" has been ");
            BTN_IS_PRESSED(cur, buttons[i]) ? Serial.print("pressed\n")
                                            : Serial.print("released\n");
        }
    }
}
