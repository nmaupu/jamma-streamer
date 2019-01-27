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

## Using arduino bootloader (for debugging and fast upload via IDE)

As ATmega328PB is used, I didn't find a way to make it work using IDE despite many project found on github such as those :
- https://github.com/Optiboot/optiboot
- https://github.com/MCUdude/MiniCore

To make it work using bootloader corresponding to a ordinary ATmega328P, use the following procedure:
- Use arduino as ISP method to upload the bootloader:
  - Plug all ICSP to Arduino ICSP except RST both sides
  - RST Jamma Streamer (from ICSP) to pin 10 of the Arduino
  - Upload Arduino ISP sketch to the arduino board to make it act as an ISP programmer
  - plug a 10uF capacitor between Arduino RESET (capacitor +) and GND (capacitor -)
  - from now on keep your board configuration unchanged (duemilanove, 328P)

If you burn the bootloader now, Arduino IDE will complain about the atmega signature...
We are going to make the IDE (avrdude in fact) think that our atmega is a 328P.
To do that, edit the following file `/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf` and find the line corresponding to the atmega328p:
```
part parent "m328"
    id>->--->---= "m328p";
    desc>--->---= "ATmega328P";
    signature>-->---= 0x1e 0x95 0x0F;

    ocdrev              = 1;
;
```

Change the signature to match the 328PB chip like so:
```
part parent "m328"
    id>->--->---= "m328p";
    desc>--->---= "ATmega328P";
    signature>-->---= 0x1e 0x95 0x16;

    ocdrev              = 1;
;
```

Once done, click tools > burn bootloader. This should work as expected !

Now, revert the changes from the `avrdude.conf` file because your chip will act as a 328P (like the duemlianove).

To upload a sketch, simply use the duemilanove configuration and click upload !

## Without using arduino bootloader for runtime
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
