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

#include "gpio.h"

#include <stdint.h>
#include <stddef.h>

#include "peripherals.h"
#include "../config.h" // for inline

static void delay_cycles(unsigned int n)
{
	volatile unsigned int i; // do not optimize delay loop
	for (i = 0; i < n; ++i);
}

uint32_t *gpio_map(void)
{
	if (peripheral_map(&gpio_base_ptr, GPIO_OFFSET, GPIO_SIZE) < 0) {
		return NULL;
	}
	return (uint32_t *)gpio_base_ptr;
}

void gpio_unmap(void)
{
	peripheral_unmap(gpio_base_ptr, GPIO_SIZE);
}

void gpio_func(uint32_t pin, enum gpio_pin_function function)
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
	GP->SET[pin / 32] = (1 << (pin % 32));
}

inline void gpio_clr(uint32_t pin)
{
	GP->CLR[pin / 32] = (1 << (pin % 32));
}

inline uint32_t gpio_tst(uint32_t pin)
{
	return GP->LEV[pin / 32] & (1 << (pin % 32));
}

void gpio_pud(uint32_t pin, enum gpio_pud pud)
{
	GP->PUD = pud;
	delay_cycles(150);
	GP->PUDCLK[pin / 32] = (1 << (pin % 32));
	delay_cycles(150);
	GP->PUD = 0;
	GP->PUDCLK[pin / 32] = 0;
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
