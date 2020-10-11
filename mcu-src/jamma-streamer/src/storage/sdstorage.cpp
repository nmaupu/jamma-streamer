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
    if(!card.init(SPI_HALF_SPEED, cs, mosi, miso, clk))
        return false;

#ifdef DEBUG_STORAGE
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
#endif

    // finally, init volume
    if(!volume.init(card))
        return false;

#ifdef DEBUG_STORAGE
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
    Serial.print("Volume size (Mb):  ");
    volumesize /= 1024;
    Serial.println(volumesize);
#endif

    return true;
}

Sd2Card* SDStorage::getCard() { return &card; }
    
SdVolume* SDStorage::getVolume() { return &volume; }

SdFile* SDStorage::getRootVolume() {
    root.openRoot(getVolume());
    return &root;
}

SdFile* SDStorage::getLogFile() { return &logFile; }

SdFile* SDStorage::openLogFile() {
    logFile.open(getRootVolume(), filename, O_CREAT | O_RDWR | O_APPEND);
    return &logFile;
}
