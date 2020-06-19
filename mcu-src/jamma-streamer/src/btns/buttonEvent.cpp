#include "btns/buttonEvent.h"

ButtonEvent::ButtonEvent(Button btn, ButtonStatus st) {
    this->btn = btn;
    this->status = st;
}

const Button ButtonEvent::getButton() { return btn; }
const ButtonStatus ButtonEvent::getStatus() { return status; }
bool ButtonEvent::isPressed() { return status == PRESSED; }
bool ButtonEvent::isReleased() { return status == RELEASED; }
