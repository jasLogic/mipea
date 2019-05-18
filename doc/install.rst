.. index::
    single: Installation

************
Installation
************

The source code is hosted on GitHub_. mipea uses autotools (autoconf,
automake, libtool) to build and install the library. So obtaining the library
is very easy::

    $ git clone https://github.com/jasLogic/mipea.git
    $ cd mipea
    $ ./configure
    $ make
    $ sudo make install

.. index::
    single: Troubleshooting

Troubleshooting
===============

If the :code:`configure` script prints this warning::

    configure: WARNING: cannot find file /proc/cpuinfo

than the script was unable to find the :code:`cpuinfo` file which is needed
to determine the SoC (BCM2835 or BCM2836/7) and the revision. Pis with a
revision number where the last four digits are less than :code:`0004`
use I2C bus 0 instead of 1, like the new ones.

This error can be fixed by editing the :code:`config.h` file ensuring that it
contains these lines (depending on your Pi)::

    #define BCM2835         1
    #define BCM2836_7       1
    #define USE_I2C_BUS_0   1


.. _GitHub: https://github.com/jasLogic/mipea
