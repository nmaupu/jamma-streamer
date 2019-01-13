# jamma-streamer

Jamma PCB video recorder and more (hardware)

# Buttons detection

Buttons detection are done using shift registers (8 bits parallel in / serial out such as the 75HC165).
The code used is strongly inspired from the following tutorial:
https://playground.arduino.cc/Code/ShiftRegSN74HC165N

# uSDCARD writing

Source:
https://learn.adafruit.com/adafruit-micro-sd-breakout-board-card-tutorial?view=all

# How to program the ATMEGA328PB

We are using Jamma Streamer board ICSP header for this.
No need for a Arduino bootloader, we will be uploading sketch directly via ICSP header !

As I am using Atmega328PB (instead of P), Arduino IDE is not recognising at first, we need to install this first to have the board available in Arduino’s IDE later on:
https://github.com/nmaupu/ATmega328PB-Testing

---

Plug cables as follow (using Arduino duemilanove):

- All ICSP to Arduino ICSP except RST both sides
- RST Jamma Streamer (from icsp) to pin 10 of the arduino

1) Plug Arduino via USB to computer and upload ArduinoISP sketch onto it.
2) plug a 10uF capacitor between Arduino RESET (capacitor +) and GND (capacitor -)
3) select tools > boards > atmega328PB Crystal Clock
4) sketch > Upload using programmer

This will program the Jamma Streamer atmega328PB !

# Thanks

- https://github.com/Shinichi-Ohki/JAMMA_connector_for_eagle
- https://github.com/watterott/wattuino
