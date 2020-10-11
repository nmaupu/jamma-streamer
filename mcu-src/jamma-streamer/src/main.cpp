#include <SD.h>
#include <SPI.h>

#include "globals.h"
#include "btns/buttonDetector.h"
#include "rtc/jammaTime.h"
#include "storage/sdstorage.h"
#include "storage/eventWriter.h"

void serialLoggerButtonCallback(ButtonEvent* e);
void sdcardLoggerButtonCallback(ButtonEvent* e);

// Singleton objects
ButtonDetector* detector;
const ButtonsState* st;
const ButtonsState* prev_st;

char logFilename[32];
SDStorage* sto;

JammaTime* time;

EventWriter* writer;

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

    // Buttons detection
    Serial.print("Configuring buttons detection...");
    detector = new ButtonDetector(PLOAD, ENABLE, DATA, CLOCK);
    detector->addButtonEventListener(serialLoggerButtonCallback);
    detector->addButtonEventListener(sdcardLoggerButtonCallback);
    Serial.println("OK");

    // RTC - Real Time Clock
    Serial.print("Initializing RTC...");
    time = new JammaTime();
    Serial.println("OK");

    Serial.print("Initializing SD card...");
    
    sprintf(logFilename, "jamma_%s.txt", time->getJammaTime());
    sto = new SDStorage(SD_CS, SD_MOSI,SD_MISO, SD_CLK, logFilename);
    if(!sto->initSDCard()) {
        Serial.println("Failed. Card present ? Formatted as FAT16/32 ?");
    } else {
#ifdef DEBUG_STORAGE
        Serial.println("List of files on SDCard:");
        sto->getRootVolume()->ls(LS_R | LS_DATE | LS_SIZE);
        Serial.println();
#endif
        Serial.printf("OK - log file name is %s\n", logFilename);
    }

    // Creating writer object
    writer = new EventWriter(sto, time);

    Serial.println("Listening for inputs.");
    Serial.flush();
}

void loop() {
#ifdef DEBUG_RTC
    Serial.print(", time=");
    Serial.println(time->getJammaTime());
#endif

    detector->loadRegisters();
    detector->readRegisters();

#ifdef DEBUG_BUTTONS
    detector->printSerial();
#endif

// sizeof(unsigned int) = 2 bytes so 65535 is the maximum for delayMicroseconds - switching to delay otherwise
#if REFRESH_DELAY_US > 0 && REFRESH_DELAY_US < 65535
    delayMicroseconds(REFRESH_DELAY_US);
#elif REFRESH_DELAY_US > 0
    delay(REFRESH_DELAY_US/1000);
#endif
}

// Callback function
void serialLoggerButtonCallback(ButtonEvent* e) {
    Serial.print("Button ");
    Serial.print(buttonsName[e->getButton()]);
    Serial.print(" has been ");
    Serial.println(e->isPressed() ? "pressed" : "released");
    Serial.flush();
}

// Callback function
void sdcardLoggerButtonCallback(ButtonEvent* e) {
    Serial.println("SD Events not implemented.");
    writer->writeEvent(e);
}
