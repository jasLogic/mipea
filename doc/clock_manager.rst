.. index::
    single: Clock Manager

*************
Clock Manager
*************

Macros
======

.. macro:: CLOCK_MANAGER_OFFSET

    ::

        0x101000

    This macro defines the offset at which the clock manager registers
    are located relative to the peripheral base.

.. macro:: CLOCK_MANAGER_SIZE

    ::

        0xA4

    This macro holds the size of the clock manager registers
    which needs to be mapped.

.. macro:: CM_PASSWD

    ::

        0x5A000000

    This macro holds the clock manager password. This value must always be
    present when writing to a clock manager register
    (e.g. by OR with the value).

Registers
=========

.. var:: volatile uint32_t *clock_manager_base_ptr

    This pointer points, when mapped, to the base of the clock manager registers.

.. type:: struct clock_manager_register_map

    This struct maps the registers of the clock manager.
    The names of the struct members correspond to the registers. Unfortunately,
    the official datasheet does not feature this chapter. But there is an
    upload of this chapter here: `BCM2835 clocks`_::

        struct clock_manager_register_map {
            uint32_t GP0CTL;
            uint32_t GP0DIV;
            uint32_t GP1CTL;
            uint32_t GP1DIV;
            uint32_t GP2CTL;
            uint32_t GP2DIV;
            uint32_t: 32;
            uint32_t: 32;
            uint32_t: 32;
            uint32_t: 32;
            uint32_t PCMCTL;
            uint32_t PCMDIV;
            uint32_t PWMCTL;
            uint32_t PWMDIV;
        }

.. macro:: CM

    ::

        #define CM ((volatile struct clock_manager_register_map *)(clock_manager_base_ptr + 28))

    By using this macro, the registers of the clcok manager can be accessed
    like this :code:`CM->PWMCTL`.

Enums
=====

.. type:: clock_source_t

    This enum holds the values for the different clock sources::

        typedef enum {
            CLOCK_GND,
            CLOCK_OSC,
            CLOCK_TST0,
            CLOCK_TST1,
            CLOCK_PLLA,
            CLOCK_PLLC,
            CLOCK_PLLD,
            CLOCK_HDMI
        } clock_source_t;

Functions
=========

.. function:: uint32_t * clock_map(void)

    This function maps the clock manager registers.
    It calls :func:`peripheral_map` with the values
    :macro:`CLOCK_MANAGER_OFFSET` and :macro:`CLOCK_MANAGER_SIZE`.

.. function:: void clock_unmap(void)

    This function unmaps the clock manager.

The following functions all take a pointer to a clock manager register as an
argument because all the registers for the *different clocks* have the
*same structure*. This means that you just need to tell the clock manager which
clock to use (by pointing to the right register). For example:
:code:`clock_enable(&CM->PWMCTL);`

.. function:: void clock_enable(volatile uint32_t *reg)

    This function enables the clock with the register pointed to by :code:`reg`.

.. function:: void clock_disable(volatile uint32_t *reg)

    This function disables the clock with the register pointed to by :code:`reg`.

.. function:: void clock_configure(volatile uint32_t *reg, clock_source_t src, \
    unsigned int divisor, unsigned int mash)

    This function configures the clock with the register pointed to by
    :code:`reg` and sets up the :type:`clock_source_t` :code:`src`, the divisor
    :code:`divisor` with the mash factor :code:`mash`.

.. todo:: Add a decimal places to the divisor.

.. _BCM2835 clocks: https://de.scribd.com/doc/127599939/BCM2835-Audio-clocks
