#ifndef __BUTTON_EVENT_HEADER__
#define __BUTTON_EVENT_HEADER__

#include "btns/buttons.h"

enum ButtonStatus { PRESSED, RELEASED };

class ButtonEvent {
   private:
    Button btn;
    ButtonStatus status;

   public:
    ButtonEvent(Button btn, ButtonStatus st);
    const Button getButton();
    const ButtonStatus getStatus();
    bool isPressed();
    bool isReleased();
};

#endif  // __BUTTON_EVENT_HEADER__
