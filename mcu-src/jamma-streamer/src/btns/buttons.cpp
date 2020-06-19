#include "btns/buttons.h"

// Order corresponds to how it is cabled into shift registers, do not change !
Button buttons[NB_BUTTONS] = {
    BTN_1P_UP,   BTN_1P_START, BTN_1P_COIN, BTN_TEST,    BTN_SERVICE,
    BTN_2P_COIN, BTN_2P_START, BTN_2P_UP,   BTN_1P_1,    BTN_1P_RIGHT,
    BTN_1P_LEFT, BTN_1P_DOWN,  BTN_2P_DOWN, BTN_2P_LEFT, BTN_2P_RIGHT,
    BTN_2P_1,    BTN_1P_5,     BTN_1P_4,    BTN_1P_3,    BTN_1P_2,
    BTN_2P_2,    BTN_2P_3,     BTN_2P_4,    BTN_2P_5};

const char* buttonsName[NB_BUTTONS] = {
    "1P UP",    "1P START", "1P COIN",  "TEST",     "SERVICE", "2P COIN",
    "2P START", "2P UP",    "1P 1",     "1P RIGHT", "1P LEFT", "1P DOWN",
    "2P DOWN",  "2P LEFT",  "2P RIGHT", "2P 1",     "1P 5",    "1P 4",
    "1P 3",     "1P 2",     "2P 2",     "2P 3",     "2P 4",    "2P 5"};

const char* getButtonName(Button btn) {
    if (btn < NB_BUTTONS)
        return buttonsName[btn];
    else
        return "undef";
}
