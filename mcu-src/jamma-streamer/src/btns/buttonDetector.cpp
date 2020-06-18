#include "btns/buttonDetector.h"

ButtonDetector::ButtonDetector(uint8_t pload_pin, uint8_t enable_pin, uint8_t data_pin, uint8_t clock_pin) {
    this->pload_pin = pload_pin;
    this->enable_pin = enable_pin;
    this->data_pin = data_pin;
    this->clock_pin = clock_pin;

    pinMode(pload_pin, OUTPUT);
    pinMode(enable_pin, OUTPUT);
    pinMode(data_pin, INPUT);
    pinMode(clock_pin, OUTPUT);

    digitalWrite(pload_pin, HIGH);
    digitalWrite(enable_pin, HIGH);
}

void ButtonDetector::loadRegisters() {
    digitalWrite(pload_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(pload_pin, HIGH);
    delayMicroseconds(5);
}

void ButtonDetector::readRegisters() {
    previousBtns = currentBtns;

    digitalWrite(clock_pin, HIGH);
    digitalWrite(enable_pin, LOW);
    currentBtns.values[2] = shiftIn(data_pin, clock_pin, MSBFIRST);
    currentBtns.values[1] = shiftIn(data_pin, clock_pin, MSBFIRST);
    currentBtns.values[0] = shiftIn(data_pin, clock_pin, MSBFIRST);
    digitalWrite(enable_pin, HIGH);
}

ButtonsState* ButtonDetector::getButtonsState() { return &currentBtns; }
ButtonsState* ButtonDetector::getButtonsPreviousState() { return &previousBtns; }

#ifdef DEBUG_BUTTONS
void ButtonDetector::printSerial() {
    for(int i=23; i>=0; i--) {
        Serial.print(bitRead(currentBtns.states, i));
        if (i % 8 == 0) {
            Serial.print(" ");
        }
    }
    Serial.println();

   /*for(int j=0; j<3; j++) {
       byte b = currentBtns.values[j];
       for (int i = 7; i >= 0; i--) {
           if (bitRead(b, i) == 1) {
               Serial.print("1");
           } else {
               Serial.print("0");
           }
       }
       Serial.print(" ");
   }
   Serial.println();
   */
}
#endif  // DEBUG_BUTTONS
