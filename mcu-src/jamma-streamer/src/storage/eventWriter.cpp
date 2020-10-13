#include "storage/eventWriter.h"

EventWriter::EventWriter(SDStorage* s, JammaTime* t) {
    this->storage = s;
    this->time = t;
}

void EventWriter::writeEvent(ButtonEvent* e) {
    if (e == NULL) {
        Serial.println("ButtonEvent is NULL !");
        return;
    }
    File* file = storage->getLogFile();
    file->printf("%s|%s|%s\n", time->getJammaTime(), getButtonName(e->getButton()), e->isPressed() ? "P" : "R");
    file->flush();
}
