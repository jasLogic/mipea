#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <stdbool.h>

#include "bcm2835_peripherals.h"

volatile uint32_t *gpio_base_pointer;

typedef enum pin_functions {
	INPUT, OUTPUT, ALT0, ALT1, ALT2, ALT3, ALT4, ALT5
} pin_functions;
typedef enum pud {
	PUD_DISABLE, PUD_DOWN, PUD_UP
} pud;

uint32_t *gpio_map(void);
void gpio_unmap(void);

void gpio_func(uint32_t pin, pin_functions function);
extern void gpio_set(uint32_t pin);
extern void gpio_clr(uint32_t pin);
extern bool gpio_tst(uint32_t pin);

void gpio_pud(uint32_t pin, pud val);

void gpio_inp(uint32_t pin);
void gpio_out(uint32_t pin);
void gpio_ca_pud(void);

/* ----- GPIO Registers ----- */
#define GPFSEL	gpio_base_pointer
#define GPFSEL0	*GPFSEL
#define GPFSEL1	*(GPFSEL + 1)
#define GPFSEL2	*(GPFSEL + 2)
#define GPFSEL3	*(GPFSEL + 3)
#define GPFSEL4	*(GPFSEL + 4)
#define GPFSEL5	*(GPFSEL + 5)

#define GPSET	(gpio_base_pointer + 7)
#define GPSET0	*GPSET
#define GPSET1	*(GPSET + 1)

#define GPCLR	(gpio_base_pointer + 10)
#define GPCLR0	*GPCLR
#define GPCLR1	*(GPCLR + 1)

#define GPLEV	(gpio_base_pointer + 13)
#define GPLEV0	*GPLEV
#define GPLEV1	*(GPLEV + 1)

#define GPEDS	(gpio_base_pointer + 16)
#define GPEDS0	*GPEDS
#define GPEDS1	*(GPEDS + 1)

#define GPREN	(gpio_base_pointer + 19)
#define GPREN0	*GPREN
#define GPREN1	*(GPREN + 1)

#define GPFEN	(gpio_base_pointer + 22)
#define GPFEN0	*GPFEN
#define GPFEN1	*(GPFEN + 1)

#define GPHEN	(gpio_base_pointer + 25)
#define GPHEN0	*GPHEN
#define GPHEN1	*(GPHEN + 1)

#define GPLEN	(gpio_base_pointer + 28)
#define GPLEN0	*GPLEN
#define GPLEN1	*(GPLEN + 1)

#define GPAREN	(gpio_base_pointer + 31)
#define GPAREN0	*GPAREN
#define GPAREN1	*(GPAREN + 1)

#define GPAFEN	(gpio_base_pointer + 34)
#define GPAFEN0	*GPAFEN
#define GPAFEN1	*(GPAFEN + 1)

#define GPPUD		*(gpio_base_pointer + 37)

#define GPPUDCLK	(gpio_base_pointer + 38)
#define GPPUDCLK0	*GPPUDCLK
#define GPPUDCLK1	*(GPPUDCLK + 1)

#endif//GPIO_H
