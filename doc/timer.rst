.. index::
    single: Timer

*****
Timer
*****

Macros
======

.. macro:: TIMER_OFFSET

    ::

        0x003000

    This macro defines the offset at which the timer registers are located from
    the peripheral base.

.. macro:: TIMER_SIZE

    ::

        0x1C

    This macro holds the size of the timer registers which needs to be mapped.

Registers
=========

.. var:: volatile uint32_t *timer_base_ptr

    This pointer points, when mapped, to the base of the timer registers.

.. type:: struct timer_register_map

    This struct maps the registers of the timer.
    The names of the struct members correspond to the registers
    from the Datasheet_::

        struct i2c_register_map {
            uint32_t CS;
            uint32_t CLO;
            uint32_t CHI;
            uint32_t C0;
            uint32_t C1;
            uint32_t C2;
            uint32_t C3;
        };

.. macro:: TIMER

    ::

        #define TIMER ((volatile struct timer_register_map *)timer_base_ptr)

    By using this macro, the registers of the timer can be accessed like this
    :code:`TIMER->CLO`.

Functions
=========

.. function:: int timer_map(void)

    This function maps the timer registers. It calls :func:`peripheral_map` with
    the values :code:`TIMER_OFFSET` and :macro:`TIMER_SIZE`. On error
    :code:`-1` is returned.

.. function:: void timer_unmap(void)

    This function unmaps the timer registers.

.. function:: void timer_read(uint64_t *counter);

    This function reads the value of the timer into the 64-bit varbiale
    pointed to by :code:`counter`.


.. _Datasheet: https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf
