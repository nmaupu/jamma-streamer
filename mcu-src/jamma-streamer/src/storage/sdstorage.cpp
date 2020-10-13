#include "storage/sdstorage.h"

SDStorage::SDStorage(uint8_t cs = 10, uint8_t mosi = 11, uint8_t miso = 12,
                     uint8_t clk = 13, const char* filename = "test.log") {
    this->cs = cs;
    this->miso = miso;
    this->mosi = mosi;
    this->clk = clk;
    this->filename = filename;
}

bool SDStorage::initSDCard() {
    if(!sd.begin(cs, SPI_HALF_SPEED)) {
        sd.initErrorHalt();
        return false;
    }

    logFile = sd.open(filename, FILE_WRITE);
    return true;
}

SdFat* SDStorage::getSD() { return &sd; }
const char* SDStorage::getFilename() { return filename; }
File* SDStorage::getLogFile() { return &logFile; }
