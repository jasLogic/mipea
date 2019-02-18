# mipea

## minimalistic peripheral access for the Raspberry Pi

This library grants easy and fast access to peripherals. The GPIO, PWM and SPI are implemented at the moment.

Contributions are welcome, please fork and open a pull request.

If you have successfully used mipea on a Raspberry Pi which is not tested yet, please inform me and I can add it to the list.

**Peripherals Implemented at the moment:**
* GPIO
* PWM
    * Using the clock manager
* SPI
* Timer

**TODO:**
1. I2C (in progress)
2. DMA (in progress)
3. PCM

| Raspberry Pi  | Supported | Tested |
|---------------|:---------:|:------:|
| 1 Model A     | ✔︎         | ✘      |
| 1 Model A+    | ✔︎         | ✘      |
| 3 Model A+    | ✔︎         | ✘      |
| 1 Model B     | ✔︎         | ✘      |
| 1 Model B+    | ✔︎         | ✘      |
| 2 Model B     | ✔︎         | ✘      |
| 2 Model Bv1.2 | ✔︎         | ✘      |
| 3 Model B     | ✔︎         | ✔︎      |
| 3 Model B+    | ✔︎         | ✘      |
| Zero v1.2     | ✔︎         | ✘      |
| Zero          | ✔︎         | ✔︎      |
| Zero W        | ✔︎         | ✘      |

### Installation

```
$ make
$ sudo make install
```

### Usage

To use a peripheral, for example GPIO, you need to include the corresponding header into your program.
`#include "gpio.h"`

After that it is crucial to map the peripheral like so `gpio_map()`. When your program is finished you should unmap the peripheral again `gpio_unmap()`
Now you can use the registers or the provided functions.

#### Compile and link
`gcc -Wall -o [outputfile] [your program].c -lmipea`

## Sources and useful documentation

* bcm2835_peripherals.h and bcm2835_peripherals.c are highly inspired by [Pieter Jan](http://pieter-jan.com/)'s ["Low Level Programming of the Raspberry Pi in C"](http://pieter-jan.com/node/15).
* [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf)
* There are many errors in the [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf) so the [BCM2835 datasheet errata](https://elinux.org/BCM2835_datasheet_errata) by elinux.org is very useful and important.
* Because the [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf) for some reason does not feature the PWM and PCM clocks, there is this very useful datasheet snippet: [BCM2835 Audio clocks](https://www.scribd.com/doc/127599939/BCM2835-Audio-clocks)
