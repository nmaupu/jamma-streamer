#include <SD.h>
#include <SPI.h>

#include "globals.h"
#include "btns/buttonDetector.h"
#include "rtc/jammaTime.h"
#include "storage/sdstorage.h"

int availableMemory();
void serialLoggerButtonCallback(ButtonEvent* e);
void sdcardLoggerButtonCallback(ButtonEvent* e);

// Singleton objects
ButtonDetector* detector;
const ButtonsState* st;
const ButtonsState* prev_st;

SDStorage* sto;

JammaTime* time;

//
void setup() {
    Serial.begin(SERIAL_SPEED);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only
    }

    Serial.println(APP_NAME);
    Serial.print("version: ");
    Serial.println(APP_VERSION);
    Serial.println();
    delay(2000);

    /*
    Serial.print("Initializing SD card...");
    sto = new SDStorage(SD_CS, SD_MOSI,SD_MISO, SD_CLK);
    if(!sto->initSDCard()) {
        Serial.println("Failed. Card present ? Formatted as FAT16/32 ?");
    } else {
        Serial.println("OK");
    }
    */

    // Buttons detection
    //Serial.print("Configuring buttons detection...");
    //detector = new ButtonDetector(PLOAD, ENABLE, DATA, CLOCK);
    //detector->addButtonEventListener(serialLoggerButtonCallback);
    //detector->addButtonEventListener(sdcardLoggerButtonCallback);
    //Serial.println("OK");

    // RTC - Real Time Clock
    Serial.print("Initializing RTC...");
    time = new JammaTime();
    Serial.println("OK");

    //Serial.println("Listening for inputs.");
}

void loop() {
    Serial.print("millis=");
    Serial.print(millis());
    Serial.print(", time=");
    Serial.println(time->getJammaTime());

    //detector->loadRegisters();
    //detector->readRegisters();

#ifdef DEBUG_BUTTONS
    detector->printSerial();
#endif

#if REFRESH_DELAY_US > 0 && REFRESH_DELAY_US < 65535
    delayMicroseconds(REFRESH_DELAY_US);
#elif REFRESH_DELAY_US > 0
    delay(REFRESH_DELAY_US/1000);
#endif
}

// Function called when a button state has changed.
void serialLoggerButtonCallback(ButtonEvent* e) {
    Serial.print("Button ");
    Serial.print(buttonsName[e->getButton()]);
    Serial.print(" has been ");
    Serial.println(e->isPressed() ? "pressed" : "released");
    Serial.flush();
}

void sdcardLoggerButtonCallback(ButtonEvent* e) {
    Serial.println("SDCard logger not implemented yet.");
    Serial.flush();
}
