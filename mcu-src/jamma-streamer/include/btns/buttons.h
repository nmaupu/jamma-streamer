#ifndef __BUTTONS_HEADER__
#define __BUTTONS_HEADER__

#include <Arduino.h>

// Buttons are active LOW !
#define BTN_IS_PRESSED(s, b) (((s) & (b)) == 0)

// Buttons bit mapping corresponding to how they are arranged on the shiftregisters' inputs
// TILT button is not mapped !
#define BTN_1P_UP 1UL << 0      // jamma pin 18
#define BTN_1P_START 1UL << 1   // jamma pin 17
#define BTN_1P_COIN 1UL << 2    // jamma pin 16
#define BTN_TEST 1UL << 3       // jamma pin 15
#define BTN_SERVICE 1UL << 4    // jamma pin R
#define BTN_2P_COIN 1UL << 5    // jamma pin T
#define BTN_2P_START 1UL << 6   // jamma pin U
#define BTN_2P_UP 1UL << 7      // jamma pin V
#define BTN_1P_1 1UL << 8       // jamma pin 22
#define BTN_1P_RIGHT 1UL << 9   // jamma pin 21
#define BTN_1P_LEFT 1UL << 10   // jamma pin 20
#define BTN_1P_DOWN 1UL << 11   // jamma pin 19
#define BTN_2P_DOWN 1UL << 12   // jamma pin W
#define BTN_2P_LEFT 1UL << 13   // jamma pin X
#define BTN_2P_RIGHT 1UL << 14  // jamma pin Y
#define BTN_2P_1 1UL << 15      // jamma pin Z
#ifdef EXTENDED_JAMMA
#define BTN_1P_5 1UL << 16  // jamma pin 26 - unreliable if not connected
#define BTN_1P_4 1UL << 17  // jamma pin 25 - unreliable if not connected
#endif
#define BTN_1P_3 1UL << 18  // jamma pin 24
#define BTN_1P_2 1UL << 19  // jamma pin 23
#define BTN_2P_2 1UL << 20  // jamma pin a
#define BTN_2P_3 1UL << 21  // jamma pin b
#ifdef EXTENDED_JAMMA
#define BTN_2P_4 1UL << 22  // jamma pin c - unreliable if not connected
#define BTN_2P_5 1UL << 23  // jamma pin d - unreliable if not connected
#endif

/*
#define BTN_1 0
#define BTN_2 1
#define BTN_3 2
const char buttons[24] = {
    BTN_1,
    BTN_2,
    BTN_3
};*/

const char* getButtonAsString(uint32_t btn) {
    switch (btn) {
        case BTN_1P_UP:
            return "1P UP";
        case BTN_1P_START:
            return "1P START";
        case BTN_1P_COIN:
            return "1P COIN";
        case BTN_TEST:
            return "TEST";
        case BTN_SERVICE:
            return "SERVICE";
        case BTN_2P_COIN:
            return "2P COIN";
        case BTN_2P_START:
            return "2P START";
        case BTN_2P_UP:
            return "2P UP";
        case BTN_1P_1:
            return "1P BTN 1";
        case BTN_1P_RIGHT:
            return "1P RIGHT";
        case BTN_1P_LEFT:
            return "1P LEFT";
        case BTN_1P_DOWN:
            return "1P DOWN";
        case BTN_2P_DOWN:
            return "2P DOWN";
        case BTN_2P_LEFT:
            return "2P LEFT";
        case BTN_2P_RIGHT:
            return "2P RIGHT";
        case BTN_2P_1:
            return "2P BTN 1";
#ifdef EXTENDED_JAMMA
        case BTN_1P_5:
            return "1P BTN 5";
        case BTN_1P_4:
            return "1P BTN 4";
#endif
        case BTN_1P_3:
            return "1P BTN 3";
        case BTN_1P_2:
            return "1P BTN 2";
        case BTN_2P_2:
            return "2P BTN 2";
        case BTN_2P_3:
            return "2P BTN 3";
#ifdef EXTENDED_JAMMA
        case BTN_2P_4:
            return "2P BTN 4";
        case BTN_2P_5:
            return "2P BTN 5";
#endif
        default:
            return "undef";
    }
}

#endif  // __BUTTONS_HEADER__
