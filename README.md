[![Documentation Status](https://readthedocs.org/projects/mipea/badge/?version=latest)](https://mipea.readthedocs.io/en/latest/?badge=latest)
[![GitHub release](https://img.shields.io/github/release/jasLogic/mipea.svg)](https://github.com/jasLogic/mipea/releases)
[![GitHub](https://img.shields.io/github/license/jasLogic/mipea.svg?color=informational)](LICENSE.md)

# mipea

## minimalistic peripheral access for the Raspberry Pi

This library grants easy and fast access to peripherals.

Contributions are welcome, please fork and open a pull request.

If you have successfully used mipea on a Raspberry Pi which is not tested yet,
please inform me and I can add it to the list.

### Goal of this library
The library is very useful for **high-speed and lighweight applications**,
**efficiency** and **total control** on the **hardware level**.


I did not create this library for simplicity. It is useful for people
who still read the datasheet and know what the registers do but don't
want to do the "ugly" work on the low level.

Also, most functions are only a bare "skeleton" with very minimalistic design
where **other programs need to implement higher level functionality**.

If you searched for a efficient and highly customizable library which
**only lays the foundation for other programs** then you are right.

### Supported Pis
| Raspberry Pi  | Supported | Tested |
|---------------|:---------:|:------:|
| 1 Model A     | ✔︎         |        |
| 1 Model A+    | ✔︎         |        |
| 3 Model A+    | ✔︎         |        |
| 1 Model B     | ✔︎         |        |
| 1 Model B+    | ✔︎         |        |
| 2 Model B     | ✔︎         |        |
| 2 Model Bv1.2 | ✔︎         |        |
| 3 Model B     | ✔︎         | ✔︎      |
| 3 Model B+    | ✔︎         | ✔︎      |
| Zero v1.2     | ✔︎         |        |
| Zero          | ✔︎         | ✔︎      |
| Zero W        | ✔︎         |        |
| 4 Model B    |experimental| ✔︎      |

### Installation

mipea uses [meson](https://mesonbuild.com/) and
[ninja](https://ninja-build.org/) or [cmake](https://cmake.org/) to build
the library (see "Why two build systems" in the docs).
But I would suggest to use meson because it automatically detects
the peripheral base and is imho altogether the better build system.
For installation guide using cmake see the docs.

#### Downloading
You can either download a source distribution or clone the repository.

##### Source Distribution
Download the source distribution from the
[releases tab](https://github.com/jasLogic/mipea/releases) and extract the files
```
$ wget https://github.com/jasLogic/mipea/releases/download/vx.x.x/mipea_x.x.x.tar.gz
or
$ curl -O https://github.com/jasLogic/mipea/releases/download/vx.x.x/mipea_x.x.x.tar.gz

$ tar -xzf mipea_x.x.x.tar.gz
```

#### Cloning the Repository
```
$ git clone https://github.com/jasLogic/mipea.git
```

#### Install the Build System
For a detailed guide to install meson see
[here](https://mesonbuild.com/Getting-meson.html). These examples assume
that you are using Raspbian (although it should work on other distributions too
with some modifications)
```
$ apt-get install python3 python3-pip python3-setuptools python3-wheel ninja-build
$ pip3 install meson
```

#### Configuration
Go into the mipea directory and run following commands
```
$ meson _build
```

#### Building
To build the project run ninja from inside the `_build` directory
```
$ cd _build
$ ninja
```

#### Installing
```
$ ninja install
```

#### Linking
I noticed that sometimes the library can be linked, but when running a program
an error message appears saying:
```
error while loading shared libraries: libmipea.so: cannot open shared object file: No such file or directory
```
If you have this problem simply run `ldconfig`.

### Documentation

Documentation is uploaded to [ReadTheDocs](https://mipea.readthedocs.io).
You can also build the documentation yourself using `sphinx`.

### Usage

To use a peripheral, for example GPIO, you need to include the corresponding header into your program.
`#include <mipea/gpio.h>`

After that it is crucial to map the peripheral like so `gpio_map()`. When your program is finished you should unmap the peripheral again `gpio_unmap()`
Now you can use the registers or the provided functions.

#### Compile and link
`gcc -Wall -o [outputfile] [your program].c -lmipea`

### Servos
Although you can drive one or two servos using this library and PWM it is now
possible to drive more. You could of course use `usleep()` but this is
not recommended, as it is not very accurate. Instead you could use my
[mipea_servo library](https://github.com/jasLogic/mipea_servo)
which makes use of DMA and PWM to archieve a **very** accurate pulse
without CPU usage.

## Sources and useful Documentation

* bcm2835_peripherals.h and bcm2835_peripherals.c are highly inspired by [Pieter Jan](http://pieter-jan.com/)'s ["Low Level Programming of the Raspberry Pi in C"](http://pieter-jan.com/node/15).
* [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf)
* There are many errors in the [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf) so the [BCM2835 datasheet errata](https://elinux.org/BCM2835_datasheet_errata) by elinux.org is very useful and important.
* Because the [BCM2835 ARM Peripherals Datasheet](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf) for some reason does not feature the PWM and PCM clocks, there is this very useful datasheet snippet: [BCM2835 Audio clocks](https://www.scribd.com/doc/127599939/BCM2835-Audio-clocks)
