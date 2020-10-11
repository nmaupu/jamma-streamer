#ifndef __GLOBALS_HEADER__
#define __GLOBALS_HEADER__

#include <Arduino.h>

#define APP_NAME "NMA Jamma Streamer"
#ifndef APP_VERSION
#define APP_VERSION "master"
#endif

// Special attention to pin numbers because Arduino library pinout macros can be
// confusing...
// As far as I know, PDx are ok whereas PBx are not really what I thought...

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

// Delay in main loop if need be
#ifndef REFRESH_DELAY_US
#define REFRESH_DELAY_US 100000
#endif

// Serial communication speed
#ifndef SERIAL_SPEED
#define SERIAL SPEED 19600
#endif

// Control register to generate a square wave (1KHz) on RTC's SQW pin to count milliseconds via interrupt.
// See page 13 - https://www.mouser.com/datasheet/2/256/DS3231-1513891.pdf
// RS2 RS1 = 1 0 for ~1kHz square wave
#define RTC_CONTROL_REG 0b10001000

// RTC / ATmega interrupt pins configuration
#define SWQ_PIN PCINT11
#define INT_PIN_GRP PINC

#endif  // __GLOBALS_HEADER__
