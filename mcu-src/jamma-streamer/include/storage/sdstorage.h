#ifndef __SDSTORAGE_HEADER__
#define __SDSTORAGE_HEADER__

#include <SPI.h>
#include <SdFat.h>

// uSDCard driver class using
// https://platformio.org/lib/show/161/SD

class SDStorage {
   private:
    uint8_t cs, miso, mosi, clk;
    SdFat sd;
    File logFile;
    const char* filename;

   public:
    SDStorage(uint8_t cs, uint8_t mosi, uint8_t miso, uint8_t clk, const char* filename);

    // Init sdcard, returns true if ok, false otherwise
    bool initSDCard();
    SdFat* getSD();
    const char* getFilename();
    File* getLogFile();
};

#endif  // __SDSTORAGE_HEADER__
