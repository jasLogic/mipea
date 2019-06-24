.. index::
    single: GPIOs

*****
GPIOs
*****

Macros
======

.. macro:: GPIO_OFFSET

    ::

        0x200000

    This macro defines the offset at which the GPIO registers are located from
    the peripheral base.

.. macro:: GPIO_SIZE

    ::

        0xB0

    This macro holds the size of the GPIO registers which needs to be mapped.

Registers
=========

.. var:: volatile uint32_t *gpio_base_ptr

    This pointer points, when mapped, to the base of the GPIO registers.

.. type:: struct gpio_register_map

    This struct maps the registers of the GPIOs. The names of the struct members
    correspond to the registers from the Datasheet_::

        struct gpio_register_map {
        	uint32_t FSEL[6];
        	uint32_t: 32;
        	uint32_t SET[2];
        	uint32_t: 32;
        	uint32_t CLR[2];
        	uint32_t: 32;
        	uint32_t LEV[2];
        	uint32_t: 32;
        	uint32_t EDS[2];
        	uint32_t: 32;
        	uint32_t REN[2];
        	uint32_t: 32;
        	uint32_t FEN[2];
        	uint32_t: 32;
        	uint32_t HEN[2];
        	uint32_t: 32;
        	uint32_t LEN[2];
        	uint32_t: 32;
        	uint32_t AREN[2];
        	uint32_t: 32;
        	uint32_t AFEN[2];
        	uint32_t: 32;
        	uint32_t PUD;
        	uint32_t PUDCLK[2];
        };

.. macro:: GP

    ::

        #define GP ((volatile struct gpio_register_map *)gpio_base_ptr)

    By using this macro, the registers of the GPIOs can be accessed like this
    :code:`GP->SET[0]`.

Enums
=====

.. type:: _pin_function

    This enum holds the values for the various pin functions::

        enum gpio_pin_function {
        	INPUT, OUTPUT, ALT0, ALT1, ALT2, ALT3, ALT4, ALT5
        };

.. type:: _pull_up_down

    This enum holds the values for the states of the pullups / -downs::

        enum gpio_pud {
        	PUD_DISABLE, PUD_DOWN, PUD_UP
        };

Functions
=========

.. function:: uint32_t * gpio_map(void)

    This function maps the GPIO registers. It calls :func:`peripheral_map` with
    the values :macro:`GPIO_OFFSET` and :macro:`GPIO_SIZE`.

.. function:: void gpio_unmap(void)

    This function unmaps the GPIOs.

.. function:: void gpio_func(uint32_t pin, enum gpio_pin_function function)

    This function sets the pin :code:`pin` to the pin function :code:`function`.

.. function:: void gpio_set(uint32_t pin)

    Set the pin :code:`pin`.

.. function:: void gpio_clr(uint32_t pin)

    Clear the pin :code:`pin`.

.. function:: uint32_t gpio_tst(uint32_t pin)

    Test the pin :code:`pin`. This function returns :code:`0` or :code:`false`
    when the pin is low and non-zero if the pin is high.

.. function:: void gpio_pud(uint32_t pin, enum gpio_pud pud)

    Use the pullup / -down functionality :code:`pud` on the pin :code:`pin`.

.. function:: void gpio_inp(uint32_t pin)

    Make pin :code:`pin` an input.

.. function:: void gpio_out(uint32_t pin)

    Make pin :code:`pin` an output.

.. _Datasheet: https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf
