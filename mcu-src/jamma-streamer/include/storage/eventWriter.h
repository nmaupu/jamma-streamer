#ifndef __EVENT_WRITER_H__
#define __EVENT_WRITER_H__

#include "sdstorage.h"
#include "rtc/jammaTime.h"
#include "btns/buttonEvent.h"
#include <btns/buttons.h>
#include <util/atomic.h>

class EventWriter {
   private:
    SDStorage* storage;
    JammaTime* time;
    char buf[64];

   public:
    EventWriter(SDStorage* s, JammaTime* t);
    // writeEvent writes an event to a log file pointed by storage
    void writeEvent(ButtonEvent* e);
};

#endif // __EVENT_WRITER_H__
