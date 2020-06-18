#include "btns/buttonDetector.h"

#include "btns/buttons.h"
#define PLOAD PD4
#define ENABLE PD5
#define DATA PD6
#define CLOCK PD7

#ifndef REFRESH_DELAY
#define REFRESH_DELAY 1000
#endif

void disBtnsChange(uint32_t, uint32_t);
void disBtnStatus(uint32_t, uint32_t);

ButtonDetector *detector;
ButtonsState *st;
ButtonsState *prev_st;

void setup() {
    Serial.begin(115200);
    Serial.print("Initialization... ");

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
    if (((st->states)^(prev_st->states)) == 0 ){
#ifdef DEBUG_BUTTONS
        Serial.println("No change detected");
#endif
    } else {
        disBtnsChange(prev_st->states, st->states);
    }

    delay(REFRESH_DELAY);
}

void disBtnsChange(uint32_t prev, uint32_t cur) {
  uint32_t x = prev ^ cur; // get only changes

  if ((x & BTN_1P_UP) > 0) disBtnStatus(cur, BTN_1P_UP);
  if ((x & BTN_1P_START) > 0) disBtnStatus(cur, BTN_1P_START);
  if ((x & BTN_1P_COIN) > 0) disBtnStatus(cur, BTN_1P_COIN);
  if ((x & BTN_TEST) > 0) disBtnStatus(cur, BTN_TEST);
  if ((x & BTN_SERVICE) > 0) disBtnStatus(cur, BTN_SERVICE);
  if ((x & BTN_2P_COIN) > 0) disBtnStatus(cur, BTN_2P_COIN);
  if ((x & BTN_2P_START) > 0) disBtnStatus(cur, BTN_2P_START);
  if ((x & BTN_2P_UP) > 0) disBtnStatus(cur, BTN_2P_UP);
  if ((x & BTN_1P_1) > 0) disBtnStatus(cur, BTN_1P_1);
  if ((x & BTN_1P_RIGHT) > 0) disBtnStatus(cur, BTN_1P_RIGHT);
  if ((x & BTN_1P_LEFT) > 0) disBtnStatus(cur, BTN_1P_LEFT);
  if ((x & BTN_1P_DOWN) > 0) disBtnStatus(cur, BTN_1P_DOWN);
  if ((x & BTN_2P_DOWN) > 0) disBtnStatus(cur, BTN_2P_DOWN);
  if ((x & BTN_2P_LEFT) > 0) disBtnStatus(cur, BTN_2P_LEFT);
  if ((x & BTN_2P_RIGHT) > 0) disBtnStatus(cur, BTN_2P_RIGHT);
  if ((x & BTN_2P_1) > 0) disBtnStatus(cur, BTN_2P_1);
#ifdef EXTENDED_JAMMA
  if ((x & BTN_1P_5) > 0) disBtnStatus(cur, BTN_1P_5);
  if ((x & BTN_1P_4) > 0) disBtnStatus(cur, BTN_1P_4);
#endif
  if ((x & BTN_1P_3) > 0) disBtnStatus(cur, BTN_1P_3);
  if ((x & BTN_1P_2) > 0) disBtnStatus(cur, BTN_1P_2);
  if ((x & BTN_2P_2) > 0) disBtnStatus(cur, BTN_2P_2);
  if ((x & BTN_2P_3) > 0) disBtnStatus(cur, BTN_2P_3);
#ifdef EXTENDED_JAMMA
  if ((x & BTN_2P_4) > 0) disBtnStatus(cur, BTN_2P_4);
  if ((x & BTN_2P_5) > 0) disBtnStatus(cur, BTN_2P_5);
#endif
}

void disBtnStatus(uint32_t cur, uint32_t btn) {
    Serial.print("Button ");
    Serial.print(getButtonAsString(btn));
    Serial.print(" has been ");
    if (BTN_IS_PRESSED(cur, btn))
        Serial.print("pressed");
    else
        Serial.print("released");

    Serial.println();
}
