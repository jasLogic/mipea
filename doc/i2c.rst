.. index::
    single: I2C

***
I2C
***

Macros
======

.. macro:: I2C_OFFSET_0

    ::

        0x205000

.. macro:: I2C_OFFSET_1

    ::

        0x804000

    The BCM2835/6/7 has three BSC (I2C) controllers, from which only one is
    connected to the I2C pins. The older Pis (where the last four digits
    of the revision number are less than :code:`0004`) have BSC0 connected to
    the pins, all the other BSC1. The configure script tries to read the
    :code:`/proc/cpuinfo` file, which includes the revision number, and than
    defines :code:`USE_I2C_BUS_0` accordingly. See :doc:`install`

.. macro:: I2C_SIZE

    ::

        0x18

    This macro holds the size of the I2C registers which needs to be mapped.

:macro:`I2C_FIFO_SIZE`
:macro:`I2C_C_I2CEN`
:macro:`I2C_C_ST`
:macro:`I2C_C_CLEAR`
:macro:`I2C_C_READ`
:macro:`I2C_S_RXS`
:macro:`I2C_S_TXD`
:macro:`I2C_S_DONE`

Registers
=========

.. var:: volatile uint32_t *i2c_base_ptr

    This pointer points, when mapped, to the base of the I2C registers.

.. type:: struct i2c_register_map

    This struct maps the registers of the BSC controller.
    The names of the struct members correspond to the registers
    from the Datasheet_::

        struct i2c_register_map {
            uint32_t C;
            uint32_t S;
            uint32_t DLEN;
            uint32_t A;
            uint32_t FIFO;
            uint32_t DIV;
            uint32_t DEL;
            uint32_t CLKT;
        };

.. macro:: I2C

    ::

        #define I2C ((volatile struct i2c_register_map *)i2c_base_ptr)

    By using this macro, the registers of the I2C can be accessed like this
    :code:`I2C->FIFO`.

Functions
=========

.. function:: uint32_t * i2c_map(void)

    This function maps the I2C registers. It calls :func:`peripheral_map` with
    the values :code:`I2C_OFFSET` and :macro:`I2C_SIZE`. :code:`I2C_OFFSET` is
    defined in :code:`i2c.c`.

.. function:: void i2c_unmap(void)

    This function unmaps the I2C registers.

.. function:: void i2c_set_address(uint8_t addr)

    This function sets the address of the I2C device to communicate with.
    The address is a seven bit value.

.. function:: void i2c_set_clkdiv(uint16_t divisor)

    This function sets the clock divisor of the BSC controller.

    .. note:: The clock source is the core clock with a frequency, \
        according to the Datasheet_, of :code:`150 MHz` and \
        according to `this file`_ and other sources of :code:`250 MHz`. \
        When I tested the clock speed of I2C and SPI with a logic analyzer, \
        it seems that :code:`250 MHz` **is correct** \
        (at least for the Raspberry Pi Zero I use).

.. function:: void i2c_set_clkstr(uint16_t clkstr)

    This function  sets the clock stretch timeout (or delay). This means that
    the master will wait :code:`clkstr` cycles after the rising clock edge
    for the slave to respond. After this the timeout flag is set.
    This can often be left at reset value :code:`0x40`.

.. function:: void i2c_start(void)

    Starts the BSC controller and clears the flag register.

.. function:: void i2c_stop(void)

    Disables the BSC controller.

.. function:: void i2c_write_byte(uint8_t byte)

    Write a :code:`byte` of data.

.. function:: uint8_t i2c_read_byte(void)

    This function receives a :code:`byte` of data and returns it.

.. function:: void i2c_write_data(const uint8_t *data, uint16_t length)

    This function writes :code:`length` bytes of data pointed to by :code:`data`.

.. function:: void i2c_read_data(uint8_t *data, uint16_t length)

    This function receives :code:`length` bytes of data and writes them to
    the array :code:`data`.

.. function:: void i2c_write_register(uint8_t reg, uint8_t data)

    This function writes to bytes of data. First :code:`reg` and then
    :code:`data`.

.. note:: You *cannot* use two calls to :func:`i2c_write_byte` instead of this \
    function because this is only *one* transmission, while two times \
    :func:`i2c_write_byte` would be *two* different transmissons.

.. function:: uint8_t i2c_read_register(uint8_t reg)

    In contrast to :func:`i2c_write_register` you *can* use a call to
    :func:`i2c_write_byte` and to :func:`i2c_read_byte`. This is because
    I2C needs to make two transmissions anyway to change the read / write bit.


.. _Datasheet: https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf
.. _this file: https://github.com/bootc/linux/blob/073993b3f3e23fb8d376f9e159eee410968e0c57/arch/arm/mach-bcm2708/bcm2708.c#L208
