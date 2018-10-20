# epaRPi

## easy peripheral access for Raspberry Pi

This library grants easy and fast access to peripherals. Only the GPIO-peripheral is implemented at the moment, with PWM being work-in-progress.

It was only tested on the Raspberry Pi Zero, but should work on all other Raspberry Pis which use the bcm2835.

TODO:
1. Fix PWM
    * PWM is for some reason only working, when a program which uses the bcm2835-library was run beforehand. After that it works without any problems.
2. SPI
3. I2C
4. Audio

### Usage

To use a peripheral, for example GPIO, you need to include the corresponding header into your program.
`#include "gpio.h"``

After that it is crucial to map the peripheral like so `gpio_map()`. When your program is finished you should unmap the peripheral again `gpio_unmap()``
Now you can use the registers or the provided functions.
