.. index::
    single: Installation

============
Installation
============

The source code is hosted on GitHub_. mipea uses meson_ and
ninja_ or cmake_ to build the library (see `Why two build systems?`_).
But I would suggest to use meson_ because it automatically detects
the peripheral base and is imho altogether the better build system.

Downloading
===========

You can either download a source distribution on GitHub_ under the releases_
tab or clone the repository.

Source Distribution
-------------------

Download the source distribution from the releases_ tab and extract the files::

        $ wget https://github.com/jasLogic/mipea/releases/download/vx.x.x/mipea_x.x.x.tar.gz
        or
        $ curl -O https://github.com/jasLogic/mipea/releases/download/vx.x.x/mipea_x.x.x.tar.gz

        $ tar -xzf mipea_x.x.x.tar.gz

Cloning the Repository
----------------------

::

        $ git clone https://github.com/jasLogic/mipea.git

Install the Build System
------------------------

For a detailed guide on how to install meson_ see
`here <https://mesonbuild.com/Getting-meson.html>`_.
For a detailed guide on how to install cmake_ see
`here <https://cmake.org/install/>`_.
These examples assume that you are using Raspbian
(although it should work on other distributions too with some modifications)::

        $ apt-get install python3 python3-pip python3-setuptools python3-wheel ninja-build
        $ pip3 install meson

        or

        $ apt-get install cmake

Configuration
-------------

Go into the mipea directory and run following commands::

        $ meson _build
        or
        $ cmake . -B _build

Building
--------

To build the project run ninja from inside the :code:`_build` directory::

        $ cd _build

        $ ninja
        or
        $ make

Installing
----------

::

        $ ninja install
        or
        $ make install

Linking
-------

I noticed that sometimes the library can be linked, but when running a program
an error message appears saying::

         error while loading shared libraries: libmipea.so: cannot open shared object file: No such file or directory

If you havethis problem simply run :code:`ldconfig`

.. index::
    single: Troubleshooting

Why two build systems?
----------------------

I like meson_ more than cmake_ but I hate the fact that you need to install
Python plus meson_ and than also install ninja_. But the better syntax
is just so much better that it is worth it.

I decided to also include cmake_ because most people also have it installed
and you don't need to install three things. Although I would **highly**
suggest using meson_ because it can automatically detect the peripheral base
and it runs some more checks. Also I didn't spend so much time on the cmake_
script and I propably won't maintain it very well.

Troubleshooting
===============

Configure script can not find /proc/cpuinfo
-------------------------------------------

If the :code:`configure` script prints this warning::

    WARNING: could not gather info from /proc/cpuinfo with bcm_info.sh

than the script was unable to get the board info from the :code:`bcm_host`
library it tries to read them from the :code:`/proc/cpuinfo` file.
When this is the case you need to specify these information manually.

This error can be fixed by editing the :code:`mipeaconfig.h`.
You need to set :code:`MIPEA_RASPBERRYPI_MODEL` and
:code:`MIPEA_BCM_HOST_PROCESSOR` to the right values. These values can
be found `here <https://github.com/raspberrypi/firmware/blob/master/opt/vc/include/bcm_host.h>`_
and `here <https://www.raspberrypi.org/documentation/hardware/raspberrypi/revision-codes/README.md>`_.

After that the important port of :code:`mipeaconfig.h` should look like this::

        // (NEEDED) raspberry pi model number
        #define MIPEA_RASPBERRYPI_MODEL 0x11
        // (NEEDED) processor number
        #define MIPEA_BCM_HOST_PROCESSOR 0x3

When running a program, the shared library file is not found
------------------------------------------------------------

I noticed that sometimes the library can be linked, but when running a program
an error message appears saying::

         error while loading shared libraries: libmipea.so: cannot open shared object file: No such file or directory

If you havethis problem simply run :code:`ldconfig`

Wifi stops working when using the library
-----------------------------------------

In versions 2.1.0 and below the GPIO map and unmap functions cleared *all*
pullup / -downs on all pins. This could lead to the wifi not working until a
reboot. This issue should be fixed with version 2.1.1.

.. _GitHub: https://github.com/jasLogic/mipea
.. _meson: https://mesonbuild.com/
.. _ninja: https://ninja-build.org/
.. _cmake: https://cmake.org/
.. _releases: https://github.com/jasLogic/mipea/releases
