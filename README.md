# epaRPi

## easy peripheral access for Raspberry Pi

This library grants easy and fast access to peripherals. Only the GPIO-peripheral is implemented at the moment, with PWM being work-in-progress.

It was only tested on the Raspberry Pi Zero, but should work on all other Raspberry Pis which use the bcm2835.

Peripherals Implemented at the moment:
* GPIO
* PWM
    * Using the clock manager

TODO:
1. SPI
2. I2C
3. Audio

### Usage

To use a peripheral, for example GPIO, you need to include the corresponding header into your program.
`#include "gpio.h"`

After that it is crucial to map the peripheral like so `gpio_map()`. When your program is finished you should unmap the peripheral again `gpio_unmap()`
Now you can use the registers or the provided functions.
