#ifndef __BUTTONS_HEADER__
#define __BUTTONS_HEADER__

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint8_t Button;

#define NB_BUTTONS 24

// Buttons are active LOW !
#define BTN_MASK(b) (1UL << (b))
#define BTN_IS_PRESSED(s, b) (((s) & (BTN_MASK(b))) == 0)

// Buttons bit mapping corresponding to how they are arranged on the shiftregisters' inputs
// TILT button is not mapped !
#define BTN_1P_UP 0      // jamma pin 18
#define BTN_1P_START 1   // jamma pin 17
#define BTN_1P_COIN 2    // jamma pin 16
#define BTN_TEST 3       // jamma pin 15
#define BTN_SERVICE 4    // jamma pin R
#define BTN_2P_COIN 5    // jamma pin T
#define BTN_2P_START 6   // jamma pin U
#define BTN_2P_UP 7      // jamma pin V
#define BTN_1P_1 8       // jamma pin 22
#define BTN_1P_RIGHT 9   // jamma pin 21
#define BTN_1P_LEFT 10   // jamma pin 20
#define BTN_1P_DOWN 11   // jamma pin 19
#define BTN_2P_DOWN 12   // jamma pin W
#define BTN_2P_LEFT 13   // jamma pin X
#define BTN_2P_RIGHT 14  // jamma pin Y
#define BTN_2P_1 15      // jamma pin Z
#define BTN_1P_5 16      // jamma pin 26 - unreliable if not connected
#define BTN_1P_4 17      // jamma pin 25 - unreliable if not connected
#define BTN_1P_3 18      // jamma pin 24
#define BTN_1P_2 19      // jamma pin 23
#define BTN_2P_2 20      // jamma pin a
#define BTN_2P_3 21      // jamma pin b
#define BTN_2P_4 22      // jamma pin c - unreliable if not connected
#define BTN_2P_5 23      // jamma pin d - unreliable if not connected

extern Button buttons[NB_BUTTONS];
extern const char* buttonsName[NB_BUTTONS];
const char* getButtonName(Button btn);

#ifdef __cplusplus
}
#endif

#endif  // __BUTTONS_HEADER__
