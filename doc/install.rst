.. index::
    single: Installation

============
Installation
============

The source code is hosted on GitHub_. mipea uses meson_ for configuration and
ninja_ to build and install the library.

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

For a detailed guide to install meson_ see
`here <https://mesonbuild.com/Getting-meson.html>`_. These examples assume
that you are using Raspbian (although it should work on other distributions too
with some modifications)::

        $ apt-get install python3 python3-pip python3-setuptools python3-wheel ninja-build
        $ pip3 install meson

Configuration
-------------

Go into the mipea directory and run following commands::

        $ meson _build

Building
--------

To build the project run ninja from inside the :code:`_build` directory::

        $ cd _build
        $ ninja

Installing
----------

::

        $ ninja install

Linking
-------

I noticed that sometimes the library can be linked, but when running a program
an error message appears saying: :code:`File or directory not found`.
If you havethis problem just run :code:`ldconfig`

.. index::
    single: Troubleshooting

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
an error message appears saying: :code:`File or directory not found`.
If you have this problem just run :code:`ldconfig`

Wifi stops working when using the library
-----------------------------------------

In versions 2.1.0 and below the GPIO map and unmap functions cleared *all*
pullup / -downs on all pins. This could lead to the wifi not working until a
reboot. This issue should be fixed with version 2.1.1.

.. _GitHub: https://github.com/jasLogic/mipea
.. _meson: https://mesonbuild.com/
.. _ninja: https://ninja-build.org/
.. _releases: https://github.com/jasLogic/mipea/releases
