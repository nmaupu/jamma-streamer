#include <SD.h>
#include <SPI.h>
#include "btns/buttonDetector.h"
#include "btns/buttons.h"

// Shift registers
#define PLOAD PD4
#define ENABLE PD5
#define DATA PD6
#define CLOCK PD7

// SD card
#define SD_CS PB2
//#define SD_MOSI PB3
//#define SD_MISO PB4
//#define SD_CLK PB5

#ifndef REFRESH_DELAY
#define REFRESH_DELAY 1000
#endif

#ifndef SERIAL_SPEED
#define SERIAL SPEED 19600
#endif

void displayButtonsChange(uint32_t, uint32_t);

ButtonDetector *detector;
const ButtonsState *st;
const ButtonsState *prev_st;

Sd2Card card;
SdVolume volume;
SdFile root;

void setup() {
    Serial.begin(SERIAL_SPEED);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Init...");

    Serial.print("PB2=");
    Serial.println(PB2);
    Serial.print("PB3=");
    Serial.println(PB3);
    Serial.print("PB4=");
    Serial.println(PB4);
    Serial.print("PB5=");
    Serial.println(PB5);
    Serial.println();

    Serial.print("PD4=");
    Serial.println(PD4);
    Serial.print("PD5=");
    Serial.println(PD5);
    Serial.print("PD6=");
    Serial.println(PD6);
    Serial.print("PD7=");
    Serial.println(PD7);
    Serial.println();

    detector = new ButtonDetector(PLOAD, ENABLE, DATA, CLOCK);

    Serial.print("Initializing SD card...");
    if(!card.init(SPI_HALF_SPEED, SD_CS)) {
        Serial.println("initialization failed. Things to check:");
        Serial.println("* is a card inserted?");
        Serial.println("* is your wiring correct?");
        Serial.println(
            "* did you change the chipSelect pin to match your shield or "
            "module?");
        Serial.print("Err code: ");
        Serial.println(card.errorCode());
        Serial.print("Err data: ");
        Serial.println(card.errorData());
        while (1) delay(1000);
    } else {
        Serial.println("Wiring is correct and a card is present.");
    }

    // print the type of card
    Serial.println();
    Serial.print("Card type:         ");
    switch (card.type()) {
        case SD_CARD_TYPE_SD1:
            Serial.println("SD1");
            break;
        case SD_CARD_TYPE_SD2:
            Serial.println("SD2");
            break;
        case SD_CARD_TYPE_SDHC:
            Serial.println("SDHC");
            break;
        default:
            Serial.println("Unknown");
    }

    Serial.println("Done.");
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

#if REFRESH_DELAY > 0
    delay(REFRESH_DELAY);
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
