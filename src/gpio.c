/*
 * gpio.c
 * Copyright (C) 2018  jasLogic
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "../config.h" // for inline and BCM235/6/7 or BCM2711

#include <stdint.h>
#include <stddef.h>

#include "gpio.h"
#include "peripherals.h"

static const size_t GPIO_OFFSET = 0x200000;

#if defined(BCM235) || defined(BCM2836_7)
	static const size_t GPIO_SIZE = 0xA0;
#else
	static const size_t GPIO_SIZE = 0xF4;
#endif//BCM2xxx

static volatile uint32_t *gpio_base_ptr = NULL;
volatile struct gpio_register_map *GP = NULL;

static inline void delay_cycles(unsigned int n)
{
	volatile unsigned int i; // do not optimize delay loop
	for (i = 0; i < n; ++i);
}

int gpio_map(void)
{
	if (peripheral_map(&gpio_base_ptr, GPIO_OFFSET, GPIO_SIZE) < 0)
		return -1;
	GP = (volatile struct gpio_register_map *)gpio_base_ptr;
	return 0;
}

void gpio_unmap(void)
{
	peripheral_unmap(gpio_base_ptr, GPIO_SIZE);
}

void gpio_func(uint32_t pin, int function)
{
	GP->FSEL[pin / 10] &= ~(7 << ((pin % 10) * 3)); // clear the 3 bits

	switch(function) {
		case INPUT:
			break;
		case OUTPUT:
			GP->FSEL[pin / 10] |= (0b001 << ((pin % 10) * 3));
			break;
		case ALT0:
			GP->FSEL[pin / 10] |= (0b100 << ((pin % 10) * 3));
			break;
		case ALT1:
			GP->FSEL[pin / 10] |= (0b101 << ((pin % 10) * 3));
			break;
		case ALT2:
			GP->FSEL[pin / 10] |= (0b110 << ((pin % 10) * 3));
			break;
		case ALT3:
			GP->FSEL[pin / 10] |= (0b111 << ((pin % 10) * 3));
			break;
		case ALT4:
			GP->FSEL[pin / 10] |= (0b011 << ((pin % 10) * 3));
			break;
		case ALT5:
			GP->FSEL[pin / 10] |= (0b010 << ((pin % 10) * 3));
			break;
		default:
			break;
	}
}

inline void gpio_set(uint32_t pin)
{
	GP->SET[pin >> 5] = (1 << (pin & 0x1f));
}

inline void gpio_clr(uint32_t pin)
{
	GP->CLR[pin >> 5] = (1 << (pin & 0x1f));
}

inline uint32_t gpio_tst(uint32_t pin)
{
	return GP->LEV[pin >> 5] & (1 << (pin & 0x1f));
}

void gpio_pud(uint32_t pin, int pud)
{
#if defined(BCM235) || defined(BCM2836_7)
	GP->PUD = pud;
	delay_cycles(150);
	GP->PUDCLK[pin >> 5] = (1 << (pin & 0x1f));
	delay_cycles(150);
	GP->PUD = 0;
	GP->PUDCLK[pin >> 5] = 0;
#else
	// BCM2711 has PUD_UP = 1 and PUD_DOWN = 2 (other way around)
	if (pud == PUD_UP)
		pud = 1;
	else if (pud == PUD_DOWN)
		pud = 2;

	GP->PUPPDN[pin >> 4] &= ~(7 << ((pin & 0xf) << 1));
	GP->PUPPDN[pin >> 4] |= pud << ((pin & 0xf) << 1);
#endif//BCM2xxx
}


void gpio_inp(uint32_t pin)
{
	GP->FSEL[pin / 10] &= ~(7 << ((pin % 10) * 3));
}

void gpio_out(uint32_t pin)
{
	GP->FSEL[pin / 10] &= ~(7 << ((pin % 10) * 3)); // clear the 3 bits first
	GP->FSEL[pin / 10] |= (1 << ((pin % 10) * 3));
}
