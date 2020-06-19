#include <SD.h>
#include <SPI.h>
#include "btns/buttonDetector.h"
#include "btns/buttons.h"
#include "storage/sdstorage.h"

// Special attention to pin numbers because Arduino library pinout macros can be
// confusing...
// As far as I know, PDx are ok whereas PBx are not ...

#define APP_NAME "NMA Jamma Streamer"
#ifndef APP_VERSION
#define APP_VERSION "master"
#endif

// Shift registers
#define PLOAD PD4   // PD4 = Arduino pin 4
#define ENABLE PD5  // PD5 = Arduino pin 5
#define DATA PD6    // PD6 = Arduino pin 6
#define CLOCK PD7   // PD7 = Arduino pin 7

// SD card
#define SD_CS 10    // PB2 = Arduino pin 10 (SS)
#define SD_MOSI 11  // PB3 = Arduino pin 11 (MOSI)
#define SD_MISO 12  // PB4 = Arduino pin 12 (MISO)
#define SD_CLK 13   // PB5 = Arduino pin 13 (SCK)

#ifndef REFRESH_DELAY_US
#define REFRESH_DELAY_US 100000
#endif

#ifndef SERIAL_SPEED
#define SERIAL SPEED 19600
#endif

void displayButtonsChange(uint32_t, uint32_t);

ButtonDetector* detector;
const ButtonsState* st;
const ButtonsState* prev_st;

SDStorage* sto;

void setup() {
    Serial.begin(SERIAL_SPEED);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only
    }

    Serial.println(APP_NAME);
    Serial.print("version: ");
    Serial.println(APP_VERSION);
    Serial.println();

    Serial.print("Initializing SD card...");
    sto = new SDStorage(SD_CS, SD_MOSI,SD_MISO, SD_CLK);
    if(!sto->initSDCard()) {
        Serial.println("Failed. Card present ? Formatted as FAT16/32 ?");
    } else {
        Serial.println("OK");
    }

    // Buttons detection
    Serial.print("Configuring buttons detection...");
    detector = new ButtonDetector(PLOAD, ENABLE, DATA, CLOCK);
    Serial.println("OK");

    Serial.println("Listening for inputs.");
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
    if (((st->states)^(prev_st->states)) != 0 ){
        displayButtonsChange(prev_st->states, st->states);
    }

#if REFRESH_DELAY_US > 0
    delayMicroseconds(REFRESH_DELAY_US);
#endif
}

void displayButtonsChange(uint32_t prev, uint32_t cur) {
// get only changes with a XOR between previous and current states
#define XOR (prev ^ cur)

    // Check all buttons
    for (uint8_t i = 0; i < NB_BUTTONS; i++) {
#ifndef EXTENDED_JAMMA
        // Ignoring those extended buttons
        if (i == BTN_1P_4 || i == BTN_1P_5 || i == BTN_2P_4 || i == BTN_2P_5) {
            continue;
        }
#endif
        if ((XOR & BTN_MASK(buttons[i])) > 0) {
            Serial.print("Button ");
            Serial.print(buttonsName[buttons[i]]);
            Serial.print(" has been ");
            BTN_IS_PRESSED(cur, buttons[i]) ? Serial.print("pressed\n")
                                            : Serial.print("released\n");
        }
    }
}
