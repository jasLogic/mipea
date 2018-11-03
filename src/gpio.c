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

#include "core/bcm2835_peripherals.h"

peripheral gpio_peripheral = {GPIO_BASE, GPIO_BLOCK_SIZE, 0, NULL};

void delay_cycles(unsigned int n) {
	for (unsigned int i = 0; i < n; ++i) {}
}

uint32_t *gpio_map(void) {
	if (peripheral_map(&gpio_peripheral) == NULL) {
		return NULL;
	}
	gpio_base_pointer = (volatile uint32_t *)gpio_peripheral.map;

	gpio_ca_pud(); // Clear all pullup / -downs

	return (uint32_t *)gpio_base_pointer;
}

void gpio_unmap(void) {
	gpio_ca_pud(); // Clear all pullup / -downs
	peripheral_unmap(&gpio_peripheral);
}

void gpio_func(uint32_t pin, pin_functions function) {
	GPFSEL[pin / 10] &= ~(7 << ((pin % 10) * 3)); /* Die drei Bits erst alle 0 machen!!! */

	switch(function) {
		case INPUT:
			break;
		case OUTPUT:
			GPFSEL[pin / 10] |= (1 << ((pin % 10) * 3));
			break;
		case ALT0:
			GPFSEL[pin / 10] |= (0b100 << ((pin % 10) * 3));
			break;
		case ALT1:
			GPFSEL[pin / 10] |= (0b101 << ((pin % 10) * 3));
			break;
		case ALT2:
			GPFSEL[pin / 10] |= (0b110 << ((pin % 10) * 3));
			break;
		case ALT3:
			GPFSEL[pin / 10] |= (0b111 << ((pin % 10) * 3));
			break;
		case ALT4:
			GPFSEL[pin / 10] |= (0b011 << ((pin % 10) * 3));
			break;
		case ALT5:
			GPFSEL[pin / 10] |= (0b010 << ((pin % 10) * 3));
			break;
		default:
			break;
	}
}

inline void gpio_set(uint32_t pin) {
	GPSET[pin / 32] = (1 << (pin % 32));
}

inline void gpio_clr(uint32_t pin) {
	GPCLR[pin / 32] = (1 << (pin % 32));
}

inline bool gpio_tst(uint32_t pin) {
	return GPLEV[pin / 32] &= (1 << (pin % 32));
}

void gpio_pud(uint32_t pin, pud val) {
	GPPUD = val;
	delay_cycles(150);
	GPPUDCLK[pin / 32] = (1 << (pin % 32));
	delay_cycles(150);
	GPPUD = 0;
	GPPUDCLK[pin / 32] = 0;
}



void gpio_inp(uint32_t pin) {
	GPFSEL[pin / 10] &= ~(7 << ((pin % 10) * 3));
}

void gpio_out(uint32_t pin) {
	GPFSEL[pin / 10] &= ~(7 << ((pin % 10) * 3)); /* Die drei Bits erst alle 0 machen!!! */
	GPFSEL[pin / 10] |= (1 << ((pin % 10) * 3));
}

void gpio_ca_pud(void) {
	GPPUD = 0;
	delay_cycles(150);
	for (uint32_t i = 0; i < 32; ++i) {
		GPPUDCLK0 = (1 << i);
	}
	for (uint32_t i = 0; i < 11; ++i) {
		GPPUDCLK1 = (1 << i);
	}
	delay_cycles(150);
	GPPUDCLK0 = 0;
	GPPUDCLK1 = 0;
}
