.. index::
    single: SPI

***
SPI
***

Macros
======

.. macro:: SPI_OFFSET

    ::

        0x204000

    This macro defines the offset at which the SPI registers are located from
    the peripheral base.

.. macro:: SPI_SIZE

    ::

        0x14

    This macro holds the size of the I2C registers which needs to be mapped.

Configuration Macros
--------------------
=============================== ===============================
:macro:`SPI_CS_CE0`             Use chip enable 0
:macro:`SPI_CS_CE1`             Use chip enable 1
:macro:`SPI_CS_CE2`             Use chip enable 2
:macro:`SPI_CPHA_CLK_BEGINNING` Data on clock leading edge
:macro:`SPI_CPHA_CLK_MIDDLE`    Data on clock trailing edge
:macro:`SPI_CPOL_RESET_LOW`     Clock polarity: active low
:macro:`SPI_CPOL_RESET_HIGH`    Clock polarity: active high
:macro:`SPI_CSPOL_ACTIVE_LOW`   Chip enable: active low
:macro:`SPI_CSPOL_ACTIVE_HIGH`  Chip enable: active high
=============================== ===============================

Registers
=========

.. var:: volatile uint32_t *spi_base_ptr

    This pointer points, when mapped, to the base of the SPI registers.

.. type:: struct spi_register_map

    This struct maps the registers of the SPI.
    The names of the struct members correspond to the registers
    from the Datasheet_::

        struct spi_register_map {
            uint32_t CS;
            uint32_t FIFO;
            uint32_t CLK;
            uint32_t DLEN;
            uint32_t LTOH;
            uint32_t DC;
        };

.. macro:: SPI

    ::

        #define SPI ((volatile struct spi_register_map *)spi_base_ptr)

    By using this macro, the registers of the SPI can be accessed like this
    :code:`SPI->CS`.

Structs
=======

.. type:: spi_channel_config_t

    This struct is used to configure SPI::

        typedef struct {
            union {
                struct {
                    uint32_t: 2;
                    uint32_t cpha: 1;
                    uint32_t cpol: 1;
                    uint32_t: 2;
                    uint32_t cspol: 1;
                    uint32_t: 14;
                    uint32_t cspol0: 1;
                    uint32_t cspol1: 1;
                    uint32_t cspol2: 1;
                };
                uint32_t cs_register;
            };

            uint16_t divisor;
        } spi_channel_config_t;

    .. member:: uint32_t cs_register

        This member can be directly edited by the anonymous struct inside
        this union. This register maps directly to the :code:`CS` register.
        The settings of this register are described
        in the `Macros`_.

    .. member:: uint16_t divisor

        The master clock divisor.

        .. note:: The clock source is the core clock with a frequency, \
            according to the Datasheet_, of :code:`150 MHz` and \
            according to `this file`_ and other sources of :code:`250 MHz`. \
            When I tested the clock speed of I2C and SPI with a logic analyzer, \
            it seems that :code:`250 MHz` **is correct** \
            (at least for the Raspberry Pi Zero I use).

Functions
=========

.. function:: uint32_t * spi_map(void)

    This function maps the SPI registers. It calls :func:`peripheral_map` with
    the values :macro:`SPI_OFFSET` and :macro:`SPI_SIZE`.

.. function:: void spi_unmap(void)

    This function unmaps the SPI registers.

.. function:: void spi_configure(spi_channel_config_t *config)

    This function configures SPI with a :type:`spi_channel_config_t`
    pointed to by :code:`config`.

.. function:: void spi_set_ce(uint8_t ce)

    This function sets which chip enable line the SPI controller should use.
    This can be a 3 bit value.

.. function:: void spi_transfer_start(void)

    This function starts a SPI transfer.

.. function:: void spi_transfer_stop(void)

    This function stops the current SPI transfer.

.. function:: uint8_t spi_transfer_byte(uint8_t data)

    While there is a SPI transfer active you can call this function as often
    as needed by the slave, to send and receive. This function needs to be
    called between :func:`spi_transfer_start` and :func:`spi_transfer_stop`,
    it  sends :code:`data` over SPI and asynchronously receives
    data and *returns* it.

.. function:: uint8_t spi_send2_recv1(uint8_t data0, uint8_t data1)

    This function writes to bytes of data and than keeps the clock running to
    receive and return the third byte. :func:`spi_transfer_start`
    and :func:`spi_transfer_stop` *may not* be called when using this
    function.

.. _Datasheet: https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf
.. _this file: https://github.com/bootc/linux/blob/073993b3f3e23fb8d376f9e159eee410968e0c57/arch/arm/mach-bcm2708/bcm2708.c#L208
