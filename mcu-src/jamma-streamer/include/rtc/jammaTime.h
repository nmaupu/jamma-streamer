#ifndef __TIME_HEADER__
#define __TIME_HEADER__

#include "globals.h"
#include <RTClib.h>
#include <Wire.h>
#include <util/atomic.h>

#ifdef __AVR__
#include <avr/pgmspace.h>
#endif
#if (ARDUINO >= 100)
#include <Arduino.h>  // capital A so it is error prone on case-sensitive filesystems
// Macro to deal with the difference in I2C write functions from old and new
// Arduino versions.
#define _I2C_WRITE write
#define _I2C_READ read
#else
#include <WProgram.h>
#define _I2C_WRITE send
#define _I2C_READ receive
#endif

// Used by RTC with interrupt
extern volatile uint16_t g_rtc_milliseconds;

class JammaTime {
    private:
     RTC_DS3231 rtc;
     char timeBuf[20];
     uint8_t read_i2c_register(uint8_t addr, uint8_t reg);
     void write_i2c_register(uint8_t addr, uint8_t reg, uint8_t val);

    public:
     JammaTime();
     const RTC_DS3231* getRtc();
     // Get the time as a string (format: YYYYmmddHHMMSSsss)
     const char* getJammaTime();
};
#endif  // __TIME_HEADER__
