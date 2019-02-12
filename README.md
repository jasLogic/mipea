# epaRPi

## easy peripheral access for Raspberry Pi

This library grants easy and fast access to peripherals. The GPIO, PWM and SPI are implemented at the moment.

It was only tested on the Raspberry Pi Zero, but should work on all other Raspberry Pis which use the bcm2835.

**Peripherals Implemented at the moment:**
* GPIO
* PWM
    * Using the clock manager
* SPI

**TODO:**
1. I2C
2. Audio

### Usage

To use a peripheral, for example GPIO, you need to include the corresponding header into your program.
`#include "gpio.h"`

After that it is crucial to map the peripheral like so `gpio_map()`. When your program is finished you should unmap the peripheral again `gpio_unmap()`
Now you can use the registers or the provided functions.

#### Compile and link
`gcc -Wall -o [outputfile] [your program].c gpio.c [...] peripherals.c`

## Sources and useful documentation

* bcm2835_peripherals.h and bcm2835_peripherals.c are highly inspired by [Pieter Jan](http://pieter-jan.com/)'s ["Low Level Programming of the Raspberry Pi in C"](http://pieter-jan.com/node/15).
* [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf)
* There are many errors in the [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf) so the [BCM2835 datasheet errata](https://elinux.org/BCM2835_datasheet_errata) by elinux.org is very useful and important.
* Because the [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf) for some reason does not feature the PWM and PCM clocks, there is this very useful datasheet snippet: [BCM2835 Audio clocks](https://www.scribd.com/doc/127599939/BCM2835-Audio-clocks)
