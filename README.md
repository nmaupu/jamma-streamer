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

## Fuses

Fuses can be calculated using: https://www.engbedded.com/fusecalc/
More info here: http://www.martyncurrey.com/arduino-atmega-328p-fuse-settings/

## Using arduino bootloader (for debugging and fast upload via IDE)

As ATmega328PB is used, I didn't find a way to make it work using IDE despite many projects found on github such as (more details below):
- https://github.com/Optiboot/optiboot (good schematic is available here but can't find correct settings in Arduino for the upload button to work as expected: http://www.vwlowen.co.uk/arduino/bootloader/page2.htm)
- https://github.com/MCUdude/MiniCore (not a bootloader per se, that's why)

---

To make it work using bootloader corresponding to an ordinary ATmega328P, use the following procedure.

Use *arduino as ISP* method to upload the bootloader:
  - First add the boards from [this arduino board file](arduino/boards.txt) to your Arduino `boards.txt` file (typically in `~/Library/Arduino15/packages/arduino/hardware/avr/1.8.2/boards.txt`)
  - Restart Arduino IDE

Then:
  - Configure your IDE to use the ISP Arduino
  - Upload Arduino ISP sketch to the arduino board to make it act as an ISP programmer (available as example sketch from the Arduino IDE)
  - Plug all ICSP to Arduino ICSP except RST both sides
  - RST Jamma Streamer (from ICSP) to pin 10 of the Arduino
  - plug a 10uF capacitor between Arduino RESET (capacitor +) and GND (capacitor -)

Your arduino is ready for ISP. Now you can configure to burn the NMA Jamma Streamer bootloader:
  - from `Tools > Board`, select the newly added *NMA Jamma Streamer*
  - select the following processor: *ATMega328PB*
  - `Tools > Port`: select the arduino device
  - `Tools > Burn Bootloader`

This should work as expected.

From now on, you will be able to upload sketches using the following configuration:
  - Board: *NMA Jamma Streamer*
  - Processor: *ATmega328P*
  - Port: *Port detected by your system*

---

Here are the avrdude commands for the manual configuration:
```
avrdude -C $HOME/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -v -p atmega328pb -c stk500v1 -P /dev/cu.usbmodem141101 -b19200 -e -Ulock:w:0x3F:m -Uefuse:w:0xF5:m -Uhfuse:w:0xDA:m -Ulfuse:w:0xFF:m

avrdude -C $HOME/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -v -p atmega328pb -c stk500v1 -P /dev/cu.usbmodem141101 -b19200 -Uflash:w:$HOME/Library/Arduino15/packages/arduino/hardware/avr/1.8.2/bootloaders/atmega/ATmegaBOOT_168_atmega328.hex:i -Ulock:w:0x0F:m 
```

## Without using arduino bootloader for runtime

We are using Jamma Streamer board ICSP header for this.
No need for a Arduino bootloader, we will be uploading sketch directly via ICSP header !

As I am using Atmega328PB (instead of P), Arduino IDE is not recognising at first, we need to install this first to have the board available in Arduino’s IDE later on:
https://github.com/nmaupu/ATmega328PB-Testing

---

Plug cables as follow (using Arduino Duemilanove or Mega):

- All ICSP to Arduino ICSP except RST both sides
- RST Jamma Streamer (from icsp) to pin 10 of the arduino
- Plug Arduino via USB to computer and upload ArduinoISP sketch onto it.
- plug a 10uF capacitor between Arduino RESET (capacitor +) and GND (capacitor -)
- select tools > boards > atmega328PB Crystal Clock
- `sketch > Upload using programmer`

This will program the NMA Jamma Streamer atmega328PB !

## Burn / read fuses (use the crystal oscillator instead of internal one)

Notes when using a crystal oscillator:
  - After burning the bootloader, first upload is working.
  - Further uploads are not, even using the "reset trick" (push reset before pressing upload and releasing reset).
  - using internal oscillator works all the time with the "reset trick".

Use an external Arduino board to act as an ISP programmer like before:

- All ICSP to Arduino ICSP except RST both sides
- RST Jamma Streamer (from icsp) to pin 10 of the arduino
- Plug Arduino via USB to computer and upload ArduinoISP sketch onto it.
- plug a 10uF capacitor between Arduino RESET (capacitor +) and GND (capacitor -)

Here are the avrdude commands needed:

```
# Default fuses (internal oscillator)
avrdude -C $HOME/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -v -patmega328pb -cstk500v1 -P/dev/cu.usbserial-A700dZIw -b19200 -e -Ulock:w:0x3F:m -Uefuse:w:0xFD:m -Uhfuse:w:0xDA:m -Ulfuse:w:0xFF:m

# Configured for a crystal oscillator (the one soldered on the board with two capacitors)
avrdude -C $HOME/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -v -patmega328pb -cstk500v1 -P/dev/cu.usbserial-A700dZIw -b19200 -e -Ulock:w:0x3F:m -Uefuse:w:0xFD:m -Uhfuse:w:0xD9:m -Ulfuse:w:0xFF:m
```

To read the fuses, simply execute:
```
avrdude -C $HOME/Library/Arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf -v -patmega328pb -cstk500v    1 -P/dev/cu.usbserial-A700dZIw -b19200 -U hfuse:r:-:h -U efuse:r:-:h -U lfuse:r:-:h
```

## Burn the 328PB Optiboot bootloader manually

Beware: Cannot find a configuration to upload via FTDI after that :/

With arduino as ISP:
```
avrdude -C $HOME/Library/Arduino15/packages/m328pb/hardware/avr/1.1.4/tools/avrdude.conf -v -patmega328pb -cstk500v1 -P /dev/cu.usbmodem141101 -b19200 -e -Ulock:w:0xFF:m -Uefuse:w:0xFD:m -Uhfuse:w:0xD6:m -Ulfuse:w:0xFF:m
avrdude -C $HOME/Library/Arduino15/packages/m328pb/hardware/avr/1.1.4/tools/avrdude.conf -v -patmega328pb -cstk500v1 -P /dev/cu.usbmodem141101 -b19200 -Uflash:w:$HOME/Library/Arduino15/packages/m328pb/hardware/avr/1.1.4/bootloaders/optiboot_m328pb.hex:i -Ulock:w:0xCF:m
```

# Thanks

- https://github.com/Shinichi-Ohki/JAMMA_connector_for_eagle
- https://github.com/watterott/wattuino
