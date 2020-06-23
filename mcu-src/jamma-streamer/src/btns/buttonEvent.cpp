#include "btns/buttonEvent.h"

ButtonEvent::ButtonEvent(Button btn, ButtonStatus st) {
    this->btn = btn;
    this->status = st;
}

ButtonEvent::ButtonEvent() {}

const Button ButtonEvent::getButton() { return btn; }
const ButtonStatus ButtonEvent::getStatus() { return status; }
bool ButtonEvent::isPressed() { return status == PRESSED; }
bool ButtonEvent::isReleased() { return status == RELEASED; }
void ButtonEvent::setButton(Button btn) { this->btn = btn; }
void ButtonEvent::setStatus(ButtonStatus status) { this->status = status; }
