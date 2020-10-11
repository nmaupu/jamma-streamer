#ifndef __SDSTORAGE_HEADER__
#define __SDSTORAGE_HEADER__

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

// uSDCard driver class using
// https://platformio.org/lib/show/161/SD

class SDStorage {
   private:
    uint8_t cs, miso, mosi, clk;
    Sd2Card card;
    SdVolume volume;
    SdFile root;
    SdFile logFile;
    const char* filename;

   public:
    SDStorage(uint8_t cs, uint8_t mosi, uint8_t miso, uint8_t clk, const char* filename);

    // Init sdcard, returns true if ok, false otherwise
    bool initSDCard();
    Sd2Card* getCard();
    SdVolume* getVolume();
    SdFile* getRootVolume();
    SdFile* getLogFile();
    SdFile* openLogFile();
};

#endif  // __SDSTORAGE_HEADER__
