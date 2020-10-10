#include "rtc/jammaTime.h"

// initialization of g_rtc_milliseconds
volatile uint16_t g_rtc_milliseconds = 0;

// interrupt for milliseconds computation
ISR(PCINT1_vect) { // PCINT1 is used because we are on group C interrupts
    if (INT_PIN_GRP & _BV(SWQ_PIN)) {  // if pin goes HIGH
        if (g_rtc_milliseconds >= 999)
            g_rtc_milliseconds = 0;
        else
            ++g_rtc_milliseconds;
    }
}

JammaTime::JammaTime() {
    if (!rtc.begin()) {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        return;
    }

    if (rtc.lostPower()) {
        Serial.println("RTC lost power, setting time");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was
        // compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to
        // set January 21, 2014 at 3am you would call: rtc.adjust(DateTime(2014,
        // 1, 21, 3, 0, 0));

        // When time needs to be re-set on a previously configured device, the
        // following line sets the RTC to the date & time this sketch was
        // compiled rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); This line
        // sets the RTC with an explicit date & time, for example to set January
        // 21, 2014 at 3am you would call: rtc.adjust(DateTime(2014, 1, 21, 3,
        // 0, 0));
    }

    // Set Control Register so that SQW outputs a 1KHz square wave (millisecond
    // accuracy)
    // Datasheet https://datasheets.maximintegrated.com/en/ds/DS3231.pdfpage
    // Page 13
    write_i2c_register(DS3231_ADDRESS, DS3231_CONTROL, CONTROL_REG);
    /*
    Serial.println();
    Serial.print("Control register: ");
    Serial.println(read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL), BIN);
    */

    // interrupt configuration and attachment
    PCICR |= _BV(PCIE1);    // Setting interrupts on group "C"
    PCMSK1 |= _BV(SWQ_PIN); // Setting interrupt on pin PCINT11 / PC3
    sei();
}

const RTC_DS3231* JammaTime::getRtc() {
    return &rtc;
}

const char* JammaTime::getJammaTime() {
    // Format YYYYmmddHHMMSSsss
    DateTime t = rtc.now();

    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        sprintf(timeBuf, "%04d%02d%02d-%02d%02d%02d%03d", t.year(), t.month(),
                t.day(), t.hour(), t.minute(), t.second(), g_rtc_milliseconds);
    }

    return timeBuf;
}

uint8_t JammaTime::read_i2c_register(uint8_t addr, uint8_t reg) {
    Wire.beginTransmission(addr);
    Wire._I2C_WRITE((byte)reg);
    Wire.endTransmission();
    Wire.requestFrom(addr, (byte)1);
    return Wire._I2C_READ();
}

void JammaTime::write_i2c_register(uint8_t addr, uint8_t reg, uint8_t val) {
    Wire.beginTransmission(addr);
    Wire._I2C_WRITE((byte)reg);
    Wire._I2C_WRITE((byte)val);
    Wire.endTransmission();
}
