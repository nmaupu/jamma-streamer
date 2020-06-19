#ifndef __USDCARD_HEADER__
#define __USDCARD_HEADER__

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

   public:
    SDStorage(uint8_t cs, uint8_t mosi, uint8_t miso, uint8_t clk);

    // Init sdcard, returns true if ok, false otherwise
    bool initSDCard();
    bool initVolume();
    Sd2Card* getCard();
    SdVolume* getVolume();
    SdFile* getRootVolume();
};

#endif  // __USDCARD_HEADER__
