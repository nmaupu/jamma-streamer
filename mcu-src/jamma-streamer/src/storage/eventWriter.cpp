#include "storage/eventWriter.h"

EventWriter::EventWriter(SDStorage* s, JammaTime* t) {
    this->storage = s;
    this->time = t;
}

void EventWriter::writeEvent(ButtonEvent* e) {
    //SdFile* file = storage->openLogFile();
    //sprintf(buf, "%s|%s|%s", time->getJammaTime(), getButtonName(e->getButton()), e->isPressed() ? "P" : "R");
    /*
    file->printf("%s\n", buf);
    Serial.println("3");
    file->flush();
    Serial.println("4");
    file->close();
    Serial.println("5");
    */
}
