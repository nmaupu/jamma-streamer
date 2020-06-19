#include <SD.h>
#include <SPI.h>
#include "btns/buttonDetector.h"
#include "btns/buttons.h"

// Special attention to pin numbers because Arduino library pinout macros can be
// confusing...
// As far as I know, PDx are ok whereas PBx are not ...

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

    Serial.print("Initializing SD card...");
    if(!card.init(SPI_HALF_SPEED, SD_CS, SD_MOSI, SD_MISO, SD_CLK)) {
        Serial.println("Failed: is a card inserted ?");
    } else {
        Serial.println("OK");
    }

    // print the type of card
    Serial.println();
    Serial.print("Card type: ");
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

    if (!volume.init(card)) {
        Serial.println("Could not find FAT16/FAT32 partition.");
    }

    Serial.print("Clusters:          ");
    Serial.println(volume.clusterCount());
    Serial.print("Blocks x Cluster:  ");
    Serial.println(volume.blocksPerCluster());

    Serial.print("Total Blocks:      ");
    Serial.println(volume.blocksPerCluster() * volume.clusterCount());
    Serial.println();

    // print the type and size of the first FAT-type volume
    uint32_t volumesize;
    Serial.print("Volume type is:    FAT");
    Serial.println(volume.fatType(), DEC);

    volumesize =
        volume.blocksPerCluster();        // clusters are collections of blocks
    volumesize *= volume.clusterCount();  // we'll have a lot of clusters
    volumesize /= 2;  // SD card blocks are always 512 bytes (2 blocks are 1KB)
    Serial.print("Volume size (Kb):  ");
    Serial.println(volumesize);
    Serial.print("Volume size (Mb):  ");
    volumesize /= 1024;
    Serial.println(volumesize);
    Serial.print("Volume size (Gb):  ");
    Serial.println((float)volumesize / 1024.0);

    Serial.println(
        "\nFiles found on the card (name, date and size in bytes): ");
    root.openRoot(volume);

    // list all files in the card with date and size
    root.ls(LS_R | LS_DATE | LS_SIZE);

    // Buttons detection
    detector = new ButtonDetector(PLOAD, ENABLE, DATA, CLOCK);

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
